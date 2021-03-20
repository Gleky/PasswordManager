#include "passwordmodel.h"

#include "istorage.h"

PasswordModel::PasswordModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void PasswordModel::setStorage(IStorage *storage)
{
    _storage = storage;
    _storage->load(_paswords);
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
