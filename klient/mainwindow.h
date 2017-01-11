#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
    class MainWindow;
    class QRect;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
    protected:
        void paintEvent(QPaintEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void checkGame();
        void cleanBoard();
    private:
        Ui::MainWindow *ui;
        QTcpSocket *tcpSocket;
        QRect rects[401];
        int plansza[20][20];
        int N = 20;
        int M = 400;
        int playerId;
        int miejsceRuchuX;
        int miejsceRuchuY;
        int permissionToMove = 0; //0-nie można wykonać ruchu, 1-można wykonać ruch, 2-ruch został wykonany
        int match = 0;
        int stageOne = 0;
        int stageTwo = 0;
        int onlyOne = 0;
        int moves = 0;  //zlicza liczbę ruchów w grze
        int opponentWin;
        int wygranaX[10];   //współrzędne X wygranych ruchów
        int wygranaY[10];   //współrzędne Y wygranych ruchów
        int myWin;
        char cbBuf[24];


    private slots:
        void readyRead();
        void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
