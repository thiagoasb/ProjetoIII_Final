#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

#include <QTimerEvent>

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
    /**
     * @brief min valor mínimo da data
     * @brief max valor máximo da data
     * @brief iniciaTemporalizador Inicia a contagem para envio de dados
     */
    int min,max,iniciaTemporalizador;
    /**
     * @brief timerEvent Envia os dados para produtor e servidor periodicamente
     * @param event
     */
    void timerEvent(QTimerEvent *event);
public slots:
    /**
     * @brief putData Transforma o tempo em segundos e inicia o temporizador para envio de dados
     */
    void putData();
    /**
     * @brief tcpConnect Conecta ao host do servidor
     */
    void tcpConnect();
    /**
     * @brief tcpDisconect Disconecta o host do servidor
     */
    void tcpDisconect();
    /**
     * @brief pararEnvio Finaliza o envio de dados
     */
    void pararEnvio();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
