#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    tcpConnect();

    connect(ui->pushButtonPut,
            SIGNAL(clicked(bool)),
            this,
            SLOT(putData()));
    connect(ui->PushButton_Connect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));
    connect(ui->PushButton_Disconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconect()));
    // conectei a função pararEnvio ao PushButton_Stop diretamente na interface
    /*connect(ui->PushButton_Stop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(pararEnvio()));
            */
}

void MainWindow::tcpConnect(){
    socket->connectToHost(ui->lineEditIP->text(),1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::tcpDisconect()
{
    socket->disconnectFromHost();
}

void MainWindow::pararEnvio()
{
    //mata o temporarilazador
    killTimer(iniciaTemporalizador);
}

void MainWindow::timerEvent(QTimerEvent *event){
    //essa funcao tem como funcao enviar dados para o servidor periodicamente e para o produtor
    QDateTime datetime;
    QString str;
    qint64 msecdate;
    min=ui->lcd_Min->value();
    max=ui->lcd_max->value();
    int i=0;
    if(min<max){
        if(socket->state()== QAbstractSocket::ConnectedState){
            msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
            str = "set "+ QString::number(msecdate) + " " + QString::number(qrand()%(max-min)+min)+"\r\n";
            ui->textBrowser->append(str);
            qDebug() << str;
            qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
            if(socket->waitForBytesWritten(3000)){
                qDebug() << "wrote";
                i++;
            }
        }
    }

}
void MainWindow::putData(){
    // a variavel intetervaloDeTempo pega o valor da label_tempo
    QString intetervaloDeTempo;
    intetervaloDeTempo = ui->label_tempo->text();
    // a variavel iniciaTemporalizador recebe startTimer que uma função que inicia o temporalizador
    // ao inicializar o temporalizador a funcao timeEvent é ativada depois do tempo inicial
    iniciaTemporalizador = startTimer((intetervaloDeTempo.toInt())*1000);
}

MainWindow::~MainWindow(){
    delete socket;
    delete ui;
}

