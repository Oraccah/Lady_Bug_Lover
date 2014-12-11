#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <random>
#include <chrono>
#include <QTimer>
#include <QPushButton>

#include <iostream>

namespace Ui {
/**
 @class Main Window
 @brief This class contains all board variables and events for the game
 */
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

 public slots:
        void moveSnake();
        void gameScore();

public:
    explicit MainWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);

    void updateSnake(int px, int py, int nx, int ny, QPoint *a);
    void Add_Part();
    QLabel *score_int = new QLabel;

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLabel* Snake;
    QPixmap* food_image;

    QPoint *snake_position;
    QPoint *food_positions;

    // Board Variables
    QWidget *Board;
    QWidget *z;
   int last_press;
    QWidget *game_over;
    int board_size;
    int number_food;
    QLabel** labels;
    QPoint *Snake_Parts[100];
    QPoint *Snake_Parts_Copy[100];
    int snake_size;
    int* values;
    int score;
    QTimer *move_timer = new QTimer(this);
    QString score_string;
    QGridLayout *SquareGrid = new QGridLayout;
    QVBoxLayout *over_layout = new QVBoxLayout;
};

#endif // MAINWINDOW_H
