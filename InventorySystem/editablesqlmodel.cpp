#include <QtSql>

#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{
}

Qt::ItemFlags EditableSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 4)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{
    if (index.column() != 4)
        return false;

    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    QString name = data(primaryKeyIndex).toString();

    clear();

    bool ok = setCount(name, value.toInt());

    refresh();
    return ok;
}

void EditableSqlModel::refresh()
{
    setQuery("SELECT name AS Name, price AS Price, wholesale AS Wholesale, manufacturer AS Manufacturer, countItem AS Count FROM Inventory");
}

bool EditableSqlModel::setCount(QString name, int count)
{



    return query.exec();
}

