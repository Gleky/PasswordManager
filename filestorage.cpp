#include "filestorage.h"

#include "password.h"

#include <QSettings>


FileStorage::FileStorage()
{}

const QString titleKey = "title";
const QString descriptionKey = "description";
const QString loginKey = "login";
const QString passwordKey = "password";

void FileStorage::load(QList<Password> &passwords)
{
    QSettings file(_fileName, QSettings::IniFormat);
    auto passwordGroups = file.childGroups();

    for ( auto group : passwordGroups )
    {
        Password pass;
        file.beginGroup(group);
        pass.title = file.value(titleKey).toString();
        pass.description = file.value(descriptionKey).toString();
        pass.login = file.value(loginKey).toString();
        pass.password = file.value(passwordKey).toString();
        file.endGroup();
        passwords.append(pass);
    }
}

void FileStorage::store(const QList<Password> &passwords) const
{
    QSettings file(_fileName, QSettings::IniFormat);
    file.clear();

    int i = 0;
    for ( auto pass : passwords )
    {
        ++i;
        file.beginGroup(QString::number(i));
        file.setValue(titleKey, pass.title);
        file.setValue(descriptionKey, pass.description);
        file.setValue(loginKey, pass.login);
        file.setValue(passwordKey, pass.password);
        file.endGroup();
    }
}
