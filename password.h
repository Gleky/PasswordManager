#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>

struct Password
{
public:
    Password() {}
    Password(QString const &ttl, QString const &lgn, QString const &psswrd)
        : title(ttl), login(lgn), password(psswrd)
    {}
    QString title;
    QString login;
    QString password;
};

#endif // PASSWORD_H
