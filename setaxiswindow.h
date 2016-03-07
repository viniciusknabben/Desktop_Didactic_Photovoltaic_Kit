#ifndef SETAXISWINDOW_H
#define SETAXISWINDOW_H

#include <QDialog>

namespace Ui {
class setAxisWindow;
}

class setAxisWindow : public QDialog
{
    Q_OBJECT

public:
    explicit setAxisWindow(QWidget *parent = 0);
    ~setAxisWindow();

    void setup_connections();

private slots:


    void on_buttonBox_accepted();

    void on_buttonBox_rejected();    

    void on_doubleSpinBox_V_valueChanged(double arg1);

    void on_doubleSpinBox_A_valueChanged(double arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

signals:

    void axisChangedSignal(double x,double y, double y2);

private:
    Ui::setAxisWindow *ui;

    double xAxisSet;
    double yAxisSet;
    double yAxis2Set;

};

#endif // SETAXISWINDOW_H
