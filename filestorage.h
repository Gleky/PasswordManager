#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "istorage.h"

#include <QObject>


class FileStorage : public IStorage
{
    Q_OBJECT
public:
    FileStorage();

    void load(QList<Password> &passwords) override;
    void store(const QList<Password> &passwords) const override;

private:
    QString const _fileName = "ololo.ini";
};

#endif // FILESTORAGE_H
