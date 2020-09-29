#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QInputDialog>
#include <QMouseEvent>
#include <QtNetwork>
#include <QPainter>
#include <QUrl>
#include <QSgml/QSgml.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <iostream>
#include <sstream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:

public:
    MainWindow(QWidget *parent = nullptr);
    bool eventFilter(QObject *object, QEvent *event);
    ~MainWindow();

public slots:
    void update_ball_data();

private slots:
    void on_actionSet_Server_IP_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *update_timer;
    std::string server_ip_addr;
};
#endif // MAINWINDOW_H
