#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isXTurn(true) {
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QVBoxLayout *vLayout = new QVBoxLayout;
    statusLabel = new QLabel("Player: X");
    gridLayout = new QGridLayout;

    // 创建按钮
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col] = new QPushButton("");
            buttons[row][col]->setFixedSize(80, 80);
            buttons[row][col]->setFont(QFont("Arial", 24));
            connect(buttons[row][col], &QPushButton::clicked, this, &MainWindow::handleButtonClick);
            gridLayout->addWidget(buttons[row][col], row, col);
        }
    }

    // 重置按钮
    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::resetBoard);

    vLayout->addWidget(statusLabel);
    vLayout->addLayout(gridLayout);
    vLayout->addWidget(clearButton);
    centralWidget->setLayout(vLayout);
}

MainWindow::~MainWindow() {}

void MainWindow::handleButtonClick() {
    QPushButton *clicked = qobject_cast<QPushButton *>(sender());
    if (clicked->text() != "") return;

    clicked->setText(isXTurn ? "X" : "O");
    checkWin();
    isXTurn = !isXTurn;
    updateStatus();
}

void MainWindow::resetBoard() {
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            buttons[row][col]->setText("");

    isXTurn = true;
    updateStatus();
}

void MainWindow::updateStatus() {
    statusLabel->setText(QString("Player: %1").arg(isXTurn ? "X" : "O"));
}

void MainWindow::checkWin() {
    QString winner = "";

    // 检查行列对角
    for (int i = 0; i < 3; ++i) {
        if (buttons[i][0]->text() != "" &&
            buttons[i][0]->text() == buttons[i][1]->text() &&
            buttons[i][1]->text() == buttons[i][2]->text())
            winner = buttons[i][0]->text();

        if (buttons[0][i]->text() != "" &&
            buttons[0][i]->text() == buttons[1][i]->text() &&
            buttons[1][i]->text() == buttons[2][i]->text())
            winner = buttons[0][i]->text();
    }

    if (buttons[0][0]->text() != "" &&
        buttons[0][0]->text() == buttons[1][1]->text() &&
        buttons[1][1]->text() == buttons[2][2]->text())
        winner = buttons[0][0]->text();

    if (buttons[0][2]->text() != "" &&
        buttons[0][2]->text() == buttons[1][1]->text() &&
        buttons[1][1]->text() == buttons[2][0]->text())
        winner = buttons[0][2]->text();

    if (!winner.isEmpty()) {
        QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(winner));
        resetBoard();
    }
}

