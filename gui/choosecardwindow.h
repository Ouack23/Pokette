#ifndef CHOOSECARDWINDOW_H
#define CHOOSECARDWINDOW_H

#include <QDialog>
#include <QList>
#include <QPushButton>
#include <QSignalMapper>
#include "card.h"
#include "exception.h"

namespace Ui {
class ChooseCardWindow;
}

class ChooseCardWindow : public QDialog
{
	Q_OBJECT

public:
	explicit ChooseCardWindow(QWidget *parent = 0);
	~ChooseCardWindow();
	QPushButton* getButtonFromCard(const Card);

private:
	Ui::ChooseCardWindow *ui;
	QList<QPushButton*> CardButtons;
	QSignalMapper *CardButtonsSignalMapper;
	Exception ChooseCardWindowException;

	void initCardButtons();
	void printCardButtons();

private slots:
	void getCardNameFromButton(const QString);

signals:
	void CardSelected(const QString);
};

#endif // CHOOSECARDWINDOW_H
