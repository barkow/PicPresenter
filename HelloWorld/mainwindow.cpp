#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>
#include <QtDebug>
#include <QWSServer>

#include "exif.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWSServer *server = QWSServer::instance();
    if(server) {
        server->setCursorVisible(false);
    }

    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0,0,this->width(),this->height());

    /*scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(ui->label);
    setCentralWidget(scrollArea);*/

    getImages();

    //QTimer::singleShot(2000, this, SLOT(loadNewImage()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(loadNewImage()));
    timer->start(15000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getImages()
{
    imageDir = new QDir("./pics");
    files = imageDir->entryList(QDir::Files);
    fileNo = files.size() - 1;
}

void MainWindow::loadNewImage()
{
    QString fileName = imageDir->absoluteFilePath(files.at(fileNo));
    fileNo--;
    if (fileNo < 0){
        this->getImages();
    }
    if (!fileName.isEmpty()) {
        //Orientierung bestimmen
        Exif *exif = new Exif();

        int Orientation;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) return;

        Orientation = 0;
        exif->getExifOrientation(file, &Orientation);
        file.close();
        //qDebug() << fileName << "  " << Orientation;

        QImage image(fileName);
        if (image.isNull()) {
            ui->label->setText(tr("Cannot load %1.").arg(fileName));
            return;
        }
        if (Orientation == 6){
            //qDebug() << "rotate";
            QTransform myTransform;
            myTransform.rotate(90);
            image = image.transformed(myTransform);
        }

        ui->label->setText("");
        ui->label->setText(tr("Load %1.").arg(fileName));
        //return;
        ui->label->setPixmap(QPixmap::fromImage(image));
        ui->label->adjustSize();

        double scaleFactor = 1;
        if (ui->label->width() > ui->label->height()){
           scaleFactor = (double)this->width() / ui->label->width();
        }
        else {
           scaleFactor = (double)this->height() / ui->label->height();
        }
        //qDebug() << "Scale: " << scaleFactor;
        //scrollArea->setWidgetResizable(true);
        //ui->label->resize(scaleFactor * 0.9* ui->label->size());
        ui->label->adjustSize();
        //ui->label->move(this->width() - ui->label->width() / 2, this->height() - ui->label->height()/2);
        ui->label->setGeometry(0,0,scaleFactor * ui->label->width(),scaleFactor * ui->label->height());
    }
}
