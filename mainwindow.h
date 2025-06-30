#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick();
    void resetBoard();

private:
    QWidget *centralWidget;
    QLabel *statusLabel;
    QGridLayout *gridLayout;
    QPushButton *buttons[3][3];
    QPushButton *clearButton;

    bool isXTurn;
    void updateStatus();
    void checkWin();
};
#endif // MAINWINDOW_H

