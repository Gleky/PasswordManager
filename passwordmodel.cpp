#include "passwordmodel.h"

#include "istorage.h"

PasswordModel::PasswordModel(QObject *parent)
    :QAbstractListModel(parent)
{}

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
    roles[LoginRole] = "pwLogin";
    roles[PasswordRole] = "pwPassword";
    return roles;
}


bool PasswordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( index.row() >= _passwords.size() || index.row() < 0 ) return false;
    auto &item = _passwords[index.row()];
    auto newText = value.toString();

    switch (role)
    {
    case TitleRole:
        if (item.title != newText) item.title = newText;
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

    emit dataChanged(index,index, QVector<int>(1, role));
    return true;
}

int PasswordModel::addNew(QString title, QString login, QString password)
{
    beginResetModel();
    _passwords.append(Password(title, login, password));
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
