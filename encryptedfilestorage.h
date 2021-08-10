#ifndef ENCRYPTEDFILESTORAGE_H
#define ENCRYPTEDFILESTORAGE_H

#include "istorage.h"

class EncryptedFileStorage : public IStorage
{
    Q_OBJECT
public:
    EncryptedFileStorage();

    void store(const QList<Password> &passwords) const override;
    void load(QList<Password> &passwords) override;

private:
};

#endif // ENCRYPTEDFILESTORAGE_H
