#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include "plotter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
    /**
   * @brief MainWindow Conecta e desconecta os botões
   * @param parent
   */
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
    /**
   * @brief tcpConnect Conecta ao host do servidor
   */
  void tcpConnect();
  /**
   * @brief getData Inicia e finaliza o temporizador
   */
  void getData();
  /**
   * @brief tcpDisconnect Disconecta o host do servidor
   */
  void tcpDisconnect();
  /**
   * @brief update Lista os IPs conectados
   */
  void update();
  /**
   * @brief stopData Finaliza o envio de dados
   */
  void stopData();
  /**
   * @brief timerEvent Envia os dados periodicamentodo servidor para consumidor
   * @param e
   */
  void timerEvent(QTimerEvent *e);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  int time;
};

#endif // MAINWINDOW_H
