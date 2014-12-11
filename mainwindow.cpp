#include "mainwindow.h"
#include "ui_mainwindow.h"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);


MainWindow::MainWindow(QWidget *parent) :



    QMainWindow(parent),
    ui(new Ui::MainWindow), board_size(21)
{
    ui->setupUi(this);

    score=0;

   // int last_press =0;

    snake_size= 0;

    game_over = new QWidget;
    QLabel *over = new QLabel("GAME OVER!");
    over_layout->addWidget(over);

    over ->setStyleSheet("QLabel { background-color : ; color : red; }");

    QFont font = over->font();
    font.setPointSize(20);
    font.setBold(true);
    font.setItalic(true);
    over->setFont(font);

    game_over->setLayout(over_layout);


    // This code Creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    values = new int[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    // Random number generator for C++11
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,15);


    // Create each label for the board, initialize with random value.
    for(int i=0;i<board_size;i++) {
        for(int j=0;j<board_size;j++) {

            // Random values


            // Create label and set properties.
            labels[i*board_size+j] = new QLabel;

            labels[i*board_size+j]->setMinimumSize(40,40);
            labels[i*board_size+j]->setMaximumSize(40,40);
            labels[i*board_size+j]->setStyleSheet("QLabel { background-color : blue; color : yellow; }");
            labels[i*board_size+j]->setFrameStyle(3);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

            // Add label to the layout
            SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

        }
    }

    // Initialize the muncher at the top left corner, coordinate (0,0).

    Snake_Parts[3] = new QPoint(0,0); snake_size++;
    labels[1]->setStyleSheet("QLabel { background-color : white; color : green; }");
    labels[1]->setScaledContents(true);

    Snake_Parts[1] =  new QPoint(2,0); snake_size++;
    labels[3]->setStyleSheet("QLabel { background-color : white; color : green; }");
    labels[3]->setScaledContents(true);

    Snake_Parts[2] =  new QPoint(1,0); snake_size++;
    labels[2]->setStyleSheet("QLabel { background-color : white; color : green; }");
    labels[2]->setScaledContents(true);

    snake_position = new QPoint(3,0); snake_size++;
    labels[4]->setStyleSheet("QLabel { background-color : white; color : green; }");
    labels[4]->setScaledContents(true);

    Snake_Parts[0]= snake_position;


    Board->setFixedSize(800,800);


    // Now piece everything together
    QWidget* CoreWidget = new QWidget;


    // Do not allow board to be resized, otherwise spacings get messed up
      setFixedSize(850,850);

      // Create a vertical box layout for the two pieces
      QVBoxLayout *piece_together = new QVBoxLayout;

      piece_together->addWidget(Board,0,Qt::AlignCenter);

      //SquareGrid -> addWidget(score_label);

      CoreWidget->setLayout(piece_together);

     // SquareGrid -> addWidget(space);
      //QLabel *score_int = new QLabel(score_string);


      // Set the CoreWidget as the central widget to the main window
      setCentralWidget(CoreWidget);


      QString food_filename("/Users/omriraccah/Snake_Game/snake_food.jpg");
      food_image = new QPixmap(food_filename);

      number_food = 1;
      food_positions = new QPoint[number_food];

      // Set food randomly on the board
      food_positions[0].setX(distribution(generator)%board_size);
      food_positions[0].setY(distribution(generator)%board_size);

      connect(move_timer, SIGNAL(timeout()), this, SLOT(moveSnake()));
      //move_timer->setInterval(50);
      move_timer->start(50);

}

/** This function moves all the snake parts in the direction of the most recent key press
 */
void MainWindow::moveSnake()
{

    for(int i=0;i<snake_size;i++)
    {
        if(snake_position[i].rx()==food_positions[0].rx() && snake_position[i].ry()==food_positions[0].ry())
            {

            for(size_t i=0;i<board_size*board_size;i++)
                labels[i]->clear();

            score++;

            QLabel *score_int = new QLabel(score_string);
            SquareGrid -> addWidget(score_int);

            labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->clear();
            labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->setStyleSheet("QLabel { background-color : blue; color : yellow ; }");
            labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->setScaledContents(true);

                std::uniform_int_distribution<int> distribution(1,10);
                Add_Part();
                food_positions[0].setX(distribution(generator)%board_size);
                food_positions[0].setY(distribution(generator)%board_size);
            }
    }



    for(int i=1;i<snake_size;i++)
    {
        if(snake_position->rx()==Snake_Parts[i]->rx() && snake_position->ry()==Snake_Parts[i]->ry())
        {
            gameScore();
            game_over->show();
            move_timer->stop();
        }
    }

    //QTimer *move_timer = new QTimer(this);

   int x = snake_position->rx();
   int y = snake_position->ry();


   if(last_press==1 || last_press==2 || last_press==3 || last_press==4)
   {
   for(int i=1;i<snake_size;i++)
   {
       int previous_x = Snake_Parts[snake_size-i]->rx();
       int previous_y = Snake_Parts[snake_size-i]->ry();

       int new_x = Snake_Parts[snake_size-(i+1)]->rx();
       int new_y = Snake_Parts[snake_size-(i+1)]->ry();


      // Snake_Parts[snake_size-i]=Snake_Parts[snake_size-(i+1)];
       updateSnake(previous_x,previous_y, new_x, new_y, Snake_Parts[snake_size-i]);

   }

   }



   if(last_press==1){
       if(snake_position->rx() != 0)
       {
   updateSnake(x,y,x-1,y,snake_position);
       }
       else
       {
           gameScore();
           game_over->show();
           move_timer->stop();
       }
   }

if(last_press==2){
    if(snake_position->rx() != board_size-1)
    {
updateSnake(x,y,x+1,y,snake_position);
    }
    else
    {
        gameScore();
        game_over->show();
        move_timer->stop();
    }
}

if(last_press==3){
    if(snake_position->ry() != 0)
    {
updateSnake(x,y,x,y-1,snake_position);
    }
    else
    {
        gameScore();
        game_over->show();
        move_timer->stop();
    }
}

if(last_press==4){
    if(snake_position->ry() != board_size-1)
    {
updateSnake(x,y,x,y+1,snake_position);
    }
    else
    {
        gameScore();
        game_over->show();
        move_timer->stop();
    }
}

for(int i=0;i<snake_size;i++)
{
    if(snake_position[i].rx()==food_positions[0].rx() && snake_position[i].ry()==food_positions[0].ry())
        {

        for(size_t i=0;i<board_size*board_size;i++)
            labels[i]->clear();

        score++;

        QLabel *score_int = new QLabel(score_string);
        SquareGrid -> addWidget(score_int);

        labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->clear();
        labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->setStyleSheet("QLabel { background-color : blue; color : yellow ; }");
        labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->setScaledContents(true);

            std::uniform_int_distribution<int> distribution(1,10);
            Add_Part();
            food_positions[0].setX(distribution(generator)%board_size);
            food_positions[0].setY(distribution(generator)%board_size);
        }
}




QCoreApplication::processEvents();
repaint();
}


MainWindow::~MainWindow()
{
    // According to
    delete [] values;
    delete [] food_positions;
    delete [] snake_position;

    delete ui;
}

/** A function to process key presses for directing snake movement
 @param QKeyEvent - dereferenced key press event.
 */
void MainWindow::keyPressEvent(QKeyEvent *event){


    for(int i=0;i<snake_size;i++)
    {
        if(snake_position[i].rx()==food_positions[0].rx() && snake_position[i].ry()==food_positions[0].ry())
            {

            for(size_t i=0;i<board_size*board_size;i++)
                labels[i]->clear();

            score++;

            QLabel *score_int = new QLabel(score_string);
            SquareGrid -> addWidget(score_int);

            labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->clear();
            labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->setStyleSheet("QLabel { background-color : blue; color : yellow ; }");
            labels[food_positions[0].rx()*board_size+food_positions[0].ry()]->setScaledContents(true);

                std::uniform_int_distribution<int> distribution(1,10);
                Add_Part();
                food_positions[0].setX(distribution(generator)%board_size);
                food_positions[0].setY(distribution(generator)%board_size);
            }
    }


    int x = snake_position->rx();
    int y = snake_position->ry();


    //LOOP IS HERE
    //

    //
    switch (event->key()){

    case Qt::Key_Left:
        if(snake_position->rx() != 0)
           {
         updateSnake(x,y,x-1,y,snake_position); last_press=1;
        }
        else
        {
            gameScore();
            game_over->show();
            move_timer->stop();
        }


        break;
    case Qt::Key_Right:
        if(snake_position->rx() != board_size-1)
          {  updateSnake(x,y,x+1,y,snake_position); last_press=2;
        }
        else
        {
            gameScore();
            game_over->show();
            move_timer->stop();
        }

        break;
    case Qt::Key_Up:
        if(snake_position->ry() != 0)
          {  updateSnake(x,y,x,y-1,snake_position); last_press=3;
                    ;}
        else
        {
            gameScore();
            game_over->show();
            move_timer->stop();
        }

        break;
    case Qt::Key_Down:
        if(snake_position->ry() != board_size-1)
           { updateSnake(x,y,x,y+1,snake_position); last_press=4;
        }
        else
            {
                gameScore();
                game_over->show();
                move_timer->stop();
            }

        break;


    default:
        QWidget::keyPressEvent(event);
    }
    QCoreApplication::processEvents();
    repaint();
    return;
}

/** Function to display the final score in the game over widget
 */
void MainWindow::gameScore()
{

QHBoxLayout *score_display = new QHBoxLayout();
QPushButton *exit = new QPushButton();
exit->setText("exit");

over_layout->addLayout(score_display);


QLabel *score_label = new QLabel("You ate ");

QString score_string;

score_string.setNum(score);

QLabel *int_label = new QLabel(score_string);

QLabel *score_label2 = new QLabel(" lady bugs!");

QFont font = int_label->font();
font.setBold(true);
font.setItalic(true);
int_label->setFont(font);




score_display->addWidget(score_label);
score_display->addWidget(int_label);
score_display->addWidget(score_label2);
over_layout->addWidget(exit);

connect(exit, SIGNAL(clicked()), game_over, SLOT(close()));
connect(exit, SIGNAL(clicked()), this, SLOT(close()));
}


/** Function to update screen objects
 @param QPaintEvent dereferenced 'e' paint event
 */
void MainWindow::paintEvent(QPaintEvent *e) {


    for(int i=0; i<snake_size;i++)
        {
    int x = Snake_Parts[i]->rx();
    int y = Snake_Parts[i]->ry();

    labels[y*board_size+x]->setStyleSheet("QLabel { background-color : white; color : green; }");
    labels[y*board_size+x]->setScaledContents(true);
    }

    for(size_t i=0;i<number_food;i++) {
        int px = food_positions[i].rx();
        int py = food_positions[i].ry();

        if(px >= 0 && py >= 0 && px < board_size && py < board_size) {
            labels[py*board_size+px]->setPixmap(*food_image);
            labels[py*board_size+px]->setScaledContents(true);
        }
    }


}

/** This function repaints prior snake positions to board color and sets new QPoint coodinates for snake part.
 @param int px - prior x-coordinate for snake block
 @param int py - prior y-coordinate for snake block
 @param int nx - new x-coordinate for snake block
 @param int ny - new x-coordinate for snake block
 @param QPoint *a - snake part (or position) being updated
 */
void MainWindow::updateSnake(int px, int py, int nx, int ny, QPoint *a) {
    labels[py*board_size+px]->setStyleSheet("QLabel { background-color :blue ; color : yellow; }");


    a->setX(nx);
    a->setY(ny);

//    return (px==nx)&&(py==ny);
}


/** A function to add increase the legnth of the snake by one label
 */
void MainWindow::Add_Part()
{
    //what point? The last one in the

    int x = Snake_Parts[snake_size-1]->rx();
    int y = Snake_Parts[snake_size-1]->ry();

    if(last_press==1)
    {
    Snake_Parts[snake_size] = new QPoint(x,y+1); snake_size++;
    //score++;
    }
    else if(last_press==2)
    {
    Snake_Parts[snake_size] = new QPoint(x,y+1); snake_size++;
    //score++;
    }
    else if(last_press==3)
    {
    Snake_Parts[snake_size] = new QPoint(x,y+1); snake_size++;
   // score++;
    }
    else if(last_press==4)
    {
    Snake_Parts[snake_size] = new QPoint(x,y+1); snake_size++;
    //score++;
    }
}

