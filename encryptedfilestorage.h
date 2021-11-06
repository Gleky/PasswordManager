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

    QString storageDescription() const override;

signals:
    void askPassPhrase();
    void passPhraseAccepted(bool accepted);

private:
    QString const _fileName = "epw";
    QString _passPhrase;
    std::string _decryptedText;
};

#endif // ENCRYPTEDFILESTORAGE_H
