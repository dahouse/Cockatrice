#ifndef DLG_CREATE_RANDOM_H
#define DLG_CREATE_RANDOM_H

#include <QDialog>
#include "carddatabase.h"

class QCheckBox;
class QComboBox;
class QLabel;
class QSpinBox;

class DlgCreateRandom : public QDialog {
	Q_OBJECT
public:
	DlgCreateRandom(QWidget* parent = 0);
	int getCmc();
	int getComparator();
	QString getType();
	bool getDestroy();
	QList<CardInfo *> getCardPool();
	int getAmount();
private slots:
	void actOk();
	void refreshData();
	void changeTypeCat();
private:
	QLabel *cmcLabel, *cardPool, *cardPoolLabel, *typeLabel, *amountLabel;
	QSpinBox *cmcBox, *amountBox;
	QCheckBox *destroyCheckbox, *anyCheckbox;
	QComboBox *comparatorBox, *typeCatBox, *typeBox;
	QList<CardInfo *> cardList;
};

#endif