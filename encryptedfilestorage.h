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
    bool fileFound() const override;
    void removeFile() override;

signals:
    void askPassPhrase() const;
    void passPhraseAccepted(bool accepted);
    void needStore();
    void needLoad();

private:
    QString const _fileName = "epw";
    QString _passPhrase;
    std::string _decryptedText;
};

#endif // ENCRYPTEDFILESTORAGE_H
