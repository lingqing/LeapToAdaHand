#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

#include "leapmotionfinger.h"
#include "userserialport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitFingerAngleRange();

private slots:
    void on_btnSendData_clicked();
    void on_btnOpenSerialPort_clicked();

    void updateHandInfo();
    void updateLeapToHand();

    void on_btnOpenLeap_clicked();
    void on_btnCloseLeap_clicked();

    void on_slderThumbFingerAngle_sliderMoved(int position);
    void on_sliderIndexFingerAngle_sliderMoved(int position);
    void on_sliderPinkyFingerAngle_sliderMoved(int position);
    void on_sliderRingFingerAngle_sliderMoved(int position);
    void on_sliderMiddleFingerAngle_sliderMoved(int position);


private:
    Ui::MainWindow *ui;
    UserSerialPort *serial;
    LeapMotionFinger *mLeap;

};

#endif // MAINWINDOW_H
