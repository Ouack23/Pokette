#include "gui/mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <iostream>

#include "gui/choosecardwindow.h"
#include "pot_odds.h"
#include "card.h"
#include "commoncards.h"

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	ResultPotOdds(std::vector<QLabel*>(0)),
	CardLabels(std::vector<QLabel*>(0)),
	CardButtons(std::vector<QPushButton*>(0)),
	SecondWindow(new ChooseCardWindow(this)),
	CardWindowSignalMapper(new QSignalMapper(this)),
	MainWindowException(Exception("MainWindow")),
	MyPotOdds(PotOdds()),
	MyCommonCards(CommonCards()),
	currentCard(0),
	DisabledCardButtons(std::queue<QPushButton*>())
{
	ui->setupUi(this);

	CombinLabel = ui->label_combin;
	ResultPotOdds.push_back(ui->result);
	ResultPotOdds.push_back(ui->result_2);

	CardButtons.push_back(ui->cardButton1);
	CardButtons.push_back(ui->cardButton2);
	CardButtons.push_back(ui->cardButton3);
	CardButtons.push_back(ui->cardButton4);
	CardButtons.push_back(ui->cardButton5);
	CardButtons.push_back(ui->cardButton6);
	CardButtons.push_back(ui->cardButton7);

	CardLabels.push_back(ui->cardLabel1);
	CardLabels.push_back(ui->cardLabel2);
	CardLabels.push_back(ui->cardLabel3);
	CardLabels.push_back(ui->cardLabel4);
	CardLabels.push_back(ui->cardLabel5);
	CardLabels.push_back(ui->cardLabel6);
	CardLabels.push_back(ui->cardLabel7);

	QObject::connect(ui->miseSize, SIGNAL(valueChanged(int)), this, SLOT(printPotOdds()));
	QObject::connect(ui->potSize, SIGNAL(valueChanged(int)), this, SLOT(printPotOdds()));

	CardWindowSignalMapper->setMapping(CardButtons.at(0), 0);
	CardWindowSignalMapper->setMapping(CardButtons.at(1), 1);
	CardWindowSignalMapper->setMapping(CardButtons.at(2), 2);
	CardWindowSignalMapper->setMapping(CardButtons.at(3), 3);
	CardWindowSignalMapper->setMapping(CardButtons.at(4), 4);
	CardWindowSignalMapper->setMapping(CardButtons.at(5), 5);
	CardWindowSignalMapper->setMapping(CardButtons.at(6), 6);

	QObject::connect(CardButtons.at(0), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	QObject::connect(CardButtons.at(1), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	QObject::connect(CardButtons.at(2), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	QObject::connect(CardButtons.at(3), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	QObject::connect(CardButtons.at(4), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	QObject::connect(CardButtons.at(5), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	QObject::connect(CardButtons.at(6), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));

	QObject::connect(CardWindowSignalMapper, SIGNAL(mapped(int)), this, SLOT(printWindowHandCard(int)));
}

MainWindow::~MainWindow() {
	delete ui;
	delete SecondWindow;
	delete CardWindowSignalMapper;
	delete CombinLabel;
}

void MainWindow::printPotOdds() {
	MyPotOdds.setValues(ui->miseSize->value(),  ui->potSize->value());

	ResultPotOdds.at(0)->setText(MyPotOdds.getPotOdds());
	ResultPotOdds.at(1)->setText(MyPotOdds.getPotOdds2());
}

void MainWindow::printWindowHandCard(const int n) {
	currentCard = n;
	SecondWindow->show();
}

void MainWindow::updateCard(const Card NewCard) {
	if (MyCommonCards.setCard(currentCard, NewCard)) {
		Card currentCardInstance = MyCommonCards.getCard(currentCard);
		CardButtons.at(currentCard)->setStyleSheet(currentCardInstance.getStyleSheet());
		CardLabels.at(currentCard)->setText(currentCardInstance.getTitle());
		SecondWindow->hide();
	}
	else {
		MainWindowException.throwException("updateCard(Card NewCard)", "Cannot setCard(currentCard, NewCard) : already in hand");
	}
	updateDisabledButtons();
	updateCombin();
}

void MainWindow::updateDisabledButtons() {
	std::vector<Card> CurrentCards = MyCommonCards.getCards();
	std::vector<Card>::iterator i;
	QPushButton* tmp(0);

	while (DisabledCardButtons.size() != 0) {
		DisabledCardButtons.front()->setDisabled(false);
		DisabledCardButtons.pop();
	}

	for (i = CurrentCards.begin(); i < CurrentCards.end(); i++) {
		tmp = SecondWindow->getButtonFromCard(*i);
		tmp->setDisabled(true);
		DisabledCardButtons.push(tmp);
	}
}

void MainWindow::updateCombin() {
	QString combine = MyCommonCards.getCurrentCombinaisonQString();
	CombinLabel->setText(combine);
}
