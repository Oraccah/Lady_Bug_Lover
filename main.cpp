#include "mainwindow.h"
#include <QApplication>
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>
#include <QPushButton>
#include <QObject>
#include <QRadioButton>
#include <QPalette>
#include<QVector>
#include <QFont>

int main(int argc, char *argv[])
{
    //Welcome screen set up
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;

    //Creating closing window
    QPushButton *start = new QPushButton();
    QPushButton *instruction = new QPushButton();
    QPushButton *close_instruction = new QPushButton();
    close_instruction-> setText("close");
    instruction-> setText("Instructions");
    QWidget *instruction_widget = new QWidget;
    QLabel *instruction_label = new QLabel("Instructions");
    QFont font_instruct = instruction_label->font();
    font_instruct.setPointSize(15);
    font_instruct.setBold(true);
    font_instruct.setItalic(true);
    instruction_label->setFont(font_instruct);

    QLabel *instructions = new QLabel("You are a snake. You're goal: eat as many lady bugs as you can!\nUse the arrow keys to move throughout the board.\nIf you run into any of the walls or yourself (any part of the snake) the game will end.\nYou're score will be displayed when the game is over and is directly related to the amount you can eat. Have Fun!");

    QVBoxLayout *instruction_layout = new QVBoxLayout();
    instruction_widget->setLayout(instruction_layout);
    instruction_layout->addWidget(instruction_label);
    instruction_layout->addWidget(instructions);
    instruction_layout->addWidget(close_instruction);


    instruction_widget->setMaximumHeight(200);
    instruction_widget->setMaximumWidth(2);

    start ->setText("Start");


    QWidget *start_widget = new QWidget();

    QLabel *welcome = new QLabel("Welcome to Lady Bug Lover!");


    QFont font = welcome->font();
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(true);
    welcome->setFont(font);

    welcome ->setStyleSheet("QLabel { background-color : ; color : red; }");

    QLabel *difficulty = new QLabel("choose difficulty: ");

    welcome->setAlignment(Qt::AlignCenter);

    start_widget->setMinimumHeight(20);
    start_widget->setMinimumWidth(20);


    QVBoxLayout *start_layout = new QVBoxLayout();


    start_layout -> addWidget(welcome);
    start_layout -> addWidget(instruction);



    start_layout -> addWidget(start);

    start_widget -> setLayout(start_layout);

    ////window->show();
    start_widget->show();

    QObject::connect(start, SIGNAL(clicked()), w, SLOT(show()));

    QObject::connect(start, SIGNAL(clicked()), start_widget, SLOT(close()));
    QObject::connect(close_instruction, SIGNAL(clicked()), instruction_widget, SLOT(close()));
    QObject::connect(instruction, SIGNAL(clicked()), instruction_widget, SLOT(show()));

    return a.exec();
}
