#ifndef PASSWORDMODEL_H
#define PASSWORDMODEL_H

#include "password.h"

#include <QAbstractListModel>


class PasswordModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PasswordModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    enum Roles{TitleRole, DescriptionRole, LoginRole, PasswordRole};

    QList<Password*> _paswords;
};

#endif // PASSWORDMODEL_H
