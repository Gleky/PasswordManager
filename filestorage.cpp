#include "filestorage.h"

#include "password.h"

#include <QSettings>
#include <QDir>


FileStorage::FileStorage()
{}

const char storageDir[] = "/.pwmng/";
const char titleKey[] = "title";
const char loginKey[] = "login";
const char passwordKey[] = "password";

void FileStorage::load(QList<Password> &passwords)
{
    QSettings file(QDir::homePath() + storageDir + _fileName, QSettings::IniFormat);
    auto passwordGroups = file.childGroups();

    for ( auto group : passwordGroups )
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
    QSettings file(QDir::homePath() + storageDir + _fileName, QSettings::IniFormat);
    file.clear();

    int i = 0;
    for ( auto pass : passwords )
    {
        ++i;
        file.beginGroup(QString::number(i));
        file.setValue(titleKey, pass.title);
        file.setValue(loginKey, pass.login);
        file.setValue(passwordKey, pass.password);
        file.endGroup();
    }
}
