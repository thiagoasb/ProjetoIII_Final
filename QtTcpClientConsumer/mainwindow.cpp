#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "plotter.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  tcpConnect();

  connect(ui->pushButtonGet,
          SIGNAL(clicked(bool)),
          this,
          SLOT(getData()));
  connect(ui->PushButton_Connect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));
  connect(ui->PushButton_Disconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));
  connect(ui->PushButton_Stop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopData()));
  connect(ui->pushButtonPut,
          SIGNAL(clicked(bool)),
          this,
          SLOT(update()));

}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->lineEditIP->text(),1234);
  if(socket->waitForConnected()){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::timerEvent(QTimerEvent *e){
  QString str;
  QByteArray array;
  QStringList list;
  qint64 thetime, n;
  double abmin,abmax,ordmin,ordmax;
  vector<double> time;
  vector<double> data;
  vector<double> tempos;
  vector<double> dados;

  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      str = "get " + ui->listWidget_2->currentItem()->text() + " 30\r\n";
      socket->write(str.toStdString().c_str());
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      time.clear();
      data.clear();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = str.toLongLong(&ok);
          time.push_back(thetime);
          str = list.at(1);
          n = str.toLongLong(&ok);
          data.push_back(n);
          qDebug() << thetime << ": " << str;
        }
      }
    }
  }

  qDebug()<<data.size()<<time.size();
  abmax = time[0], abmin = time[0];
  ordmin = data[0], ordmax = data[0];

  for(int i=1; i<30; i++){
      if(time[i]<abmin){
          abmin=time[i];
      }
      else if(time[i] >abmax){
          abmax=time[i];
      }
      if(data[i] <ordmin){
          ordmin=data[i];
      }
      else if(data[i]>ordmax){
          ordmax=data[i];
      }
  }
  qDebug()<<abmax-abmin;
  qDebug()<<ordmax-ordmin;

  tempos.clear();
  dados.clear();
  for(int i=0; i<30; i++){
      tempos.push_back((time[i]-abmin)/(abmax-abmin));
      dados.push_back((data[i]-ordmin)/(ordmax-ordmin));
  }
  qDebug()<<"ok";
  ui->widget_draw->loadData(tempos,dados);

}

void MainWindow::getData(){
    if(time){
        killTimer(time);
    }
    time = startTimer(ui->timing_slider->value()*1000);
}


void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
}

void MainWindow::stopData(){
    if(time){
        killTimer(time);
    }
}

void MainWindow::update()
{
    QString str;
    ui->listWidget_2->clear();
    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->write("list\r\n");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        while(socket->bytesAvailable()){
            str = socket->readLine().replace("\n","").replace("\r","");
            ui->listWidget_2->addItem((str));
        }
    }
    else{
        ui->listWidget_2->addItem("Nothing");
    }
}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
