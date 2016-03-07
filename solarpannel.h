#ifndef SOLARPANNEL_H
#define SOLARPANNEL_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

#define num_points 200	// Number of points of the graph

typedef struct
{
    float vcoef;
    float icoef;
    float tcoef;
    ushort vp[num_points];
    ushort ip[num_points];
    ushort tp;

}analysis_pkg_t;

typedef union
{
    char byteBuff [3*sizeof(float) + 2*num_points*sizeof(ushort) + sizeof(ushort)];
    analysis_pkg_t dataStruct;

}analysis_pkg_union;


class SolarPannel : public QObject
{
    Q_OBJECT

public:

    explicit SolarPannel(QObject *parent = 0);

    // Setup Signals/Slots with UI class KIT
    void setup_connections();

    bool new_pannel_curve(ushort lum, ushort angle);

    //network classes
    bool ping_server(void);
    void set_ipAddress(QString ip_addr);
    void set_serverPort(int sv_port);


    analysis_pkg_t data_toPlot();

signals:

    void ready_toPlot();

public slots:

private slots:

     void read_pannel_data();

private:

    analysis_pkg_t analysis_data;

    QTcpSocket tcpSocket;
    QString ip_address;
    int server_port;

};

#endif // SOLARPANNEL_H
