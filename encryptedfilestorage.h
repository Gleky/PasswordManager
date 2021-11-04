#ifndef ENCRYPTEDFILESTORAGE_H
#define ENCRYPTEDFILESTORAGE_H

#include "istorage.h"

class EncryptedFileStorage : public IStorage
{
    Q_OBJECT
    Q_PROPERTY(QString passPhrase MEMBER _passPhrase WRITE setPassPhrase)
public:
    EncryptedFileStorage();

    void store(const QList<Password> &passwords) const override;
    void load(QList<Password> &passwords) override;

    void setPassPhrase(QString passPhrase);

signals:
    void passPhraseAccepted(bool accepted);

private:
    QString const _fileName = "epw";
    QString _passPhrase;
};

#endif // ENCRYPTEDFILESTORAGE_H
