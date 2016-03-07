#include "solarpannel.h"
#include "kit.h"
#include <QtNetwork>


SolarPannel::SolarPannel(QObject *parent) :
    QObject(parent)
{
    ip_address = "192.168.1.100";
    server_port = 8080;
}

void SolarPannel::setup_connections()
{
    connect(&tcpSocket, SIGNAL(readyRead()), this,SLOT(read_pannel_data()));
    connect(this, SIGNAL(ready_toPlot()), kit::get_instance(),SLOT(plot_graph()));
}

bool SolarPannel::new_pannel_curve(ushort lum, ushort angle) // send the command to a new
{
    QByteArray pkg_out;
    pkg_out.clear();

    char * char_ptr;

    char_ptr = (char *) &angle;
    pkg_out.append(*char_ptr);
    char_ptr++;
    pkg_out.append(*char_ptr);

    char_ptr = (char *) &lum;
    pkg_out.append(*char_ptr);
    char_ptr++;
    pkg_out.append(*char_ptr);

    tcpSocket.abort();
    tcpSocket.connectToHost(ip_address,server_port);

    if(tcpSocket.waitForConnected(5000))
    {
        tcpSocket.write(pkg_out);
        return true;
    }

    return false;
}

bool SolarPannel::ping_server(void)
{

    QProcess pingProcess;
    QStringList params;
    params << "-n" << "2" << ip_address;

    pingProcess.start("ping",params,QIODevice::ReadOnly);
    pingProcess.waitForFinished(-1);

    QString p_stdout = pingProcess.readAllStandardOutput();
    QString p_stderr = pingProcess.readAllStandardError();

    if(p_stdout.contains("TTL"))
        return true;

    return false;

}

void SolarPannel::set_ipAddress(QString addr)
{
    tcpSocket.abort();
    ip_address=addr;
}

void SolarPannel::set_serverPort(int prt)
{
    tcpSocket.abort();
    server_port=prt;
}


void SolarPannel::read_pannel_data()
{
    QByteArray pkg_in;
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_3);

    analysis_pkg_union analysis;


    // Data read with memcopy and structs
    int bytes = tcpSocket.bytesAvailable();

    // check the corect Datalength
    if (bytes != sizeof(analysis.byteBuff))
    {
        in.skipRawData(tcpSocket.bytesAvailable());
        return; // or emit error signal...
    }

    pkg_in.resize(tcpSocket.bytesAvailable());

    in.readRawData(pkg_in.data(),pkg_in.size());

    memcpy(&analysis.byteBuff,pkg_in.data(),sizeof(analysis.byteBuff));

    analysis_data = analysis.dataStruct;

    emit ready_toPlot();

}

analysis_pkg_t SolarPannel::data_toPlot()
{
    return analysis_data;
}



