#include "setaxiswindow.h"
#include "ui_setaxiswindow.h"

#include "kit.h"

setAxisWindow::setAxisWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setAxisWindow)
{
    ui->setupUi(this);

    xAxisSet=26;
    yAxisSet=0.6;
    yAxis2Set=5;

}

void setAxisWindow::setup_connections()
{
    connect(this, SIGNAL(axisChangedSignal(double,double,double)), kit::get_instance(),SLOT(axisChanged(double,double,double)));
}

setAxisWindow::~setAxisWindow()
{
    delete ui;
}

void setAxisWindow::on_doubleSpinBox_V_valueChanged(double arg1)
{
    xAxisSet=arg1;
}

void setAxisWindow::on_doubleSpinBox_A_valueChanged(double arg1)
{
    yAxisSet=arg1;
}

void setAxisWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    yAxis2Set = arg1;
}

void setAxisWindow::on_buttonBox_accepted()
{
    emit axisChangedSignal(xAxisSet,yAxisSet,yAxis2Set);
    setAxisWindow::close();
}

void setAxisWindow::on_buttonBox_rejected()
{
    setAxisWindow::close();
}


