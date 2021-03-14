#ifndef ISTORAGE_H
#define ISTORAGE_H

#include <QList>
struct Password;

class IStorage
{
public:
    virtual void store(const QList<Password> &passwords) const = 0;
    virtual void load(QList<Password> &passwords) = 0;
    virtual ~IStorage() {}
};

#endif // ISTORAGE_H
