#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(pressed()), this, SLOT(playMusic()));
    connect(ui->stopButton, SIGNAL(pressed()), this, SLOT(stopMusic()));

    // test
    ui->songList->addItem("Bach");
    ui->songList->addItem("Grieg");
    ui->composerImage->setPixmap(QPixmap(":/composers/grieg.jpg"));
    ui->composerText->setText("bla bla\nbla");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playMusic()
{
    // test
    ui->pianoRoll->noteOn(rand() % 100);
    ui->pianoRoll->noteOff(rand() % 100);
}

void MainWindow::stopMusic()
{
    ui->pianoRoll->noteOffAll();
}
