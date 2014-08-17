#include "customdatabasemodel.h"

CustomDatabaseModel::CustomDatabaseModel(QObject *parent)
	:QAbstractTableModel(parent)
{

}

int CustomDatabaseModel::rowCount(const QModelIndex &/*parent*/) const
{
	return 0;
}

int CustomDatabaseModel::columnCount(const QModelIndex &/*parent*/) const
{
	return 0;
}

QVariant CustomDatabaseModel::data(const QModelIndex &index, int role) const
{
	return QVariant();
}

bool CustomDatabaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return false;
}

Qt::ItemFlags CustomDatabaseModel::flags(const QModelIndex &index) const
{
	return 0;
}