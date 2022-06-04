#ifndef LABBOCK_H
#define LABBOCK_H

#include <QObject>
#include "listmedal.h"

class base : public QObject
{
    Q_OBJECT
public:
    explicit base(QObject *parent = nullptr); //
    listModal *modal;

public slots:
    bool parsing(QString pin, QString searchSubstring);
    void cryptCopy(int index, QString parametr, QString pin);


protected:
    QObject *viewer;
};

#endif // BASE_H
