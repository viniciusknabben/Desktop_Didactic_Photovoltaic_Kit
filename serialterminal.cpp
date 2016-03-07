#include "serialterminal.h"
#include "ui_serialterminal.h"

SerialTerminal::SerialTerminal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SerialTerminal)
{
    ui->setupUi(this);
    ui->Connect_pushButton->setEnabled(false); // disable connect button
    ui->Write_pushButton->setEnabled(false);
    port_state = DISCONNECTED;

    setupInputMasks();

    connect(&serial_port, SIGNAL(readyRead()), this, SLOT(readSerialData()));

}

SerialTerminal::~SerialTerminal()
{
    delete ui;
}

void SerialTerminal::setupInputMasks(void)
{

    ui->MAC_lineEdit->setInputMask("HH-HH-HH-HH-HH-HH;");

    ui->GTW_lineEdit->setInputMask("000.000.000.000;");

    ui->SMSK_lineEdit->setInputMask("000.000.000.000;");

    ui->IP_lineEdit->setInputMask("000.000.000.000;");

    ui->PORT_lineEdit->setInputMask("00000");

}

// Seek for available "Arduino Uno" connected and fill combo box with they COM numbers
void SerialTerminal::seekArduinoPort(void)
{
    ui->COM_comboBox->clear();
    serialPortInfoList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList)
    {
        if(serialPortInfo.description() == "Arduino Uno")
        {
            ui->COM_comboBox->addItem(serialPortInfo.portName());
        }
    }

    if(!ui->COM_comboBox->count())
    {
        ui->Connect_pushButton->setEnabled(false);
        ui->textBrowser->append("Arduino Uno devices not fund");
    }

}

//Handle the combo box selections from the user
void SerialTerminal::on_COM_comboBox_activated(const QString &arg1)
{
    seekArduinoPort();
    foreach (const QSerialPortInfo &serialPortInfo, serialPortInfoList)
    {
        if(serialPortInfo.portName() == arg1)
        {
            serial_port.setPort(serialPortInfo);

            ui->Connect_pushButton->setEnabled(true);
            ui->textBrowser->append("Arduino Uno Device Assigned on " + serial_port.portName());
            ui->textBrowser->append("Baud rate: " + QString::number(serial_port.baudRate()));
            return;
        }
    }
}

// refresh the combo box
void SerialTerminal::on_Refresh_pushButton_clicked()
{
    seekArduinoPort();
}

// connect with Arduino device
void SerialTerminal::on_Connect_pushButton_clicked()
{
    switch(port_state)
    {
        case DISCONNECTED:
        if(serial_port.open(QIODevice::ReadWrite))
        {
            ui->textBrowser->append("Connected!");
            ui->Connect_pushButton->setText("Disconnect");
            ui->COM_comboBox->setEnabled(false);
            port_state = CONNECTED;
            ui->Write_pushButton->setEnabled(true);
        }
        else
        {
            ui->textBrowser->append(serial_port.errorString());
            seekArduinoPort();
        }
        return;

        case CONNECTED:
        serial_port.close();
        ui->textBrowser->append("Disconnected!");
        ui->Connect_pushButton->setText("Connect");
        ui->COM_comboBox->setEnabled(true);
        port_state = DISCONNECTED;
        ui->Write_pushButton->setEnabled(false);
        return;
    }


}

// Validators //

// MAC //
bool SerialTerminal::validate_MAC()
{
    QString mac_string = ui->MAC_lineEdit->text();
    QStringList mac_stringList = mac_string.split("-");

    bool ok = true;
    int hex_value;

    for(int x = 0;x<6;x++)
    {
        if(mac_stringList[x].size() != 2)
        {
            ui->textBrowser->append("Incomplete MAC Address");
            return false;
        }

        hex_value = mac_stringList[x].toInt(&ok,16);
        np.mac_addr[x] = (unsigned char) hex_value;

    }

    ui->textBrowser->append("MAC Address: " + QString::number(np.mac_addr[0],16).toUpper() + "-"
                                            + QString::number(np.mac_addr[1],16).toUpper() + "-"
                                            + QString::number(np.mac_addr[2],16).toUpper() + "-"
                                            + QString::number(np.mac_addr[3],16).toUpper() + "-"
                                            + QString::number(np.mac_addr[4],16).toUpper() + "-"
                                            + QString::number(np.mac_addr[5],16).toUpper());
    return true;
}

// Gateway //
bool SerialTerminal::validate_GTW()
{
    QString gtw_string = ui->GTW_lineEdit->text();
    QStringList gtw_stringList = gtw_string.split(".");

    bool ok;
    int dec_value;

    for(int x = 0;x<4;x++)
    {
        if(gtw_stringList[x].size() == 0)
        {
            ui->textBrowser->append("Incomplete Gateway Address");
            return false;
        }

        dec_value = gtw_stringList[x].toInt(&ok,10);

        if(dec_value>255)
        {
            ui->textBrowser->append("Invalid Gateway Address");
            return false;
        }

        np.gtw_addr[x] = (unsigned char) dec_value;

    }

    ui->textBrowser->append("Gateway Address: " + QString::number(np.gtw_addr[0]) + "."
                                                + QString::number(np.gtw_addr[1]) + "."
                                                + QString::number(np.gtw_addr[2]) + "."
                                                + QString::number(np.gtw_addr[3]));
    return true;
}

// Sub Mask //
bool SerialTerminal::validate_SMSK()
{
    QString smsk_string = ui->SMSK_lineEdit->text();
    QStringList smsk_stringList = smsk_string.split(".");

    bool ok;
    int dec_value;

    for(int x = 0;x<4;x++)
    {
        if(smsk_stringList[x].size() == 0)
        {
            ui->textBrowser->append("Incomplete Sub Mask Network");
            return false;
        }

        dec_value = smsk_stringList[x].toInt(&ok,10);

        if(dec_value != 255 && dec_value != 0)
        {
            ui->textBrowser->append("Invalid Sub Mask Network");
            return false;
        }

        np.sub_mask[x] = (unsigned char) dec_value;
    }

    ui->textBrowser->append("Sub-Net Mask: " + QString::number(np.sub_mask[0]) + "."
                                             + QString::number(np.sub_mask[1]) + "."
                                             + QString::number(np.sub_mask[2]) + "."
                                             + QString::number(np.sub_mask[3]));
    return true;
}

//  Ip  //
bool SerialTerminal::validate_Ip()
{
    QString ip_string = ui->IP_lineEdit->text();
    QStringList ip_stringList = ip_string.split(".");

    bool ok;
    int dec_value;

    for(int x = 0;x<4;x++)
    {
        if(ip_stringList[x].size() == 0)
        {
            ui->textBrowser->append("Incomplete Ip Address");
            return false;
        }

        dec_value = ip_stringList[x].toInt(&ok,10);

        if(dec_value>255)
        {
            ui->textBrowser->append("Invalid IP Address");
            return false;
        }

        np.ip_addr[x] = (unsigned char) dec_value;

    }

    ui->textBrowser->append("Ip Address: " + QString::number(np.ip_addr[0]) + "."
                                           + QString::number(np.ip_addr[1]) + "."
                                           + QString::number(np.ip_addr[2]) + "."
                                           + QString::number(np.ip_addr[3]));

    return true;
}

// Port //
bool SerialTerminal::validate_svport()
{
    QString port_string;
    port_string=ui->PORT_lineEdit->text();

    bool ok = true;
    int port_input=0;

    port_input=port_string.toInt(&ok, 10);

    if(!ok)
    {
        ui->textBrowser->append("Invalid Server Port");
        return false;
    }

    if(port_input>65536)
    {
        ui->textBrowser->append("Invalid Server Port");
        ui->textBrowser->append("Choose a value between 0 to 65535");
        return false;
    }
    else
    {
        np.port=port_input;
    }

    ui->textBrowser->append("Port Number: " + QString::number(np.port));
    return true;
}

// Restore defaults button //
void SerialTerminal::on_RestoreDefault_pushButton_clicked()
{
    ui->MAC_lineEdit->setText("de-ad-be-ef-fe-ed");
    np.mac_addr[0] = 0xde;
    np.mac_addr[1] = 0xad;
    np.mac_addr[2] = 0xbe;
    np.mac_addr[3] = 0xef;
    np.mac_addr[4] = 0xfe;
    np.mac_addr[5] = 0xed;

    ui->GTW_lineEdit->setText("192.168.1.1");
    np.gtw_addr[0] = 192;
    np.gtw_addr[1] = 168;
    np.gtw_addr[2] = 1;
    np.gtw_addr[3] = 1;

    ui->SMSK_lineEdit->setText("255.255.255.0");
    np.sub_mask[0] = 255;
    np.sub_mask[1] = 255;
    np.sub_mask[2] = 255;
    np.sub_mask[3] = 0;

    ui->IP_lineEdit->setText("192.168.1.100");
    np.ip_addr[0] = 192;
    np.ip_addr[1] = 168;
    np.ip_addr[2] = 1;
    np.ip_addr[3] = 100;

    ui->PORT_lineEdit->setText("80");
    np.port = 80;

}

void SerialTerminal::on_Write_pushButton_clicked()
{
    ui->textBrowser->append("\n\nVerifying Parameters...\n");
    if(!validate_MAC())
        return;

    if(!validate_GTW())
        return;

    if(!validate_SMSK())
        return;

    if(!validate_Ip())
        return;

    if(!validate_svport())
        return;

     ui->textBrowser->append("\nAll Network Parameters Verified\n");

     QByteArray tx_buff;
     char * char_ptr = (char *) &np;

     for(unsigned int x = 0; x < sizeof(network_parameters_t); x++)
     {
         tx_buff.append(*char_ptr);
         char_ptr++;
     }

     serial_port.write(tx_buff,sizeof(network_parameters_t));

     ui->textBrowser->append("Sending Data...\n");

}

void SerialTerminal::readSerialData(void)
{
    static QByteArray rx_buff;
    QList<QByteArray> line_list;

    if(serial_port.bytesAvailable())
        rx_buff += serial_port.readAll();

    line_list = rx_buff.split('\n');

    int x;
    for(x = 0; x < line_list.size()-1; x++)
    {
        ui->textBrowser->append(line_list.at(x));
    }

    if(line_list.at(x).contains('\n'))
    {
        ui->textBrowser->append(line_list.at(x));
        rx_buff.clear();
    }
    else
    {
        rx_buff.clear();
        rx_buff.append(line_list.at(x));
    }


}

