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
#include "cards.h"

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
	CardButtons.push_back(ui->cardButton2_1);
	CardButtons.push_back(ui->cardButton2_2);
	CardButtons.push_back(ui->cardButton3_1);
	CardButtons.push_back(ui->cardButton3_2);
	CardButtons.push_back(ui->cardButton4_1);
	CardButtons.push_back(ui->cardButton4_2);

	CardLabels.push_back(ui->cardLabel1);
	CardLabels.push_back(ui->cardLabel2);
	CardLabels.push_back(ui->cardLabel3);
	CardLabels.push_back(ui->cardLabel4);
	CardLabels.push_back(ui->cardLabel5);
	CardLabels.push_back(ui->cardLabel6);
	CardLabels.push_back(ui->cardLabel7);
	CardLabels.push_back(ui->cardLabel2_1);
	CardLabels.push_back(ui->cardLabel2_2);
	CardLabels.push_back(ui->cardLabel3_1);
	CardLabels.push_back(ui->cardLabel3_1);
	CardLabels.push_back(ui->cardLabel4_1);
	CardLabels.push_back(ui->cardLabel4_1);

	QObject::connect(ui->miseSize, SIGNAL(valueChanged(int)), this, SLOT(printPotOdds()));
	QObject::connect(ui->potSize, SIGNAL(valueChanged(int)), this, SLOT(printPotOdds()));

	for (unsigned int i = 0; i < CardButtons.size(); i ++) {
		CardWindowSignalMapper->setMapping(CardButtons.at(i), i);
		QObject::connect(CardButtons.at(i), SIGNAL(clicked()), CardWindowSignalMapper, SLOT(map()));
	}

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
	if (MyCards.setCommonCard(currentCard, NewCard)) {
		Card currentCardInstance = MyCards.getCommonCardsObjects().at(currentCard);
		CardButtons.at(currentCard)->setStyleSheet(currentCardInstance.getStyleSheet());
		CardLabels.at(currentCard)->setText(currentCardInstance.getTitle());
		SecondWindow->hide();
	}
	else {
		MainWindowException.throwException("updateCard(Card NewCard)", "Cannot setCard(currentCard, NewCard) : already in hand");
	}
	updateDisabledButtons();
	MyCards.updateCombinaisons();
}

void MainWindow::updateDisabledButtons() {
	std::vector<Card> CurrentCards = MyCards.getCommonCardsObjects();
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
