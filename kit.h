#ifndef KIT_H
#define KIT_H

#include <QMainWindow>
#include <QTcpSocket>

#include "solarpannel.h"
#include "setaxiswindow.h"
#include "setnetworkwindow.h"
#include "serialterminal.h"

namespace Ui {
class kit;
}

class kit : public QMainWindow
{
    Q_OBJECT

public:
    explicit kit(QWidget *parent = 0);

    Ui::kit * get_ui()
    {
        return ui;
    }
    static kit * get_instance();
    ~kit();    

    SetNetworkWindow setNetwork;
    SerialTerminal terminal;

private slots:

    //slots dos signals botões da analise
    void on_button_g1_clicked();

    void on_button_g2_clicked();

    void on_button_g3_clicked();

    void on_button_g4_clicked();


    // slots dos signals checkboxes da analise
    void on_check_g1_stateChanged(int arg1);

    void on_check_g2_stateChanged(int arg2);

    void on_check_g3_stateChanged(int arg3);

    void on_check_g4_stateChanged(int arg4);


    void on_ClrButton_1_clicked();

    void on_ClrButton_2_clicked();

    void on_ClrButton_3_clicked();

    void on_ClrButton_4_clicked();


    void on_actionDefinir_Escala_triggered();

    void on_actionRestaurar_Escala_triggered();

    void on_actionTravar_Escala_toggled(bool checked);

    void on_actionRede_triggered();


    void on_angleBox_1_valueChanged(int angle);

    void on_angleBox_2_valueChanged(int angle);

    void on_angleBox_3_valueChanged(int angle);

    void on_angleBox_4_valueChanged(int angle);


    void on_lumBox_valueChanged(int lumValue);

    void on_lumSlider_valueChanged(int value);




    void on_check_Button_clicked();

    void on_actionSerial_triggered();

    void on_check_g1_p_stateChanged(int arg1);

    void on_check_g2_p_stateChanged(int arg2);

    void on_check_g3_p_stateChanged(int arg3);

    void on_check_g4_p_stateChanged(int arg4);

public slots:

    //slot construção do gráfico
    void plot_graph();
    void clr_graph(int);

    //slot mudança de escala

    void axisChanged(double x, double y, double y2);
    void netChanged(QString ip, int port);

private:

    Ui::kit *ui;
    SolarPannel pannel;
    setAxisWindow setAxis;

    static kit * _instance;

    int channel;

    double xLenght; // x axis for voltage
    double yLenght; // y axis for current
    double y2Lenght;// y axis for power

    ushort lum;

    ushort lum_ploted_1;
    ushort lum_ploted_2;
    ushort lum_ploted_3;
    ushort lum_ploted_4;

    ushort angle_1;
    ushort angle_2;
    ushort angle_3;
    ushort angle_4;

    ushort angle_ploted_1;
    ushort angle_ploted_2;
    ushort angle_ploted_3;
    ushort angle_ploted_4;


};

#endif // KIT_H
