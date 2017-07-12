#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <queue>
#include "pot_odds.h"
#include "gui/choosecardwindow.h"
#include "commoncards.h"
#include "exception.h"
#include "hand.h"
#include "cards.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	Ui::MainWindow *ui;
	std::vector<QLabel*> ResultPotOdds , CardLabels;
	QLabel *CombinLabel;
	std::vector<QPushButton*> CardButtons;
	ChooseCardWindow *SecondWindow;
	QSignalMapper *CardWindowSignalMapper;

	Exception MainWindowException;
	PotOdds MyPotOdds;
	Cards MyCards;
	int currentCard;
	std::queue<QPushButton*> DisabledCardButtons;

	void updateDisabledButtons();

private slots:
    void printPotOdds();
	void updateCard(const Card);
	void printWindowHandCard(const int);
};

#endif // MAINWINDOW_H
