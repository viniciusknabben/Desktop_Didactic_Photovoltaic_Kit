#include "setnetworkwindow.h"
#include "ui_setnetworkwindow.h"

#include "kit.h"

SetNetworkWindow::SetNetworkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNetworkWindow)
{
    ui->setupUi(this);

    ui->Ip_lineEdit->setInputMask("000.000.000.000;");

    ui->port_lineEdit->setInputMask("00000");
}

SetNetworkWindow::~SetNetworkWindow()
{
    delete ui;
}

void SetNetworkWindow::setup_connections()
{
    connect(this, SIGNAL(netParamChanged(QString,int)),kit::get_instance(),SLOT(netChanged(QString,int)));
}


bool SetNetworkWindow::validate_ip()
{
    QString ip_string = ui->Ip_lineEdit->text();
    QStringList ip_stringList = ip_string.split(".");

    bool ok;
    int dec_value;

    for(int x = 0;x<4;x++)
    {
        if(ip_stringList[x].size() == 0)
        {
            ui->error_label->setText("Incomplete Ip Address");
            return false;
        }

        dec_value = ip_stringList[x].toInt(&ok,10);

        if(dec_value>255)
        {
            ui->error_label->setText("Invalid IP Address");
            return false;
        }

    }

    ip = ip_string;

    return true;
}

bool SetNetworkWindow::validate_svport()
{
    QString port_string = ui->port_lineEdit->text();

    bool ok = true;
    int port_input=0;

    port_input=port_string.toInt(&ok, 10);

    if(!ok)
    {
        ui->error_label->setText("Invalid Server Port");
        return false;
    }

    if(port_input>65536)
    {
        ui->error_label->setText("Invalid Server Port");
        return false;
    }

    port = port_input;
    return true;
}


void SetNetworkWindow::on_Ok_Button_clicked()
{
    // run verifier...
    if(!validate_ip())
        return;
    if(!validate_svport())
        return;

    emit netParamChanged(ip,port);
    ui->error_label->clear();
    SetNetworkWindow::close();
}

void SetNetworkWindow::on_Cancel_Button_clicked()
{
    ui->error_label->clear();
    SetNetworkWindow::close();
}

