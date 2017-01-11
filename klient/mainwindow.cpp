#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <iostream>
#include <QtNetwork>
#include <fstream>

void MainWindow::checkGame() //procedura sprawdzająca czy gracz wygrał
{
    int piatka = 1; //zmienna zliczająca czy było min 5 w "rzędzie"
    //przypisanie miejsca ostatniego ruchu do zmiennych pomocniczych
    int gdzieX = miejsceRuchuX; //współrzędna X na planszy
    int gdzieY = miejsceRuchuY; //współrzędna Y na planszy
    int w = 1;

    //zerowanie tablic zwycięskich ruchów
    for(int i = 1; i < 10; i++)
    {
        wygranaX[i] = -1;
        wygranaY[i] = -1;
    }
    wygranaX[0] = gdzieX;
    wygranaY[0] = gdzieY;

    //sprawdzam na lewo od aktualnego ruchu
    for(int i = 0; i < 4; i++)
    {
        gdzieY -= 1;
        if(gdzieY >= 0 && gdzieY <= 19 && plansza[gdzieX][gdzieY] == playerId)
        {
            piatka += 1;
            wygranaX[w] = gdzieX;
            wygranaY[w] = gdzieY;;
            w++;
            if(gdzieY == 0) i = 4;
        }
        else
        {
            i = 4;
        }
    }
    gdzieX = miejsceRuchuX;
    gdzieY = miejsceRuchuY;
    //sprawdzam na lewo od aktualnego ruchu
    for(int i = 0; i < 4; i++)
    {
        gdzieY += 1;
        wygranaX[w] = gdzieX;
        wygranaY[w] = gdzieY;;
        w++;
        if(gdzieY >= 0 && gdzieY <= 19 && plansza[gdzieX][gdzieY] == playerId)
        {
            piatka += 1;
            if(gdzieY == 19) i = 4;
        }
        else
        {
            i = 4;
        }
    }

    if(piatka < 5)
    {
        piatka = 1;
        gdzieX = miejsceRuchuX;
        gdzieY = miejsceRuchuY;
        for(int i = 1; i < 10; i++)
        {
            wygranaX[i] = -1;
            wygranaY[i] = -1;
        }
        w = 1;
        //sprawdzam w górę od aktualnego ruchu
        for(int i = 0; i < 4; i++)
        {
            gdzieX -= 1;
            if(gdzieX >= 0 && gdzieX <= 19 && plansza[gdzieX][gdzieY] == playerId)
            {
                piatka += 1;
                wygranaX[w] = gdzieX;
                wygranaY[w] = gdzieY;;
                w++;
                if(gdzieX == 0) i = 4;
            }
            else
            {
                i = 4;
            }
        }
        gdzieX = miejsceRuchuX;
        gdzieY = miejsceRuchuY;
        //sprawdzam w dół od aktualnego ruchu
        for(int i = 0; i < 4; i++)
        {
            gdzieX += 1;
            if(gdzieX >= 0 && gdzieX <= 19 && plansza[gdzieX][gdzieY] == playerId)
            {
                piatka += 1;
                wygranaX[w] = gdzieX;
                wygranaY[w] = gdzieY;;
                w++;
                if(gdzieX == 19) i = 4;
            }
            else
            {
                i = 4;
            }
        }

        if(piatka < 5)
        {
            piatka = 1;
            gdzieX = miejsceRuchuX;
            gdzieY = miejsceRuchuY;
            for(int i = 1; i < 10; i++)
            {
                wygranaX[i] = -1;
                wygranaY[i] = -1;
            }
            w = 1;
            //sprawdzam po skosie \ górna część
            for(int i = 0; i < 4; i++)
            {
                gdzieX -= 1;
                gdzieY -= 1;
                if(gdzieX >= 0 && gdzieY >= 0 && plansza[gdzieX][gdzieY] == playerId)
                {
                    piatka += 1;
                    wygranaX[w] = gdzieX;
                    wygranaY[w] = gdzieY;;
                    w++;
                    if(gdzieX == 0 || gdzieY == 0) i = 4;
                }
                else
                {
                    i = 4;
                }
            }
            gdzieX = miejsceRuchuX;
            gdzieY = miejsceRuchuY;
            //sprawdzam w dół od aktualnego ruchu
            for(int i = 0; i < 4; i++)
            {
                gdzieX += 1;
                gdzieY += 1;
                if(gdzieX <= 19 && gdzieY <= 19 && plansza[gdzieX][gdzieY] == playerId)
                {
                    piatka += 1;
                    wygranaX[w] = gdzieX;
                    wygranaY[w] = gdzieY;;
                    w++;
                    if(gdzieX == 19 || gdzieY == 19) i = 4;
                }
                else
                {
                    i = 4;
                }
            }

            if(piatka < 5)
            {
                piatka = 1;
                gdzieX = miejsceRuchuX;
                gdzieY = miejsceRuchuY;
                for(int i = 1; i < 10; i++)
                {
                    wygranaX[i] = -1;
                    wygranaY[i] = -1;
                }
                w = 1;
                //sprawdzam po skosie /
                //górna część
                for(int i = 0; i < 4; i++)
                {
                    gdzieX -= 1;
                    gdzieY += 1;
                    if(gdzieX >= 0 && gdzieY <= 19 && plansza[gdzieX][gdzieY] == playerId)
                    {
                        piatka += 1;
                        wygranaX[w] = gdzieX;
                        wygranaY[w] = gdzieY;;
                        w++;
                        if(gdzieX == 0 || gdzieY == 19) i = 4;
                    }
                    else
                    {
                        i = 4;
                    }
                }
                gdzieX = miejsceRuchuX;
                gdzieY = miejsceRuchuY;
                //sprawdzam w dół od aktualnego ruchu
                for(int i = 0; i < 4; i++)
                {
                    gdzieX += 1;
                    gdzieY -= 1;
                    if(gdzieX <= 19 && gdzieY >= 0 && plansza[gdzieX][gdzieY] == playerId)
                    {
                        piatka += 1;
                        wygranaX[w] = gdzieX;
                        wygranaY[w] = gdzieY;;
                        w++;
                        if(gdzieX == 19 || gdzieY == 0) i = 4;
                    }
                    else
                    {
                        i = 4;
                    }
                }

            }
        }
    }

    if(piatka >= 5) //jeżeli jest min 5 w "rzędzie"
    {
        myWin = 8;
        //zaznaczenie na planszy zwycięskich ruchów
        for(int i = 0 ; i < 9; i++)
        {
            if(wygranaX[i] != -1)
            {
                plansza[wygranaX[i]][wygranaY[i]] = 8;
            }
            else
            {
                i = 9;
            }
        }
        repaint();
    }

}

void MainWindow::cleanBoard() //czyszczenie planszy
{
   for(int i = 0; i < N; i++)
   {
       for(int j = 0; j < N; j++)
       {
           plansza[i][j] = 0;
       }
   }
   repaint();

}

void MainWindow::readyRead() //gra
{

    if(onlyOne == 0) //odbieranie informacji o id gracza w danej rozgrywce
    {
        //odbieranie info, którym klient jest graczem
        bzero(cbBuf,sizeof(cbBuf));
        tcpSocket->read(cbBuf, sizeof(char));
        playerId = (int)(cbBuf[0])-48; //przypisanie ID gracza w tej rozgrywce
        onlyOne = 1;
        myWin = 0;
    }


    if(playerId == 2 && onlyOne == 1) //jeżeli odebrane zostały informacje o id, gracz przechodzi do swojej "części gry" - odbiera info o ruchu/wykonuje ruch
    {
        stageOne = 1;
        match = 1;
        onlyOne = 2;
    }
    if(playerId == 1 && onlyOne == 1)
    {
        stageTwo = 1;
        match = 1;
        onlyOne = 2;
    }

    if(match == 1 && myWin != 8)
    {
        if(stageOne == 1) //zgoda na oczekiwanie na ruch
        {
            ui->label_2->setText("Ruch \n  przeciwnika...");
            //odbieram info o ruchu przeciwnika
            bzero(cbBuf,sizeof(cbBuf));
            tcpSocket->read(cbBuf, sizeof(cbBuf));

            if(cbBuf[0] != 0)
            {
                plansza[(int)(cbBuf[1])-48][(int)(cbBuf[2])-48] = (int)(cbBuf[0])-48; //zapisanie ruchu przeciwnika na planszy
                opponentWin = (int)cbBuf[3]-48;
                repaint();
                moves += 1;
                if(opponentWin == 8) //jeżeli przeciwnik wygrał
                {
                    match = 0;
                    ui->label_2->setText("Przegrałeś...");

                    for(int j = 5; j < 23; j++)
                    {
                        plansza[(int)(cbBuf[j])-48][(int)(cbBuf[j+1])-48] = 8;
                        j++;
                    }
                    repaint();
                }
                else if(moves == 400) //jeżeli plansza jest zapełniona
                {
                    match = 0;
                    ui->label_2->setText("Remis!!!");
                }
                else if(opponentWin != 8 && moves < 400) //przeciwnik wykonał ruch i nie wygrał, ani nie ma remisu
                {
                    stageOne = 0;
                    stageTwo = 1;
                }
            }
            if((int)cbBuf[4]-48 == 3) //jeżeli przeciwnik przerwał grę
            {
                match = 0;
                ui->label_2->setText("Przeciwnik \nprzerwał grę...");
                stageTwo = 0;
            }

        }

        //jeśli gra trwa to robię ruch i wysyłam informacje
        if(stageTwo == 1)
        {
            ui->label_2->setText("Twój ruch...");
            if(permissionToMove == 0) permissionToMove = 1; //przyznanie możliwości wykonania ruchu

            if(permissionToMove == 2) //jeżeli ruch został wykonany
            {
                repaint();
                checkGame();
                //wysyłam info
                bzero(cbBuf, sizeof(cbBuf));
                cbBuf[0] = (char)playerId+48;
                cbBuf[1] = (char)miejsceRuchuX+48;
                cbBuf[2] = (char)miejsceRuchuY+48;
                cbBuf[3] = (char)myWin+48;

                if(myWin == 8)//jeżeli gracz wygrał to zapisuje do bufora informację o zwycięskich ruchach
                {
                    int j = 5;
                    for(int i = 0; i < 9; i++)
                    {
                        cbBuf[j] = (char)wygranaX[i]+48;
                        j++;
                        cbBuf[j] = (char)wygranaY[i]+48;
                        j++;
                    }
                }

                tcpSocket->write(cbBuf,sizeof(cbBuf));

                permissionToMove = 0;
                moves += 1;
                if(moves == 400)//jeżeli plansza zapełniona
                {
                    match = 0;
                    ui->label_2->setText("Remis!!!");
                }
                else if(myWin == 8)//jeżeli gracz wygrał
                {
                    ui->label_2->setText("Wygrałeś!!!");
                }
                else
                {
                    stageOne = 1;
                    stageTwo = 0;
                    ui->label_2->setText("Ruch \n  przeciwnika...");
                }

            }
            else //jeżeli jeszcze nie został wykonany ruch, wysyłany zostaje pusty bufor
            {
                bzero(cbBuf,sizeof(cbBuf));
                tcpSocket->write(cbBuf,sizeof(cbBuf));
            }
        }

    }

    bzero(cbBuf,sizeof(cbBuf));
    tcpSocket->read(cbBuf, sizeof(cbBuf));

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    this->setFixedSize(800,700);
    this->setWindowTitle("Tic-Tac-Toe");
    int k = 0;
    //przypisanie współrzędnych kwadracików na planszy
    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            int pomx = 30 * j;
            int pomy = 30 * i;
            rects[k] = QRect(50+pomx,5+pomy,30,30);
            k++;
        }
    }
    rects[400] = QRect(715,75,30,30); //do pokazania znaku gracza

    //wyzerowanie planszy
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            plansza[i][j] = 0;
        }
    }

    ui->label->setText("Oczekiwanie na \nprzeciwnika...");
    ui->label_2->setText(" ");

    //łączenie z serwerem
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    tcpSocket->connectToHost("127.0.0.1", 1234);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter *painter = new QPainter(this);
    painter->fillRect(e->rect(),QColor("white"));
    painter->setPen(QColor("green"));
    painter->drawRects(rects,M);

    //rysowanie znku gracza
    if(playerId == 1)
    {
        ui->label->setText("Twój znak:");
        painter->drawPixmap(rects[400].x()+3,rects[400].y()+3,QPixmap(":/images/one.png"));
    }
    else if(playerId == 2)
    {
        ui->label->setText("Twój znak:");
        painter->drawPixmap(rects[400].x()+3,rects[400].y()+3,QPixmap(":/images/two.png"));
    }

    //rysowanie ruchu gracza na planszy
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(plansza[i][j] == 1)
            {
                painter->drawPixmap(rects[i*N+j].x()+3,rects[i*N+j].y()+3,QPixmap(":/images/one.png"));
            }
            else if(plansza[i][j] == 2)
            {
                painter->drawPixmap(rects[i*N+j].x()+3,rects[i*N+j].y()+3,QPixmap(":/images/two.png"));
            }
            else if((plansza[i][j] == 8 && myWin == 8 && playerId == 1) || (plansza[i][j] == 8 && opponentWin == 8 && playerId == 2))
            {
                painter->drawPixmap(rects[i*N+j].x()+3,rects[i*N+j].y()+3,QPixmap(":/images/win/one.png"));
            }
            else if((plansza[i][j] == 8 && myWin == 8 && playerId == 2) || (plansza[i][j] == 8 && opponentWin == 8 && playerId == 1))
            {
                painter->drawPixmap(rects[i*N+j].x()+3,rects[i*N+j].y()+3,QPixmap(":/images/win/two.png"));
            }
        }
    }
}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(permissionToMove == 1) //jeżeli zgoda na ruch
    {
        for(int i = 0; i < M; i++)
        {
            if(rects[i].contains(e->pos()))
            {
                int row = i/N;
                int col = i%N;
                if(plansza[row][col] == 0)
                {
                    plansza[row][col] = playerId;
                    repaint(rects[i]);
                    miejsceRuchuX = row;
                    miejsceRuchuY = col;
                    permissionToMove = 2; //zgoda na wysłanie informacji o ruchu
                    repaint();
                }
            }
        }
    }
}





void MainWindow::on_pushButton_clicked()
{
    tcpSocket->disconnectFromHost();

    ui->label->setText("Oczekiwanie na \nprzeciwnika...");
    ui->label_2->setText(" ");
    //zresetowanie parametrów gry
    match = 0;
    playerId = 0;
    cleanBoard();
    onlyOne = 0;
    stageOne = 0;
    stageTwo = 0;

    tcpSocket->connectToHost("127.0.0.1", 1234);
}

