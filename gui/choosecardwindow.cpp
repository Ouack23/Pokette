#include "choosecardwindow.h"
#include "ui_choosecardwindow.h"
#include <QPushButton>
#include <QList>
#include <QSplitter>
#include <QSignalMapper>
#include "card.h"
#include "exception.h"
#include <iostream>

ChooseCardWindow::ChooseCardWindow(QWidget *parent):
	QDialog(parent),
	ui(new Ui::ChooseCardWindow),
	CardButtons(QList<QPushButton*> ()),
	CardButtonsSignalMapper(new QSignalMapper(this)),
	ChooseCardWindowException(Exception("ChooseCardWindow"))
{
	ui->setupUi(this);
	initCardButtons();

	for(QList<QPushButton*>::iterator i = CardButtons.begin(); i < CardButtons.end(); i++) {
		CardButtonsSignalMapper->setMapping(*i, (*i)->objectName());
		QObject::connect(*i, SIGNAL(clicked()), CardButtonsSignalMapper, SLOT(map()));
	}

	QObject::connect(CardButtonsSignalMapper, SIGNAL(mapped(QString)), this, SLOT(getCardNameFromButton(QString)));
	QObject::connect(this, SIGNAL(CardSelected(const QString)), parent, SLOT(updateCard(const QString)));
}

ChooseCardWindow::~ChooseCardWindow()
{
	delete ui;
	delete CardButtonsSignalMapper;
}

void ChooseCardWindow::initCardButtons() {
	QList<QPushButton*> CardButtonsList = ui->splitter_cards->findChildren<QPushButton*>();

	if (CardButtonsList.isEmpty()) ChooseCardWindowException.throwException("initCardButtons", "Wrong size of CardButtonsList");

	for (QList<QPushButton*>::iterator i = CardButtonsList.begin(); i < CardButtonsList.end(); i++)
		CardButtons.push_back(*i);
}

void ChooseCardWindow::getCardNameFromButton(const QString buttonName) {
	//pushButton_2s
	emit CardSelected(buttonName.right(2));
}

QPushButton* ChooseCardWindow::getButtonFromCard(const Card c) {
	QString title = c.getTitle();
	title.prepend("pushButton_");

	for (QList<QPushButton*>::iterator i = CardButtons.begin(); i != CardButtons.end(); i++) {
		if ((*i)->objectName().contains(title))
			return *i;
	}

	return new QPushButton(0);
}
