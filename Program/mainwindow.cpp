#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QVector>
QVector <QString> f1;
QVector <QString> zna;
QString del1="Delete";
QString del2="Do you want to delete your colour?";
QString yes="Yes";
QString no="No";
QString err="ERROR!";
QString errm="SET NAME FOR COLOR!";
QString save="Save";
QString CN="Color Name:";
QVector <QString> setn;
QVector <QString> setzn;


void MainWindow::LoadSettings(){
    QString defset="debug=0";
    struct stat sb;
    bool exs=true;
    if(stat("set.cfg", &sb) != 0) exs=false;
    if (exs==false){
        std::ofstream FDC;
        FDC.open("set.cfg");
        FDC << defset.toStdString();
        FDC.close();
        exs=true;
    }
    std::ifstream setfi;
    setfi.open("set.cfg");
    std::string a;
    //QVector<QString> vec;
    //QVector <QString> vec2;
    int count=0;
    while(getline(setfi, a)){
    count++;
    }
    setfi.close();
    if (count ==0){
        std::ofstream FDC;
        FDC.open("set.cfg");
        FDC << defset.toStdString();
        FDC.close();
        exs=true;
    }
    setfi.open("set.cfg");
    while(getline(setfi, a)){
    setzn.push_back(QString::fromStdString(a));
    }
    setfi.close();
    int tmp;
    QString qr;
    for(int i=0; i<setzn.length(); i++){
    tmp=setzn[i].indexOf("=",0);
    qr="";
    for(int j=0; j < tmp; j++)
        qr[j]=setzn[i][j];
    setn.push_back(qr);
    setzn[i].remove(0,tmp+1);
    }
    for(int i=0; i<setn.length(); i++){
        if(setn[i]=="debug") { ui->checkBox->setChecked(setzn[i].toInt());
            ui->textBrowser->setVisible(setzn[i].toInt());
        }
    }
}


void USF(){
std::ofstream set;
set.open("set.cfg");
for(int i=0; i<setn.length();i++)
    set<<setn[i].toStdString()+'='+setzn[i].toStdString()<<'\n';
set.close();
}



int MainWindow::Language(){
std::ifstream f;
struct stat sb;
if(stat("lang.cfg", &sb) != 0) return 0;
f.open("lang.cfg");
std::string a;
QVector<QString> vec;
QVector <QString> vec2;
while(getline(f, a)){
vec.push_back(QString::fromStdString(a));
}
f.close();
int tmp;
QString qr;
for(int i=0; i<vec.length(); i++){
tmp=vec[i].indexOf("=",0);
qr="";
for(int j=0; j < tmp; j++)
    qr[j]=vec[i][j];
vec2.push_back(qr);
vec[i].remove(0,tmp+1);
}
for(int i=0; i<vec2.length(); i++){
    if(vec2[i]=="connect") ui->pushButton_2->setText(vec[i]);
    if(vec2[i]=="send") ui->pushButton->setText(vec[i]);
    if(vec2[i]=="getcolor") ui->pushButton_4->setText(vec[i]);
    if(vec2[i]=="close") ui->pushButton_3->setText(vec[i]);
    if(vec2[i]=="red") ui->label->setText(vec[i]);
    if(vec2[i]=="green") ui->label_2->setText(vec[i]);
    if(vec2[i]=="blue") ui->label_3->setText(vec[i]);
    if(vec2[i]=="setup") ui->pushButton_5->setText(vec[i]);
    if(vec2[i]=="save") ui->pushButton_6->setText(vec[i]);
    if(vec2[i]=="delete") ui->pushButton_7->setText(vec[i]);
    if(vec2[i]=="yes") yes=vec[i];
    if(vec2[i]=="no") no=vec[i];
    if(vec2[i]=="del1") del1=vec[i];
    if(vec2[i]=="del2") del2=vec[i];
    if(vec2[i]=="err") err=vec[i];
    if(vec2[i]=="errm") errm=vec[i];
    if(vec2[i]=="save") save=vec[i];
    if(vec2[i]=="CN") CN=vec[i];
    if(vec2[i]=="tab1") ui->tabWidget->setTabText(0,vec[i]);
    if(vec2[i]=="tab2") ui->tabWidget->setTabText(1,vec[i]);
    if(vec2[i]=="tab3") ui->tabWidget->setTabText(2, vec[i]);
    if(vec2[i]=="profile") ui->label_4->setText(vec[i]);
    if(vec2[i]=="debug") ui->checkBox->setText(vec[i]);
}
return 1;
}


void UF(){
std::ofstream f;
f.open("colors.txt");
for(int i=0; i<f1.length();i++)
    f<<zna[i].toStdString()+':'+f1[i].toStdString()<<'\n';
f.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            ui->comboBox->addItem(info.portName());
    std::string a;

    std::ifstream f;
    f.open("colors.txt");
    while(getline(f, a)){
    f1.push_back(QString::fromStdString(a));
    }
    f.close();
     int tmp;
    QString qr;
    for(int i=0; i<f1.length(); i++){
    tmp=f1[i].indexOf(":",0);
    qr="";
    for(int j=0; j < tmp; j++)
        qr[j]=f1[i][j];
    zna.push_back(qr);
    f1[i].remove(0,tmp+1);
}
for(int i=0; i<zna.length(); i++)
ui->comboBox_2->addItem(zna[i]);
Language();
LoadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSerialPort serial;

void MainWindow::on_pushButton_clicked()
{
    int red = ui->horizontalSlider->value();
    int green = ui->horizontalSlider_2->value();
    int blue = ui->horizontalSlider_3->value();
    QString RED = QString::number(red);
    QString GREEN = QString::number(green);
    QString BLUE = QString::number(blue);
    QString FS = RED + ':'+ GREEN + ':' + BLUE;
   serial.write(FS.toUtf8());
ui->textBrowser->setText(ui->textBrowser->toPlainText() + "\n send> " + FS.toUtf8());
QScrollBar *sb = ui->textBrowser->verticalScrollBar();
sb->setValue(sb->maximum());
}



void MainWindow::on_pushButton_2_clicked()
{
    if (serial.portName() != ui->comboBox->currentText())
    {
          serial.close();
          serial.setPortName(ui->comboBox->currentText());
    }
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    serial.open(QSerialPort::ReadWrite);

}

void MainWindow::on_pushButton_3_clicked()
{
    serial.close();
}

void MainWindow::on_horizontalSlider_valueChanged()
{
    ui->spinBox->setValue(ui->horizontalSlider->value());
}

void MainWindow::on_spinBox_valueChanged()
{
    ui->horizontalSlider->setValue(ui->spinBox->value());
}


void MainWindow::on_horizontalSlider_2_valueChanged()
{
    ui->spinBox_2->setValue(ui->horizontalSlider_2->value());
}

void MainWindow::on_spinBox_2_valueChanged()
{
    ui->horizontalSlider_2->setValue(ui->spinBox_2->value());
}


void MainWindow::on_horizontalSlider_3_valueChanged()
{
    ui->spinBox_3->setValue(ui->horizontalSlider_3->value());
}

void MainWindow::on_spinBox_3_valueChanged()
{
    ui->horizontalSlider_3->setValue(ui->spinBox_3->value());
}

QString t;

void MainWindow::GETt(){
    t= QString::fromUtf8(serial.readAll());
     ui->textBrowser->setText(ui->textBrowser->toPlainText() + "\n get> "+ t);
     QScrollBar *sb = ui->textBrowser->verticalScrollBar();
     sb->setValue(sb->maximum());
    int r;
    QString qr;
    int g;
    QString qg;
    int b;
    int tmp;
    tmp=t.indexOf(":",0);
    for(int j=0; j < tmp; j++)
        qr[j]=t[j];
    t.remove(0,tmp+1);
    r=qr.toInt();
    tmp=t.indexOf(":",0);
    for(int j=0; j < tmp; j++)
        qg[j]=t[j];
    t.remove(0,tmp+1);
    g=qg.toInt();
    b=t.toInt();
    ui->spinBox->setValue(r);
    ui->spinBox_2->setValue(g);
    ui->spinBox_3->setValue(b);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString str2 = "GeS";
    serial.write(str2.toUtf8());
    QTimer::singleShot(5000, this, SLOT(GETt()));

}

void MainWindow::on_pushButton_6_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, save, CN, QLineEdit::Normal,"", &ok);
    if(text.length()==0){
        QMessageBox msgBox;
        msgBox.setText(err);
        msgBox.setInformativeText(errm);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    } else {
    QString r=QString::number(ui->spinBox->value());
    QString g=QString::number(ui->spinBox_2->value());
    QString b=QString::number(ui->spinBox_3->value());
    QString ft=r+':'+g+':'+b;
    f1.push_back(ft);
    zna.push_back(text);
    ui->comboBox_2->addItem(zna[zna.length()-1]);
    UF();
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(del1);
    msgBox.setInformativeText(del2);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes, yes);
    msgBox.setButtonText(QMessageBox::No, no);
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes){
        int index=ui->comboBox_2->currentIndex();
        f1.remove(index);
        zna.remove(index);
        ui->comboBox_2->removeItem(index);
        UF();
}
}

void MainWindow::on_pushButton_5_clicked()
{
    int index = ui->comboBox_2->currentIndex();
    QString zn=f1[index];
    int r;
    QString qr;
    int g;
    QString qg;
    int b;
    int tmp;
    tmp=zn.indexOf(":",0);
    for(int j=0; j < tmp; j++)
        qr[j]=zn[j];
    zn.remove(0,tmp+1);
    r=qr.toInt();
    tmp=zn.indexOf(":",0);
    for(int j=0; j < tmp; j++)
        qg[j]=zn[j];
    zn.remove(0,tmp+1);
    g=qg.toInt();
    b=zn.toInt();
    ui->spinBox->setValue(r);
    ui->spinBox_2->setValue(g);
    ui->spinBox_3->setValue(b);
    serial.write(f1[index].toUtf8());

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    int z=checked;
    ui->textBrowser->setVisible(checked);
    for(int i=0; i<setn.length(); i++)
        if(setn[i]=="debug") setzn[i]=QString::number(z);
        USF();
}

int pars(QChar arg){
    if (arg=='0') return 0;
    if (arg=='1') return 1;
    if (arg=='2') return 2;
    if (arg=='3') return 3;
    if (arg=='4') return 4;
    if (arg=='5') return 5;
    if (arg=='6') return 6;
    if (arg=='7') return 7;
    if (arg=='8') return 8;
    if (arg=='9') return 9;
    if ((arg=='a') or (arg=='A')) return 10;
    if ((arg=='b') or (arg=='B')) return 11;
    if ((arg=='c') or (arg=='C')) return 12;
    if ((arg=='d') or (arg=='D')) return 13;
    if ((arg=='e') or (arg=='E')) return 14;
    if ((arg=='f') or (arg=='F')) return 15;
return -1;
}

int HtD(int a1, int a2){
int dec=a1*16+a2;
return dec;
}

void MainWindow::on_lineEdit_textChanged()
{
    int r1,r2,g1,g2,b1,b2;
    QString HPP;
    HPP=ui->lineEdit->text();
    if(HPP.length()==3){
    r1=pars(HPP[0]);
    r2=r1;
    g1=pars(HPP[1]);
    g2=g1;
    b1=pars(HPP[2]);
    b2=b1;
    } else if(HPP.length()==6){
    r1=pars(HPP[0]);
    r2=pars(HPP[1]);
    g1=pars(HPP[2]);
    g2=pars(HPP[3]);
    b1=pars(HPP[4]);
    b2=pars(HPP[5]);
    }
if((HPP.length()==3) || (HPP.length()==6)){
ui->spinBox->setValue(HtD(r1,r2));
ui->spinBox_2->setValue(HtD(g1,g2));
ui->spinBox_3->setValue(HtD(b1,b2));
}
if(HPP.length()==0){
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
}
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    ui->label_6->setText(f1[index]);
}
