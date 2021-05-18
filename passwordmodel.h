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

    enum Roles{TitleRole, LoginRole, PasswordRole};
    Q_ENUM(Roles)

public slots:
    int addNew(QString title, QString login, QString password);
    void remove (int index);
    void save() const;

private:
    IStorage *_storage = nullptr;
    QList<Password> _passwords;
};

#endif // PASSWORDMODEL_H
