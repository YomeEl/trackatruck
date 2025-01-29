#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include <QObject>
#include <QTimer>

class TimeControl : public QObject
{
    Q_OBJECT
public:
    explicit TimeControl(QObject *parent = nullptr);

    QDateTime getCurrentTime();
    QString getCurrentTimeString();
    QString getCurrentDateString;

signals:
    void everySecond();

private:
    QTimer _timer;
};

#endif // TIMECONTROL_H
