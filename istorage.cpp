#include "istorage.h"

#include <QDir>
#include <QSettings>


IStorage::IStorage()
{
    QSettings settings(QDir::currentPath()+"/settings.ini", QSettings::IniFormat);
    _storageDir = settings.value("storageDir", QDir::homePath() + "/.pwmng/").toString();
}

void IStorage::setDir(const QString &dir)
{
    const auto oldDirPath = _storageDir;
    _storageDir = dir;
    if (!_storageDir.endsWith(".pwmng")) _storageDir += "/.pwmng/";

    QSettings settings(QDir::currentPath()+"/settings.ini", QSettings::IniFormat);
    settings.setValue("storageDir", _storageDir);

    QDir newDir(_storageDir);
    QDir oldDir(oldDirPath);
    if ( !newDir.exists() ) newDir.mkpath("./");

    const auto files = oldDir.entryList(QDir::Files);
    for (auto &file : files)
    {
        QFile(oldDirPath+file).rename(_storageDir+file);
    }
    oldDir.rmdir("./");
}

QString IStorage::storageDir() const
{
    return _storageDir;
}
