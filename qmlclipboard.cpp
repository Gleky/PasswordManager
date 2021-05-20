#include "qmlclipboard.h"

#include <QClipboard>
#include <QGuiApplication>

QmlClipboard::QmlClipboard(QObject *parent)
    : QObject(parent)
{}

void QmlClipboard::copy(QString text) const
{
    QGuiApplication::clipboard()->setText(text);
}

void QmlClipboard::clear() const
{
    QGuiApplication::clipboard()->clear();
}
