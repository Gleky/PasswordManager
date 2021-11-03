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

bool decryptFile(const std::string &filePath, const std::string &key, std::string &decryptedText);
}


constexpr unsigned char iv[] = "0123456789012345";

EncryptedFileStorage::EncryptedFileStorage()
{}

void EncryptedFileStorage::store(const QList<Password> &passwords) const
{

}

void EncryptedFileStorage::load(QList<Password> &passwords)
{
    unsigned char key[] = "01234567890123456789012345678901";
    unsigned char plaintext[] = "The quick brown fox jumps over the lazy dog";

    /*
     * Buffer for ciphertext. Ensure the buffer is long enough for the
     * ciphertext which may be longer than the plaintext, depending on the
     * algorithm and mode.
     */
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];
    int decryptedtext_len, ciphertext_len;

    ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,
                              ciphertext);

    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                decryptedtext);

    decryptedtext[decryptedtext_len] = '\0';
    qDebug() << "Source text:" << (char *)plaintext;
    qDebug() << "Encrypted text:" << (char *)ciphertext;
    qDebug() << "decrypt result:" << (char *)decryptedtext;
    qDebug() << "Are they equal?" << (QString((char *)plaintext) == QString((char *)decryptedtext));
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
    std::string decryptedText;

    if (computeHash(key, keyHash) &&
        decryptFile(filePath, keyHash, decryptedText))
    {
        success = true;
    }
    emit passPhraseAccepted(success);
}


namespace {
bool decryptFile(const std::string &filePath, const std::string &key, std::string &decryptedText)
{
    return false;
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
