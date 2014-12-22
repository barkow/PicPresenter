#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void getNextImage();
    void loadNewImage();

private:
    void getImages();
    Ui::MainWindow *ui;
    QScrollArea *scrollArea;
    QDir *imageDir;
    QStringList files;
    int fileNo;
    QTimer *timer;
};

#endif // MAINWINDOW_H
