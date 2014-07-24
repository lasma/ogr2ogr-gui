#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/ogr2ogr.cpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ogrconfig = OgrConfig();
    this->ogrconfig.source = "/home/inovauk/Downloads/airports/aaaaa.shp";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    char ** papszArgv = NULL;
//    papszOpti/*o*/ns = CSLSetNameValue( papszOptions, "DIM", "2" );
    papszArgv = CSLAddString( papszArgv, "gdal" );
    papszArgv = CSLAddString( papszArgv,  this->ogrconfig.source.toStdString().c_str() );
    papszArgv = CSLAddString( papszArgv, "/home/inovauk/Downloads/airports/foo.shp" );
    run(3, papszArgv);
}

//void MainWindow::on_source_entered()
//{
//    this->ogrconfig.source = "/home/inovauk/Downloads/airports/aaaaa.shp";
//}

void MainWindow::on_lineEdit_editingFinished()
{

}
