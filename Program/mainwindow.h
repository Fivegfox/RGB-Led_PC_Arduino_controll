#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <cstring>
#include<fstream>
#include <QMessageBox>
#include <QInputDialog>
#include<sys/stat.h>
#include<QTabBar>
//#include <QtTest/QTest>
#include<QTimer>
#include<QScrollBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    int Language();
    void GETt();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_valueChanged();

    void on_spinBox_valueChanged();

    void on_horizontalSlider_2_valueChanged();

    void on_spinBox_2_valueChanged();

    void on_horizontalSlider_3_valueChanged();

    void on_spinBox_3_valueChanged();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_clicked(bool checked);
    void LoadSettings();
    void on_lineEdit_textChanged();

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
