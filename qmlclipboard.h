#ifndef QMLCLIPBOARD_H
#define QMLCLIPBOARD_H

#include <QObject>

class QmlClipboard : public QObject
{
    Q_OBJECT
public:
    explicit QmlClipboard(QObject *parent = nullptr);
    Q_INVOKABLE void copy(QString text) const;
    Q_INVOKABLE void clear() const;
};

#endif // QMLCLIPBOARD_H
