#ifndef CUSTOMDATABASEMODEL_H
#define CUSTOMDATABASEMODEL_H

#include <QAbstractTableModel>

class QVariant;

class CustomDatabaseModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	CustomDatabaseModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif