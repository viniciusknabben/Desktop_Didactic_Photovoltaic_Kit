#ifndef SERIALTERMINAL_H
#define SERIALTERMINAL_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDataStream>
#include <QBuffer>

#define DISCONNECTED 0
#define CONNECTED    1

typedef struct
{
    unsigned char mac_addr[6];
    unsigned char gtw_addr[4];
    unsigned char sub_mask[4];
    unsigned char ip_addr[4];
    unsigned short port;

}network_parameters_t;

namespace Ui {
class SerialTerminal;
}

class SerialTerminal : public QMainWindow
{
    Q_OBJECT

public:
    explicit SerialTerminal(QWidget *parent = 0);
    ~SerialTerminal();

    void seekArduinoPort(void);

private slots:

    void on_COM_comboBox_activated(const QString &arg1);

    void on_Refresh_pushButton_clicked();

    void on_Connect_pushButton_clicked();

    void on_RestoreDefault_pushButton_clicked();

    void setupInputMasks(void);

    bool validate_MAC();

    bool validate_GTW();

    bool validate_SMSK();

    bool validate_Ip();

    bool validate_svport();

    void on_Write_pushButton_clicked();

    void readSerialData(void);

private:
    Ui::SerialTerminal *ui;

    network_parameters_t np;

    QList<QSerialPortInfo> serialPortInfoList;
    QSerialPort serial_port;

    int port_state;

};

#endif // SERIALTERMINAL_H
