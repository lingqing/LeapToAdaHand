#ifndef USERSERIALPORT_H
#define USERSERIALPORT_H

#include <QSerialPort>
#include <iostream>
#include <QTimerEvent>
#include "typedefine.h"

#define COM_PORT "COM5"
//#define COM_PORT "COM9"

using namespace std;

typedef struct Com_Frame{
    char Tag;
    char type;
    uint16_t lenth;
    char data[20];
    char End[2];
}Com_Frame;

class UserSerialPort: public QSerialPort
{
    Q_OBJECT
public:
    UserSerialPort();

    bool InitSeiralPort();

    bool connectHand();

    void timerEvent(QTimerEvent *event);
    bool isHandConnected();
    void sendFingerAngle(FingerAngle *);
    bool setFingerPosition(int finger, int position);

private:
    Com_Frame readFrame;
    bool mHandConnected;
    bool mRecvFromeSerial;
    int mTimerId;
    bool waitResp();
public slots :
    void serialRead();

signals:
    void readyUpdateHandInfo();

};

#endif // USERSERIALPORT_H
