#include "encryptedfilestorage.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <openssl/evp.h>

#include <QFile>
#include <QDebug>

namespace {
bool computeHash(const std::string &input, std::string &hashed);

int encrypt(const unsigned char *plaintext,
            const int plaintext_len,
            const unsigned char *key,
            const unsigned char *iv,
            unsigned char *ciphertext);

int decrypt(const unsigned char *ciphertext,
            const int ciphertext_len,
            const unsigned char *key,
            const unsigned char *iv,
            unsigned char *plaintext);

bool encryptToFile(const QString &filePath,
                   const std::string &key,
                   const std::string &plainText);

bool decryptFile(const QString &filePath,
                 const std::string &key,
                 std::string &decryptedText);
}


constexpr unsigned char iv[] = "0123456789012345";

EncryptedFileStorage::EncryptedFileStorage()
{}

void EncryptedFileStorage::store(const QList<Password> &passwords) const
{
    //convert list to plaintext

    std::string plainText;

    std::string key = _passPhrase.toStdString(), keyHash;
    Q_ASSERT( computeHash(key, keyHash) );

    auto filePath = storageDir()+_fileName;
    Q_ASSERT( encryptToFile(filePath, key, plainText) );
}

void EncryptedFileStorage::load(QList<Password> &passwords)
{
    if (_passPhrase.isEmpty())
    {
        emit askPassPhrase();
        return;
    }

    //load from decryptedText
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
    auto filePath = storageDir()+_fileName;

    if (computeHash(key, keyHash) &&
        decryptFile(filePath, keyHash, _decryptedText))
    {
        success = true;
        _passPhrase = passPhrase;
    }
    emit passPhraseAccepted(success);
}


namespace {
bool encryptToFile(const QString &filePath,
                   const std::string &key,
                   const std::string &plainText)
{
    const unsigned char *uc_key = (unsigned char*)key.c_str();


    unsigned char *uc_plainText = (unsigned char*)plainText.c_str();
    int plainTextLength = plainText.length();

    QByteArray qba_ciphertext;
    qba_ciphertext.reserve(plainTextLength + EVP_CIPHER_block_size(EVP_aes_256_cbc()));
    unsigned char *uc_ciphertext = (unsigned char*)qba_ciphertext.data();
    int cipherTextLength;

    cipherTextLength = encrypt (uc_plainText,
                                plainTextLength,
                                uc_key,
                                iv,
                                uc_ciphertext);
    uc_ciphertext[cipherTextLength] = '\0';

    Q_ASSERT(cipherTextLength == qba_ciphertext.length());

    QFile existingFile(filePath);
    existingFile.rename(filePath + "_old");

    QFile newFile(filePath);
    Q_ASSERT(!newFile.exists());
    newFile.open(QIODevice::WriteOnly);
    auto bytesWritten = newFile.write(qba_ciphertext);
    if (bytesWritten != cipherTextLength)
    {
        newFile.remove();
        existingFile.rename(filePath);
        return false;
    }
    else
    {
        existingFile.remove();
        return true;
    }
    return false;
}

bool decryptFile(const QString &filePath,
                 const std::string &key,
                 std::string &decryptedText)
{
    QFile encryptedFile(filePath);
    if (!encryptedFile.exists()) return false;
    encryptedFile.open(QIODevice::ReadOnly);

    QByteArray qba_encryptedText = encryptedFile.readAll();
    const unsigned char *uc_key = (unsigned char*)key.c_str();

    unsigned char *uc_ciphertext = (unsigned char*)qba_encryptedText.data();
    int cipherTextLength = qba_encryptedText.length();

    QByteArray qba_decryptedText;
    qba_decryptedText.reserve(cipherTextLength);
    unsigned char *uc_decryptedText = (unsigned char*)qba_decryptedText.data();
    int decryptedTextLength;

    decryptedTextLength = decrypt(uc_ciphertext,
                                cipherTextLength,
                                uc_key,
                                iv,
                                uc_decryptedText);

    uc_decryptedText[decryptedTextLength] = '\0';
    decryptedText = (char *)uc_decryptedText;
    return true;
}

//ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv, ciphertext);

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

int encrypt(const unsigned char *plaintext,
            const int plaintext_len,
            const unsigned char *key,
            const unsigned char *iv,
            unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        qCritical() << "";

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        qCritical() << "";

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        qCritical() << "";
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        qCritical() << "";
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(const unsigned char *ciphertext,
            const int ciphertext_len,
            const unsigned char *key,
            const unsigned char *iv,
            unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        qCritical() << "";

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        qCritical() << "";

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        qCritical() << "";
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        qCritical() << "";
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
} // end unnamed namespace
