#include "kit.h"
#include "ui_kit.h"

kit * kit::_instance = 0;

kit::kit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::kit)
{

    _instance = this;
    pannel.setup_connections();
    setAxis.setup_connections();
    setNetwork.setup_connections();

    ui->setupUi(this);

    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis); // cria um slot de gráfico
    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis);
    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis);
    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis);

    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis2); // cria um slot de gráfico
    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis2);
    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis2);
    ui->graficos->addGraph(ui->graficos->xAxis,ui->graficos->yAxis2);

    ui->tabela1->setRowCount(num_points);
    ui->tabela2->setRowCount(num_points);
    ui->tabela3->setRowCount(num_points);
    ui->tabela4->setRowCount(num_points);

    for(int x=0;x<num_points;x++) // preenche a tabela com QTableWidgetItem
    {
        for(int y = 0; y < 3 ; y++)
        {
            ui->tabela1->setItem(x,y,new QTableWidgetItem(""));
            ui->tabela2->setItem(x,y,new QTableWidgetItem(""));
            ui->tabela3->setItem(x,y,new QTableWidgetItem(""));
            ui->tabela4->setItem(x,y,new QTableWidgetItem(""));
        }
    }


    //ui->graficos->setInteraction(QCP::iSelectPlottables, true); // torna os graficos selecionaveis


    // Nomeia os eixos
    ui->graficos->xAxis->setLabel("Tensão(V)");
    ui->graficos->yAxis->setLabel("Corrente(A)");
    ui->graficos->yAxis2->setLabel("Potência(W)");
    ui->graficos->yAxis2->setVisible(true);

    ui->button_g1->

    xLenght=26.0;
    yLenght=0.6;

    angle_1=30;
    angle_2=45;
    angle_3=60;
    angle_4=90;

    lum=100;

    // Define a escala do grafico:
    ui->graficos->xAxis->setRange(0, xLenght);
    ui->graficos->yAxis->setRange(0, yLenght);
    ui->graficos->yAxis2->setRange(0,5);

    ui->ClrButton_1->setEnabled(false);
    ui->ClrButton_2->setEnabled(false);
    ui->ClrButton_3->setEnabled(false);
    ui->ClrButton_4->setEnabled(false);

}

kit * kit::get_instance(){
    return _instance;
}

kit::~kit()
{
    delete ui;
}


void kit::on_button_g1_clicked()
{
    channel=0;
    ui->button_g1->setEnabled(false);

    if(!pannel.new_pannel_curve(lum,angle_1))
    {
        if(pannel.ping_server())
        {
            ui->status_label->setText("Server Busy");
        }
        else
        {
            ui->status_label->setText("Server Offline");
        }
        ui->button_g1->setEnabled(true);
        return;
    }

    lum_ploted_1=lum;
    angle_ploted_1=angle_1;    

}

void kit::on_ClrButton_1_clicked() // limpa os dados da curva relacionada
{
    kit::clr_graph(0);
    ui->button_g1->setEnabled(true);
}


void kit::on_button_g2_clicked()
{
    channel=1;
    ui->button_g2->setEnabled(false);

    if(!pannel.new_pannel_curve(lum,angle_2))
    {
        if(pannel.ping_server())
        {
            ui->status_label->setText("Server Busy");
        }
        else
        {
            ui->status_label->setText("Server Offline");
        }
        ui->button_g2->setEnabled(true);
        return;
    }

    lum_ploted_2=lum;
    angle_ploted_2=angle_2;

}

void kit::on_ClrButton_2_clicked()
{
    kit::clr_graph(1);
    ui->button_g2->setEnabled(true);
}


void kit::on_button_g3_clicked()
{
    channel=2;
    ui->button_g3->setEnabled(false);

    if(!pannel.new_pannel_curve(lum,angle_3))
    {
        ui->button_g3->setEnabled(true);
        return;
    }

    lum_ploted_3=lum;
    angle_ploted_3=angle_3;

}

void kit::on_ClrButton_3_clicked()
{
    kit::clr_graph(2);
    ui->button_g3->setEnabled(true);
}


void kit::on_button_g4_clicked()
{
    channel=3;
    ui->button_g4->setEnabled(false);

    if(!pannel.new_pannel_curve(lum,angle_4))
    {
        ui->button_g4->setEnabled(true);
        return;
    }

    lum_ploted_4=lum;
    angle_ploted_4=angle_4;

}

void kit::on_ClrButton_4_clicked()
{
    kit::clr_graph(3);
    ui->button_g4->setEnabled(true);
}


// Angle Box

void kit::on_angleBox_1_valueChanged(int angle)
{
    angle_1=(ushort)angle;
}

void kit::on_angleBox_2_valueChanged(int angle)
{
    angle_2=(ushort)angle;
}

void kit::on_angleBox_3_valueChanged(int angle)
{
    angle_3=(ushort)angle;
}

void kit::on_angleBox_4_valueChanged(int angle)
{
    angle_4=(ushort)angle;
}

// ////////////////////////////

// Lum Box

void kit::on_lumBox_valueChanged(int lumValue)
{
    lum = (ushort)lumValue;
    ui->lumSlider->setValue(lumValue);
}

void kit::on_lumSlider_valueChanged(int lumValue)
{
    lum =(ushort)lumValue;
    ui->lumBox->setValue(lumValue);
}


// Check box: Habilitam gráficos

void kit::on_check_g1_stateChanged(int arg1)
{
    ui->graficos->graph(0)->setVisible((arg1 == Qt::Checked)); // arg1 = 0 (unchecked) arg1 = 2 (checked) / compara com Qt::Checked(definido como 2) e retorna false ou true
    ui->graficos->replot();
}

void kit::on_check_g1_p_stateChanged(int arg1)
{
    ui->graficos->graph(0+4)->setVisible((arg1 == Qt::Checked));
    ui->graficos->replot();
}


void kit::on_check_g2_stateChanged(int arg2)
{
    ui->graficos->graph(1)->setVisible((arg2 == Qt::Checked));
    ui->graficos->replot();
}

void kit::on_check_g2_p_stateChanged(int arg2)
{
    ui->graficos->graph(1+4)->setVisible((arg2 == Qt::Checked));
    ui->graficos->replot();
}

void kit::on_check_g3_stateChanged(int arg3)
{
    ui->graficos->graph(2)->setVisible((arg3 == Qt::Checked));
    ui->graficos->replot();
}

void kit::on_check_g3_p_stateChanged(int arg3)
{
    ui->graficos->graph(2+4)->setVisible((arg3 == Qt::Checked));
    ui->graficos->replot();
}

void kit::on_check_g4_stateChanged(int arg4)
{
    ui->graficos->graph(3)->setVisible((arg4 == Qt::Checked));
    ui->graficos->replot();
}

void kit::on_check_g4_p_stateChanged(int arg4)
{
    ui->graficos->graph(3+4)->setVisible((arg4 == Qt::Checked));
    ui->graficos->replot();
}


// ///////////////////////////


// Graph

void kit::plot_graph()
{   
    analysis_pkg_t analysis = pannel.data_toPlot();

    QVector<double> vp_plot;
    QVector<double> ip_plot;
    QVector<double> pp_plot;
    double mp = 0;

    vp_plot.resize(num_points);
    ip_plot.resize(num_points);
    pp_plot.resize(num_points);

    switch(channel)
    {
    case 0:

        ui->check_g1->setCheckState(Qt::Checked);
        ui->check_g1_p->setCheckState(Qt::Checked);
        ui->graficos->graph(channel)->setPen(QPen(Qt::blue));
        ui->graficos->graph(channel+4)->setPen(QPen(Qt::blue));
        ui->ClrButton_1->setEnabled(true);


        for(int x=0;x<num_points;x++) // preenche a tabela com os dados
        {

            vp_plot[x]=analysis.vp[x]*(analysis.vcoef);
            ip_plot[x]=analysis.ip[x]*(analysis.icoef);
            pp_plot[x]=vp_plot[x]*ip_plot[x];

            if((x>0) & (pp_plot[x] > pp_plot[x-1]))
                mp=pp_plot[x];

            ui->tabela1->item(x,0)->setText(QString::number(vp_plot[x]));
            ui->tabela1->item(x,1)->setText(QString::number(ip_plot[x]));
            ui->tabela1->item(x,2)->setText(QString::number(vp_plot[x]*ip_plot[x]));

        }

        ui->label_t1->setText(QString::number(analysis.tp*analysis.tcoef,'f',2)); // atualiza o grafico com o valor da temperatura
        ui->label_a1->setText(QString::number(angle_ploted_1)); // atualiza o grafico com o angulo
        ui->label_l1->setText(QString::number(lum_ploted_1)); // atualiza o grafico com o a luminosidade
        ui->label_p1->setText(QString::number(mp,'f',2));

        ui->tabWidget->setCurrentIndex(0);
        break;

    case 1:

        ui->check_g2->setCheckState(Qt::Checked);
        ui->check_g2_p->setCheckState(Qt::Checked);
        ui->graficos->graph(channel)->setPen(QPen(Qt::red));
        ui->graficos->graph(channel+4)->setPen(QPen(Qt::red));
        ui->ClrButton_2->setEnabled(true);

        for(int x=0;x<num_points;x++)
        {

            vp_plot[x]=analysis.vp[x]*(analysis.vcoef);
            ip_plot[x]=analysis.ip[x]*(analysis.icoef);
            pp_plot[x]=vp_plot[x]*ip_plot[x];

            if((x>0) & (pp_plot[x] > pp_plot[x-1]))
                mp=pp_plot[x];

            ui->tabela2->item(x,0)->setText(QString::number(vp_plot[x]));
            ui->tabela2->item(x,1)->setText(QString::number(ip_plot[x]));
            ui->tabela2->item(x,2)->setText(QString::number(vp_plot[x]*ip_plot[x]));

        }

        ui->label_t2->setText(QString::number(analysis.tp*analysis.tcoef,'f',2));
        ui->label_a2->setText(QString::number(angle_ploted_2));
        ui->label_l2->setText(QString::number(lum_ploted_2));
        ui->label_p2->setText(QString::number(mp,'f',2));

        ui->tabWidget->setCurrentIndex(1);
        break;

    case 2:

        ui->check_g3->setCheckState(Qt::Checked);
        ui->check_g3_p->setCheckState(Qt::Checked);
        ui->graficos->graph(channel)->setPen(QPen(Qt::green));
        ui->graficos->graph(channel+4)->setPen(QPen(Qt::green));
        ui->ClrButton_3->setEnabled(true);

        for(int x=0;x<num_points;x++)
        {

            vp_plot[x]=analysis.vp[x]*(analysis.vcoef);
            ip_plot[x]=analysis.ip[x]*(analysis.icoef);
            pp_plot[x]=vp_plot[x]*ip_plot[x];

            if((x>0) & (pp_plot[x] > pp_plot[x-1]))
                mp=pp_plot[x];

            ui->tabela3->item(x,0)->setText(QString::number(vp_plot[x]));
            ui->tabela3->item(x,1)->setText(QString::number(ip_plot[x]));
            ui->tabela3->item(x,2)->setText(QString::number(vp_plot[x]*ip_plot[x]));

        }

        ui->label_t3->setText(QString::number(analysis.tp*analysis.tcoef,'f',2));
        ui->label_a3->setText(QString::number(angle_ploted_3));
        ui->label_l3->setText(QString::number(lum_ploted_3));
        ui->label_p3->setText(QString::number(mp,'f',2));

        ui->tabWidget->setCurrentIndex(2);
        break;

    case 3:

        ui->check_g4->setCheckState(Qt::Checked);
        ui->check_g4_p->setCheckState(Qt::Checked);
        ui->graficos->graph(channel)->setPen(QPen(Qt::black));
        ui->graficos->graph(channel+4)->setPen(QPen(Qt::black));
        ui->ClrButton_4->setEnabled(true);

        for(int x=0;x<num_points;x++)
        {

            vp_plot[x]=analysis.vp[x]*(analysis.vcoef);
            ip_plot[x]=analysis.ip[x]*(analysis.icoef);
            pp_plot[x]=vp_plot[x]*ip_plot[x];

            if((x>0) & (pp_plot[x] > pp_plot[x-1]))
                mp=pp_plot[x];

            ui->tabela4->item(x,0)->setText(QString::number(vp_plot[x]));
            ui->tabela4->item(x,1)->setText(QString::number(ip_plot[x]));
            ui->tabela4->item(x,2)->setText(QString::number(vp_plot[x]*ip_plot[x]));

        }

        ui->label_t4->setText(QString::number(analysis.tp*analysis.tcoef,'f',2));
        ui->label_a4->setText(QString::number(angle_ploted_4));
        ui->label_l4->setText(QString::number(lum_ploted_4));
        ui->label_p4->setText(QString::number(mp,'f',2));

        ui->tabWidget->setCurrentIndex(3);
        break;
    }

    ui->graficos->graph(channel)->setData(vp_plot, ip_plot);
    ui->graficos->graph(channel+4)->setData(vp_plot, pp_plot);
    ui->graficos->replot();

    ui->status_label->setText("-");
}

void kit::clr_graph(int channel)
{

    switch(channel) //desabilita botao clear
    {
        case 0:

            ui->ClrButton_1->setEnabled(false);
            ui->check_g1->setChecked(false);
            ui->check_g1_p->setChecked(false);

            ui->label_l1->setText("-");
            ui->label_t1->setText("-");
            ui->label_a1->setText("-");
            ui->label_p1->setText("-");

            for(int x=0;x<num_points;x++)
            {
                ui->tabela1->item(x,0)->setText("");
                ui->tabela1->item(x,1)->setText("");
                ui->tabela1->item(x,2)->setText("");
            }
        break;

        case 1:

            ui->ClrButton_2->setEnabled(false);
            ui->check_g2->setChecked(false);
            ui->check_g2_p->setChecked(false);

            ui->label_l2->setText("-");
            ui->label_t2->setText("-");
            ui->label_a2->setText("-");
            ui->label_p2->setText("-");

            for(int x=0;x<num_points;x++)
            {
                ui->tabela2->item(x,0)->setText("");
                ui->tabela2->item(x,1)->setText("");
                ui->tabela2->item(x,2)->setText("");
            }
        break;

        case 2:

            ui->ClrButton_3->setEnabled(false);
            ui->check_g3->setChecked(false);
            ui->check_g3_p->setChecked(false);

            ui->label_l3->setText("-");
            ui->label_t3->setText("-");
            ui->label_a3->setText("-");
            ui->label_p3->setText("-");

            for(int x=0;x<num_points;x++)
            {
                ui->tabela3->item(x,0)->setText("");
                ui->tabela3->item(x,1)->setText("");
                ui->tabela3->item(x,2)->setText("");
            }
        break;

        case 3:

            ui->ClrButton_4->setEnabled(false);
            ui->check_g4->setChecked(false);
            ui->check_g4_p->setChecked(false);

            ui->label_l4->setText("-");
            ui->label_t4->setText("-");
            ui->label_a4->setText("-");
            ui->label_p4->setText("-");

            for(int x=0;x<num_points;x++)
            {
                ui->tabela4->item(x,0)->setText("");
                ui->tabela4->item(x,1)->setText("");
                ui->tabela4->item(x,2)->setText("");
            }
        break;
    }       

    ui->graficos->graph(channel)->clearData();
    ui->graficos->graph(channel+4)->clearData();
    ui->graficos->replot();

}


/* Menu */

//Gráfico

void kit::on_actionRestaurar_Escala_triggered()
{
    ui->graficos->xAxis->setRange(0, xLenght);
    ui->graficos->yAxis->setRange(0, yLenght);
    ui->graficos->yAxis2->setRange(0, y2Lenght);
    ui->graficos->replot();    
}

void kit::on_actionTravar_Escala_toggled(bool checked)
{
    if(checked)
    {
        ui->graficos->setInteraction(QCP::iRangeDrag, false);
        ui->graficos->setInteraction(QCP::iRangeZoom, false);
    }
    else
    {
        ui->graficos->setInteraction(QCP::iRangeDrag, true);
        ui->graficos->setInteraction(QCP::iRangeZoom, true);
    }

}

void kit::on_actionDefinir_Escala_triggered()
{
    setAxis.show();
}

void kit::axisChanged(double x, double y, double y2)
{
    xLenght=x;
    yLenght=y;
    y2Lenght=y2;
    kit::on_actionRestaurar_Escala_triggered();
}

// Network

void kit::on_actionRede_triggered()
{
    setNetwork.show();
}

void kit::netChanged(QString ip, int port)
{
    pannel.set_ipAddress(ip);
    ui->ipvalue_label->setText(ip);

    pannel.set_serverPort(port);
    ui->portvalue_label->setText(QString::number(port));

}

// Serial

void kit::on_actionSerial_triggered()
{
    terminal.show();
}

// ///////////////////////////


void kit::on_check_Button_clicked()
{

    if(pannel.ping_server())
        ui->status_label->setText("Server Online");
    else
        ui->status_label->setText("Server Offline");
}

