#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include "inc/ogrconfig.h"
#include "inc/databasedialog.h"

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
    DatabaseDialog *databaseDialog;

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

    /*!
     *	\fn void UpdateParameters( void );
     *	\brief Updates parameters
     */
    void UpdateParameters( void );

private slots:
    //void on_buttonBox_clicked(QAbstractButton *button);

    void evtRadSourceFile( void );
    void evtRadSourceFolder( void );
    void evtRadSourceDatabase( void );

    void evtTxtSourceName( void );
    void evtBtnSourceName( void );
    void evtCmbSourceFormat(int i);
    void evtTxtSourceQuery( void );

    void evtRadTargetFile( void );
    void evtRadTargetFolder( void );
    void evtRadTargetDatabase( void );

    void evtCmbTargetFormat(int i);

    void evtTxtTargetName( void );
    void evtBtnTargetName( void );
    void evtTxtTargetProj( void );
    void evtCmbTargetProj( void );

    void evtRadTargetAppend( void );
    void evtRadTargetOverwrite( void );
    void evtRadTargetUpdate( void );

    void evtTargetSkipFailures( void );

    void evtBtnExecute( void );
    void evtBtnQuit( void );

    void SetTargetFormat(QString format = "ESRI Shapefile");


};

#endif // MAINWINDOW_H
