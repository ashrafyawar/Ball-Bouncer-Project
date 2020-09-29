#include "mainwindow.h"
#include "ui_mainwindow.h"

// 3rd Party
#include "HTTPRequest.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(QSize(500, 500));
    ui->MainArea->setDrawData(0, 0, 0);
}

bool MainWindow::eventFilter(QObject *object Q_DECL_UNUSED, QEvent *event) {
    return false;
}

void MainWindow::update_ball_data() {
    // Prepare and send
    http::Request request("http://" + this->server_ip_addr + "/ball");
    const http::Response response = request.send("GET");
    std::string body_content = std::string(response.body.begin(), response.body.end());

    // Tokenize
    std::vector<std::string> tokens;
    std::istringstream f(body_content);
    std::string s;
    while (getline(f, s, ',')) {
        tokens.push_back(s);
    }

    int ball_x = std::stod(tokens[0]);
    int ball_y = std::stod(tokens[1]);
    float ball_radius = std::stof(tokens[2]);

    ui->MainArea->setDrawData(ball_x, ball_y, ball_radius);
}

MainWindow::~MainWindow() {
    delete update_timer;
    delete ui;
}

void MainWindow::on_actionSet_Server_IP_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Server Info"), tr("Server IP and PORT:"), QLineEdit::Normal, "IP:PORT", &ok);
    if (ok && !text.isEmpty()) {
        std::cout << "Input given is: " << text.toStdString() << std::endl;
    }

    this->server_ip_addr = text.toStdString();

    update_timer = new QTimer(this);
    connect(update_timer, SIGNAL(timeout()), this, SLOT(update_ball_data()));
    update_timer->start(100);

    ui->menuBar->setEnabled(false);
    ui->EnterIPLabel->setVisible(false);
}
