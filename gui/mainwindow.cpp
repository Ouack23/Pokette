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
#include "functions.h"

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
	MyCards(Cards()),
	currentCard(0),
	DisabledCardButtons(std::queue<QPushButton*>())
{
	ui->setupUi(this);

	CombinLabel = ui->label_combin;

	ResultPotOdds.push_back(ui->result);
	ResultPotOdds.push_back(ui->result_2);

	CardButtons.push_back(ui->card_button_own1);
	CardButtons.push_back(ui->card_button_own2);
	CardButtons.push_back(ui->card_button_common1);
	CardButtons.push_back(ui->card_button_common2);
	CardButtons.push_back(ui->card_button_common3);
	CardButtons.push_back(ui->card_button_common4);
	CardButtons.push_back(ui->card_button_common5);
	CardButtons.push_back(ui->card_button_adv1_1);
	CardButtons.push_back(ui->card_button_adv1_2);
	CardButtons.push_back(ui->card_button_adv2_1);
	CardButtons.push_back(ui->card_button_adv2_2);
	CardButtons.push_back(ui->card_button_adv3_1);
	CardButtons.push_back(ui->card_button_adv3_2);
	CardButtons.push_back(ui->card_button_adv4_1);
	CardButtons.push_back(ui->card_button_adv4_2);
	CardButtons.push_back(ui->card_button_adv5_1);
	CardButtons.push_back(ui->card_button_adv5_2);

	CardLabels.push_back(ui->card_label_own1);
	CardLabels.push_back(ui->card_label_own2);
	CardLabels.push_back(ui->card_label_common1);
	CardLabels.push_back(ui->card_label_common2);
	CardLabels.push_back(ui->card_label_common3);
	CardLabels.push_back(ui->card_label_common4);
	CardLabels.push_back(ui->card_label_common5);
	CardLabels.push_back(ui->card_label_adv1_1);
	CardLabels.push_back(ui->card_label_adv1_2);
	CardLabels.push_back(ui->card_label_adv2_1);
	CardLabels.push_back(ui->card_label_adv2_2);
	CardLabels.push_back(ui->card_label_adv3_1);
	CardLabels.push_back(ui->card_label_adv3_2);
	CardLabels.push_back(ui->card_label_adv4_1);
	CardLabels.push_back(ui->card_label_adv4_2);
	CardLabels.push_back(ui->card_label_adv5_1);
	CardLabels.push_back(ui->card_label_adv5_2);

	for (unsigned int i = 0; i < 6; i++) {
		MyCards.addHand(Hand());
		MyCards.addCombinaison(Combinaison());
	}

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

void MainWindow::updateCard(const QString CardName) {
	Card NewCard = Card();
	NewCard.setCard(CardName);

	if (MyCards.setCard(currentCard, NewCard)) {
		std::vector<Card> allCards = MyCards.getAllCards();
		Card currentCardInstance = allCards.at(currentCard);
		CardButtons.at(currentCard)->setStyleSheet(currentCardInstance.getStyleSheet());
		CardLabels.at(currentCard)->setText(currentCardInstance.getTitle());
		SecondWindow->hide();
	}
	else MainWindowException.throwException("updateCard(Card NewCard)", "Cannot setCard(currentCard, NewCard)");

	updateDisabledButtons();
	MyCards.updateCombinaisons();
}

void MainWindow::updateDisabledButtons() {
	std::vector<Card> CurrentCards = MyCards.getAllCards();
	std::vector<Card>::const_iterator i;
	QPushButton* tmp(0);

	while (!DisabledCardButtons.empty()) {
		DisabledCardButtons.front()->setDisabled(false);
		DisabledCardButtons.pop();
	}

	for (i = CurrentCards.begin(); i != CurrentCards.end(); i++) {
		tmp = SecondWindow->getButtonFromCard(*i);
		tmp->setDisabled(true);
		DisabledCardButtons.push(tmp);
	}
}
