#ifndef LEAPMOTIONFINGER_H
#define LEAPMOTIONFINGER_H

#include "Leap.h"
#include <QThread>
#include <iostream>

#include "typedefine.h"
#include "userfilter.h"

using namespace std;
using namespace Leap;

class LeapMotionFinger:public QThread
{
    Q_OBJECT
public:
    LeapMotionFinger();

    bool startLeap();

    FingerAngle mFingerAngle[5];

    // about thread
    bool stop;
    void run();
private:
    void processFrame(Frame);
    UserFilter mFilter[5];

signals:
    void readyFingerAngle();

};

#endif // LEAPMOTIONFINGER_H
