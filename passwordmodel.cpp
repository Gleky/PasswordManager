#include "passwordmodel.h"

#include "istorage.h"

PasswordModel::PasswordModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void PasswordModel::setStorage(IStorage *storage)
{
    _storage = storage;
    _storage->load(_passwords);
}

int PasswordModel::rowCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant PasswordModel::data(const QModelIndex &index, int role) const
{
    return "Lol";
}

QHash<int, QByteArray> PasswordModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "pwTitle";
    roles[DescriptionRole] = "pwDescription";
    roles[LoginRole] = "pwLogin";
    roles[PasswordRole] = "pwPassword";
    return roles;
}


bool PasswordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    auto item = _passwords[index.row()];

    switch (role)
    {
    case TitleRole:
        item.title = value.toString();
        break;

    case DescriptionRole:
        item.description = value.toString();
        break;

    case LoginRole:
        item.login = value.toString();
        break;

    case PasswordRole:
        item.password = value.toString();
        break;
    }

    dataChanged(index,index, QVector<int>(1, role));
}

int PasswordModel::addNew()
{
    beginResetModel();
    _passwords.append(Password());
    endResetModel();
    return _passwords.size()-1;
}

void PasswordModel::remove(int index)
{
    beginResetModel();
    _passwords.removeAt(index);
    endResetModel();
}
