#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QDebug>
#include "dlg_create_random.h"
#include "main.h"

DlgCreateRandom::DlgCreateRandom(QWidget *parent)
	: QDialog(parent)
{
	cmcLabel = new QLabel(tr("&CMC:"));
	cmcBox = new QSpinBox;
	cmcBox->setValue(0);
	cmcLabel->setBuddy(cmcBox);
	connect(cmcBox, SIGNAL(valueChanged(int)), this, SLOT(refreshData()));

	comparatorBox = new QComboBox;
	comparatorBox->addItem("=", 0);
	comparatorBox->addItem(">", 1);
	comparatorBox->addItem("<", 2);
	comparatorBox->addItem(">=", 3);
	comparatorBox->addItem("<=", 4);
	connect(comparatorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshData()));

	destroyCheckbox = new QCheckBox(tr("&Destroy token when it leaves the table"));
	destroyCheckbox->setChecked(true);

	anyCheckbox = new QCheckBox(tr("&Any"));
	connect(anyCheckbox, SIGNAL(stateChanged(int)), this, SLOT(refreshData()));

	typeLabel = new QLabel(tr("Type:"));
	typeCatBox = new QComboBox;
	typeCatBox->addItem("Type");
	typeCatBox->addItem("Subtype");
	typeCatBox->addItem("Supertype");
	connect(typeCatBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTypeCat()));

	typeBox = new QComboBox;
	typeBox->addItems(db->getTypes());
	typeBox->setEditable(true);
	typeBox->setCurrentText("Creature");
	connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshData()));

	amountLabel = new QLabel(tr("Amount:"));
	amountBox = new QSpinBox;
	amountBox->setValue(1);
	amountBox->setRange(1, 3);

	QGridLayout *grid = new QGridLayout;
	grid->addWidget(cmcLabel, 0, 0);
	grid->addWidget(comparatorBox, 0, 1);
	grid->addWidget(cmcBox, 0, 2);
	grid->addWidget(anyCheckbox, 0, 3);
	grid->addWidget(typeLabel, 1, 0);
	grid->addWidget(typeCatBox, 1, 1);
	grid->addWidget(typeBox, 1, 2);
	grid->addWidget(amountLabel, 2, 0);
	grid->addWidget(amountBox, 2, 1);
	grid->addWidget(destroyCheckbox, 3, 0, 1, 2, Qt::AlignLeft);

	QGroupBox *tokenDataGroupBox = new QGroupBox(tr("Token data:"));
	tokenDataGroupBox->setLayout(grid);

	cardPoolLabel = new QLabel(tr("Number of possible results:"));
	cardPool = new QLabel(QString());

	QVBoxLayout *poolDataBox = new QVBoxLayout;
	poolDataBox->addWidget(cardPoolLabel);
	poolDataBox->addWidget(cardPool);

	QGroupBox *cardPoolGroupBox = new QGroupBox(QString());
	cardPoolGroupBox->setLayout(poolDataBox);

	QVBoxLayout *leftVBox = new QVBoxLayout;
	leftVBox->addWidget(tokenDataGroupBox);
	leftVBox->addStretch();

	QHBoxLayout *hbox = new QHBoxLayout;
	hbox->addLayout(leftVBox);
	hbox->addWidget(cardPoolGroupBox);

	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(actOk()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(hbox);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);

	setWindowTitle(tr("Create random token"));
	setFixedHeight(sizeHint().height());
	setMinimumWidth(300);

	refreshData();
}

void DlgCreateRandom::refreshData()
{
	bool anyChecked = anyCheckbox->isChecked();
	comparatorBox->setEnabled(!anyChecked);
	cmcBox->setEnabled(!anyChecked);
	cardList = db->getCards(anyChecked ? -1 : cmcBox->value(), anyChecked? -1 : comparatorBox->itemData(comparatorBox->currentIndex()).toInt(), typeBox->currentText());
	cardPool->setText(QString::number(cardList.size()));
}

int DlgCreateRandom::getCmc()
{
	return anyCheckbox->isChecked() ? -1 : cmcBox->value();
}

int DlgCreateRandom::getComparator()
{
	return anyCheckbox->isChecked() ? -1 : comparatorBox->itemData(comparatorBox->currentIndex()).toInt();
}

QString DlgCreateRandom::getType()
{
	return typeBox->currentText();
}

bool DlgCreateRandom::getDestroy()
{
	return destroyCheckbox->isChecked();
}

QList<CardInfo *> DlgCreateRandom::getCardPool()
{
	return cardList;
}

void DlgCreateRandom::actOk()
{
	accept();
}

void DlgCreateRandom::changeTypeCat()
{
	typeBox->clear();
	switch (typeCatBox->currentIndex())
	{
		case 0:
			typeBox->addItems(db->getTypes());
			break;
		case 1:
			typeBox->addItems(db->getSubtypes());
			break;
		case 2:
			typeBox->addItems(db->getSupertypes());
			break;
	}
	refreshData();
}

int DlgCreateRandom::getAmount()
{
	return amountBox->value();
}

