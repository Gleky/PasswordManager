#include "encryptedfilestorage.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <openssl/evp.h>

#include <QFile>


bool computeHash(const std::string &input, std::string &hashed);
bool decryptFile(const std::string &filePath, const std::string &key);

EncryptedFileStorage::EncryptedFileStorage()
{}

void EncryptedFileStorage::store(const QList<Password> &passwords) const
{

}

void EncryptedFileStorage::load(QList<Password> &passwords)
{

}

void EncryptedFileStorage::setPassPhrase(QString passPhrase)
{
    if (!QFile::exists(storageDir() + _fileName))
    {
        _passPhrase = passPhrase;
        emit passPhraseAccepted(true);
        return;
    }

    bool success = false;
    std::string key = passPhrase.toStdString(), keyHash;
    std::string filePath = (storageDir()+_fileName).toStdString();

    if (computeHash(key, keyHash) &&
        decryptFile(filePath, keyHash))
    {
        success = true;
    }
    emit passPhraseAccepted(success);
}


bool computeHash(const std::string& input, std::string& hashed)
{
    bool success = false;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) return success;

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength = 0;

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) &&
        EVP_DigestUpdate(context, input.c_str(), input.length()) &&
        EVP_DigestFinal_ex(context, hash, &hashLength))
    {
        std::stringstream ss;
        for (unsigned int i = 0; i < hashLength; ++i)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }

        hashed = ss.str();
        success = true;
    }
    EVP_MD_CTX_free(context);
    return success;
}

bool decryptFile(const std::string &filePath, const std::string &key)
{
    bool success = false;
    return success;
}
