#include "filestorage.h"

#include "password.h"

#include <QSettings>
#include <QFile>


FileStorage::FileStorage()
{}

const char titleKey[] = "title";
const char loginKey[] = "login";
const char passwordKey[] = "password";

void FileStorage::load(QList<Password> &passwords)
{
    QSettings file(storageDir() + _fileName, QSettings::IniFormat);
    const auto passwordGroups = file.childGroups();

    for ( auto &group : passwordGroups )
    {
        Password pass;
        file.beginGroup(group);
        pass.title = file.value(titleKey).toString();
        pass.login = file.value(loginKey).toString();
        pass.password = file.value(passwordKey).toString();
        file.endGroup();
        passwords.append(pass);
    }
}

void FileStorage::store(const QList<Password> &passwords) const
{
    QSettings file(storageDir() + _fileName, QSettings::IniFormat);
    file.clear();

    int i = 0;
    for ( auto &pass : passwords )
    {
        ++i;
        file.beginGroup(QString::number(i));
        file.setValue(titleKey, pass.title);
        file.setValue(loginKey, pass.login);
        file.setValue(passwordKey, pass.password);
        file.endGroup();
    }
}

QString FileStorage::storageDescription() const
{
    return "Unprotected text format storage";
}

void FileStorage::removeFile()
{
    QFile::remove(storageDir() + _fileName);
}
