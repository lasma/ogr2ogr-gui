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

    // file formats
    const static int formatsCount = 13;
    QString **formats;

    // output formats
    const static int formatsOutput = 9;

    // database formats
    const static int databasesCount = 5;
    QString **databases;

    // output databases
    const static int databasesOutput = 3;

    // target projections
    const static int projectionsCount = 3578;
    QString **projections;

    /*!
     *	\fn void InitSlots( void );
     *	\brief Inits Slots
     */
    void InitSlots( void );

    /*!
     *	\fn void InitData( void );
     *	\brief Inits data
     */
    void InitData( void );

    /*!
     *	\fn void void InitProjections( void );
     *	\brief Inits projections
     */
    void InitProjections( void );

    void InitFormats( void );

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

//    void on_source_entered():
    void evtTxtSourceName();
    void evtBtnSourceName( void );
    void evtCmbSourceFormat(int i);
    void evtCmbTargetFormat( void );

    void SetFormat(QString format = "ESRI Shapefile");


};

#endif // MAINWINDOW_H
