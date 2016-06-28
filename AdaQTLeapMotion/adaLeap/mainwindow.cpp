#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    mLeap = new LeapMotionFinger();
    serial = new UserSerialPort();
    serial->InitSeiralPort();

    connect(serial,SIGNAL(readyRead()),serial,SLOT(serialRead()));    //连接槽
    connect(serial,SIGNAL(readyUpdateHandInfo()), this, SLOT(updateHandInfo()));
    connect(mLeap,SIGNAL(readyFingerAngle()),this,SLOT(updateLeapToHand()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::InitFingerAngleRange
 */
void MainWindow::InitFingerAngleRange()
{
//    this->ui->sliderThumbFingerAngle->setMinimum(0);
//    this->ui->sliderThumbFingerAngle->setMaximum(100);
//    this->ui->labelThumbMin->setText(QString("0"));
}

void MainWindow::on_btnSendData_clicked()
{
    FingerAngle angle[5] = {{(char)1,'y',15},{(char)1,'y',15},{(char)1,'y',15},{(char)1,'y',15},{(char)1,'y',15}};
    memcpy(mLeap->mFingerAngle, angle, 5 * sizeof(FingerAngle));
//    serial->write("test", 4);
//    serial->waitForBytesWritten(500);
//    serial->connectHand();
    serial->sendFingerAngle(mLeap->mFingerAngle);
}
/**
 * 打开串口
 * @brief MainWindow::on_btnOpenSerialPort_clicked
 */
void MainWindow::on_btnOpenSerialPort_clicked()
{
    if(!serial->isOpen())
    {
        if(serial->InitSeiralPort())
            cout << "Open serial port succeed" << endl;
        else
            cout << "Open Serial port failed!" << endl;
    }
}
/**
 * @brief MainWindow::updateLeapToHand
 */
void MainWindow::updateLeapToHand()
{
    serial->sendFingerAngle(mLeap->mFingerAngle);
    this->ui->angle->display(mLeap->mFingerAngle[0].angle);
    this->ui->angle_2->display(mLeap->mFingerAngle[1].angle);
    this->ui->angle_3->display(mLeap->mFingerAngle[2].angle);
    this->ui->angle_4->display(mLeap->mFingerAngle[3].angle);
    this->ui->angle_5->display(mLeap->mFingerAngle[4].angle);
}

/**
 * @brief MainWindow::updateHandInfo
 */
void MainWindow::updateHandInfo()
{
    if(serial->isHandConnected())
    {
        this->ui->labelHancConnect->setText(QString("手已连接"));
    }
    else
    {
        this->ui->labelHancConnect->setText(QString("手已断开"));
    }
}
/**
 * @brief MainWindow::on_btnOpenLeap_clicked
 */
void MainWindow::on_btnOpenLeap_clicked()
{
    mLeap->stop = false;
    mLeap->start();
}
/**
 * @brief MainWindow::on_btnCloseLeap_clicked
 */
void MainWindow::on_btnCloseLeap_clicked()
{
    mLeap->stop = true;
}
/**
 * @brief MainWindow::on_slderFingerAngleThumb_valueChanged
 * @param value
 */
void MainWindow::on_slderThumbFingerAngle_sliderMoved(int position)
{
    serial->setFingerPosition(0, position);
}

void MainWindow::on_sliderIndexFingerAngle_sliderMoved(int position)
{
    serial->setFingerPosition(1, position);
}

void MainWindow::on_sliderMiddleFingerAngle_sliderMoved(int position)
{
    serial->setFingerPosition(2, position);
}

void MainWindow::on_sliderRingFingerAngle_sliderMoved(int position)
{
    serial->setFingerPosition(3, position);
}

void MainWindow::on_sliderPinkyFingerAngle_sliderMoved(int position)
{
    serial->setFingerPosition(4, position);
}





