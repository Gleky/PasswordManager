#ifndef ISTORAGE_H
#define ISTORAGE_H

#include <QList>
#include <QObject>


struct Password;

class IStorage : public QObject
{
    Q_OBJECT
public:
    IStorage();
    virtual void store(const QList<Password> &passwords) const = 0;
    virtual void load(QList<Password> &passwords) = 0;
    virtual ~IStorage() {}

public slots:
    void setDir(const QString &dir);
    QString storageDir() const;
    virtual QString storageDescription() const = 0;
    virtual bool fileFound() const = 0;
    virtual void removeFile() = 0;

private:
    QString _storageDir;
};

#endif // ISTORAGE_H
