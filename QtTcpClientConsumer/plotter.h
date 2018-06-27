#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QWidget>
#include <vector>

using namespace std;
class Plotter: public QWidget
{
    Q_OBJECT

private:
    vector<double> tempos;
    vector<double> dados;
    float time;
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void loadData(vector<double>,vector<double>);
};

#endif // PLOTTER_H
