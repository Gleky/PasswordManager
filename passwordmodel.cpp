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
    return _passwords.size();
}

QVariant PasswordModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case TitleRole:
        return _passwords.at(index.row()).title;

    case DescriptionRole:
        return _passwords.at(index.row()).description;

    case LoginRole:
        return _passwords.at(index.row()).login;

    case PasswordRole:
        return _passwords.at(index.row()).password;
    }
    return  QVariant();
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
    if ( index.row() >= _passwords.size() ) return false;
    auto &item = _passwords[index.row()];
    auto newText = value.toString();

    switch (role)
    {
    case TitleRole:
        if (item.title != newText) item.title = newText;
        else return false;
        break;

    case DescriptionRole:
        if (item.description != newText) item.description = newText;
        else return false;
        break;

    case LoginRole:
        if (item.login != newText) item.login = newText;
        else return false;
        break;

    case PasswordRole:
        if (item.password != newText) item.password = newText;
        else return false;
        break;
    }

    dataChanged(index,index, QVector<int>(1, role));
    return true;
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

void PasswordModel::save() const
{
    _storage->store(_passwords);
}
