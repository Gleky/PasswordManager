#include "passwordmodel.h"

PasswordModel::PasswordModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

int PasswordModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant PasswordModel::data(const QModelIndex &index, int role) const
{
    return 0;
}

QHash<int, QByteArray> PasswordModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[DescriptionRole] = "description";
    roles[LoginRole] = "login";
    roles[PasswordRole] = "password";
    return roles;
}
