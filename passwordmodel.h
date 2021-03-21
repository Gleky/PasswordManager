#ifndef PASSWORDMODEL_H
#define PASSWORDMODEL_H

#include "password.h"

#include <QAbstractListModel>

class IStorage;

class PasswordModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(IStorage *storage MEMBER _storage WRITE setStorage)
public:
    explicit PasswordModel(QObject *parent = nullptr);

    void setStorage(IStorage *storage);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

public slots:
    int addNew();
    void remove (int index);

private:
    enum Roles{TitleRole, DescriptionRole, LoginRole, PasswordRole};

    IStorage *_storage = nullptr;
    QList<Password> _paswords;
};

#endif // PASSWORDMODEL_H
