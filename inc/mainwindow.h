#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include "inc/ogrconfig.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    OgrConfig ogrconfig;
    Ui::MainWindow *ui;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

//    void on_source_entered():


    void on_lineEdit_editingFinished();
};

#endif // MAINWINDOW_H
