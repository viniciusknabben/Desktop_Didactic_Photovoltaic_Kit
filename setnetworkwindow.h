#ifndef SETNETWORKWINDOW_H
#define SETNETWORKWINDOW_H

#include <QDialog>

namespace Ui {
class SetNetworkWindow;
}

class SetNetworkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetNetworkWindow(QWidget *parent = 0);
    ~SetNetworkWindow();

    void setup_connections();

private slots:

    void on_Ok_Button_clicked();

    void on_Cancel_Button_clicked();

signals:

    void netParamChanged(QString ip_string, int port_int);

private:
    Ui::SetNetworkWindow *ui;

    bool validate_ip(void);
    bool validate_svport(void);

    QString ip;
    int port;
};

#endif // SETNETWORKWINDOW_H
