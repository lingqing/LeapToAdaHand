#include "userserialport.h"


UserSerialPort::UserSerialPort():mHandConnected(false),
    mRecvFromeSerial(false)
{

}

/**
 * @brief UserSerialPort::InitSeiralPort
 * @return
 */
bool UserSerialPort::InitSeiralPort()
{
//    QSerialPortInfo info;
//    this->setPort(info);

    setPortName(COM_PORT);

    open(QIODevice::ReadWrite);      //读写打开
    setBaudRate(QSerialPort::Baud38400);  //波特率
    setDataBits(QSerialPort::Data8); //数据位
    setParity(QSerialPort::NoParity);    //无奇偶校验
    setStopBits(QSerialPort::OneStop);   //无停止位
    setFlowControl(QSerialPort::NoFlowControl);  //无控制

    if((mTimerId = startTimer(1000)) ==0 ) return false;
    return true;
}

void UserSerialPort::serialRead()
{
    //char data[100];
    waitForReadyRead(100);
    read((char *)&readFrame.Tag, 100);
    cout << readFrame.type << endl;
    if(readFrame.Tag == 'a'/* && '5' == readFrame.End*/)
    {
        if(readFrame.type == 'r')
        {
            mRecvFromeSerial = true;
        }
        else
            mRecvFromeSerial = false;
    }
    else
        mRecvFromeSerial = false;
//    cout << "read data is : " << data << endl;
}
/**
 * @brief UserSerialPort::connectHand
 * @return
 */
bool UserSerialPort::connectHand()
{
    Com_Frame con = {'a','a',3,"",'a'};

    if(!isOpen())
    {
        cout << "serial is not opened" << endl;
        return false;
    }
    else
    {
        write(&con.Tag,con.lenth);
        if(waitResp())  return true;
        else
            return false;
    }
}
/**
 * @brief UserSerialPort::waitResp
 * @return
 */
bool UserSerialPort::waitResp()
{
//    char data[100];
//    Com_Frame * readData;
//    waitForReadyRead(500);
//    read(data,100);

//    readData = (Com_Frame *)data;
//    cout << "respond data is " << readFrame.data << endl;


    return true;

}
/**
 * @brief UserSerialPort::timerEvent
 * @param event
 */
void UserSerialPort::timerEvent(QTimerEvent *event)
{
    if(mRecvFromeSerial)
    {
        mRecvFromeSerial = false;
        mHandConnected = true;
    }
    else
    {
        mHandConnected= false;
    }
    emit readyUpdateHandInfo();
//    cout << "serial is connected: " << mHandConnected << endl;
}
/**
 * @brief UserSerialPort::isHandConnected
 * @return
 */
bool UserSerialPort::isHandConnected()
{
    return mHandConnected;
}
/**
 * @brief UserSerialPort::sendFingerAngle
 *                      通过这个方法与Ada手通信，发送5个手指的角度
 * @param angle
 */
void UserSerialPort::sendFingerAngle(FingerAngle * angle)
{
    char *data = (char*)angle;
    Com_Frame con = {'a','l',26,"",'5'};
    memcpy( con.data, data,con.lenth-4);
    if(!isOpen())
    {
        cout << "serial is not opened" << endl;
        return ;
    }
    else
    {
        waitForReadyRead(100);
        write(&con.Tag,con.lenth);
    }
}
/**
 * @brief UserSerialPort::setFingerPosition
 * @param finger
 * @param position
 * @return
 */
bool UserSerialPort::setFingerPosition(int finger, int position)
{
    FingerAngle angle;
    angle.type = 'y';
    angle.type = finger;
    angle.angle = position;

    Com_Frame con;
    con.Tag = 'a';
    con.End[0] = '5';
    con.type = 'f'; // 单个手指
    con.lenth = 4; // 长度为4

    memcpy(&con.data[0], &angle.type, sizeof(FingerAngle));

    if(!isOpen())
    {
        cout << "serial is not opened" << endl;
        return false;
    }
    else
    {
        waitForReadyRead(100);
        write(&con.Tag,con.lenth);
    }
    return true;
}
