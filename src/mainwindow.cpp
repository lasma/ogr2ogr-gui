#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/ogr2ogr.cpp"
#include "inc/ogrconfig.h"
#include "QFileDialog"
#include "QPlainTextEdit"
#include "QDebug"
#include "QProcess"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    databaseDialog = new DatabaseDialog(this);

    InitData();
    InitProjections();
    InitFormats();
    InitSlots();

    ui->txtSourceName->setText( "/home/inovauk/Downloads/airports/foo.shp" );
    ui->txtTargetName->setText( "/home/inovauk/Downloads/airports/out.shp" );

    ui->radTargetOverwrite->setChecked( true );
    ogrconfig.setToOverwrite( true );

    SetTargetFormat("ESRI Shapefile");


}

MainWindow::~MainWindow()
{
    delete ui;
    delete [] *formats;
    delete [] *databases;
    delete [] *projections;
}

void MainWindow::InitSlots()
{
    QObject::connect( ui->radSourceFile, SIGNAL( toggled( bool ) ), this, SLOT( evtRadSourceFile( void ) ) );
    QObject::connect( ui->radSourceFolder, SIGNAL( toggled( bool ) ), this, SLOT( evtRadSourceFolder( void ) ) );
    QObject::connect( ui->radSourceDatabase, SIGNAL( toggled( bool ) ), this, SLOT( evtRadSourceDatabase( void ) ) );

    QObject::connect( ui->txtSourceName, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtSourceName( void ) ) );
    QObject::connect( ui->btnSourceName, SIGNAL( clicked( void ) ), this, SLOT( evtBtnSourceName( void ) ) );
    QObject::connect( ui->cmbSourceFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbSourceFormat( int ) ) );


    QObject::connect( ui->radTargetFile, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetFile( void ) ) );
    QObject::connect( ui->radTargetFolder, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetFolder( void ) ) );
    QObject::connect( ui->radTargetDatabase, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetDatabase( void ) ) );

    QObject::connect( ui->cmbTargetFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbTargetFormat( int ) ) );
    QObject::connect( ui->cmbTargetFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbTargetFormat( void ) ) );

    QObject::connect( ui->txtTargetName, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtTargetName( void ) ) );
    QObject::connect( ui->btnTargetName, SIGNAL( clicked() ), this, SLOT( evtBtnTargetName( void ) ) );

    QObject::connect( ui->radTargetOverwrite, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetOverwrite( void ) ) );
    QObject::connect( ui->radTargetAppend, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetAppend( void ) ) );
    QObject::connect( ui->radTargetUpdate, SIGNAL( toggled( bool ) ), this, SLOT( evtRadTargetUpdate( void ) ) );

    QObject::connect( ui->btnExecute, SIGNAL( clicked( void ) ), this, SLOT( evtBtnExecute( void ) ) );
    QObject::connect( ui->btnQuit, SIGNAL( clicked( void ) ), this, SLOT( evtBtnQuit( void ) ) );

}

void MainWindow::InitData( void )
{

    formats = new QString * [ formatsCount ];

    for( int i = 0; i < formatsCount; i ++ )
    {
        formats[ i ] = new QString[ 2 ];
    }

    databases = new QString * [ databasesCount ];

    for( int i = 0; i < databasesCount; i ++ )
    {
        databases[ i ] = new QString[ 2 ];
    }

    projections = new QString*[ projectionsCount ];

    for( int i = 0; i < projectionsCount; i ++ )
    {
        projections[ i ] = new QString[ 2 ];
    }

    #include "inc/dta.h"
}

void MainWindow::InitProjections( void )
{
    QString prj;

    ui->cmbTargetProj->addItem( tr( "" ) );

    for( int i = 1; i < projectionsCount; i ++ )
    {
        prj.clear();
        prj = projections[ i ][ 0 ];
        prj.append( tr( " : " ) );
        prj.append( projections[ i ][ 1 ] );

        ui->cmbTargetProj->addItem( prj );
    }
}

void MainWindow::InitFormats( void )
{
    for( int i = 0; i < formatsCount; i ++ )
    {
        ui->cmbSourceFormat->addItem( formats[ i ][ 0 ] );
    }

    for( int i = 0; i < formatsCount; i ++ )
    {
        ui->cmbTargetFormat->addItem( formats[ i ][ 0 ] );
    }
}

void MainWindow::UpdateParameters( void )
{
    int argcount = this->ogrconfig.getArgumentCount();
    char ** papszArgv = this->ogrconfig.preparePapszArgv();
    QString args;
    for (int i=0; i<argcount; i++)
    {
        if (i == 0)
        {
            args.append("ogr2ogr");
        }
        else
        {
            args.append(QString::fromLatin1(papszArgv[i]));
            args.append(" ");
        }
    }
    ui->txtParameters->setPlainText(args);
}

void MainWindow::SetTargetFormat(QString format)
{
    this->ogrconfig.setOutputFormat(format);
}

//void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
//{
/*
Usage: ogr2ogr [--help-general] [-skipfailures] [-append] [-update]
               [-select field_list] [-where restricted_where]
               [-progress] [-sql <sql statement>] [-dialect dialect]
               [-preserve_fid] [-fid FID]
               [-spat xmin ymin xmax ymax]
               [-a_srs srs_def] [-t_srs srs_def] [-s_srs srs_def]
               [-f format_name] [-overwrite] [[-dsco NAME=VALUE] ...]
               dst_datasource_name src_datasource_name
               [-lco NAME=VALUE] [-nln name] [-nlt type] [-dim 2|3] [layer [layer ...]]

Advanced options :
               [-gt n]
               [-clipsrc [xmin ymin xmax ymax]|WKT|datasource|spat_extent]
               [-clipsrcsql sql_statement] [-clipsrclayer layer]
               [-clipsrcwhere expression]
               [-clipdst [xmin ymin xmax ymax]|WKT|datasource]
               [-clipdstsql sql_statement] [-clipdstlayer layer]
               [-clipdstwhere expression]
               [-wrapdateline][-datelineoffset val]
               [[-simplify tolerance] | [-segmentize max_dist]]
               [-fieldTypeToString All|(type1[,type2]*)]
               [-fieldmap identity | index1[,index2]*]
               [-splitlistfields] [-maxsubfields val]
               [-explodecollections] [-zfield field_name]
               [-gcp pixel line easting northing [elevation]]* [-order n | -tps]

*/
    // Create argi=ument list for the run program
   // char ** papszArgv = NULL;
//    papszOpti/*o*/ns = CSLSetNameValue( papszOptions, "DIM", "2" );
    // this first argument replaces ogr2ogr self
    //papszArgv = CSLAddString( papszArgv, "gdal" );
    //dst_datasource_name
    //papszArgv = CSLAddString( papszArgv, this->ogrconfig.dst_datasource_name.toStdString().c_str() );
    //src_datasource_name
    //papszArgv = CSLAddString( papszArgv,  this->ogrconfig.src_datasource_name.toStdString().c_str() );

    //char * papszArgv = NULL;
//    int argcount = this->ogrconfig.getArgumentCount();
//    char ** papszArgv = this->ogrconfig.preparePapszArgv();

//    run(argcount, papszArgv);
//}

void MainWindow::evtTxtSourceName( void )
{
//    if( ui->txtSourceName->text().startsWith( tr( "file://" ) ) )
//    {
//        ui->txtSourceName->setText( QUrl( ui->txtSourceName->text() ).authority().trimmed() );
//    }

    this->ogrconfig.setSourceName( ui->txtSourceName->text() );

    UpdateParameters();
}


void MainWindow::evtBtnSourceName( void )
{
    int idx = ui->cmbSourceFormat->currentIndex();

    QString type;

    if( ui->radSourceFile->isChecked() )
    {
        type = tr( "\"" ) + formats[ idx ][ 0 ] + tr( "\" | *." ) + formats[ idx ][ 1 ];

        ui->txtSourceName->setText( QFileDialog::getOpenFileName( this, tr( "Source File" ), tr( "" ), type ) );

        ogrconfig.src_file_list.clear();

        ogrconfig.src_file_list.append( ui->txtSourceName->text() );
    }
    else if( ui->radSourceFolder->isChecked() )
    {
        QStringList types;

        type = tr( "*." ) + formats[ ui->cmbSourceFormat->currentIndex() ][ 1 ];

        ui->txtSourceName->setText( QFileDialog::getExistingDirectory( this, tr( "Source Folder" ), tr( "" ), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ) );

        QDir dir( ui->txtSourceName->text() );

        types.append( type );

        QStringList list = dir.entryList( types );

        ogrconfig.src_file_list.clear();

        for( int i = 0; i < list.size(); i ++ )
        {
            ogrconfig.src_file_list.append( list.at( i ) );
        }

        if( list.size() > 1 )
        {
            ui->txtSourceProj->setEnabled( false );
            ui->txtSourceQuery->setEnabled( false );
        }
    }
    else if( ui->radSourceDatabase->isChecked() )
    {
        databaseDialog->show();
//		inf->setConnectionType( databases[ idx ][ 1 ] );

//		inf->setDialogStyle( 1 );

//		if( inf->exec() == QDialog::Accepted )
//		{
//			ui->txtSourceName->setText( inf->getConnectionString() );
//		}

        ogrconfig.src_file_list.clear();

//		QStringList tables = inf->getSelectedTables();

//		QString connectionString = ui->txtSourceName->text();

//		connectionString.truncate( connectionString.lastIndexOf( tr( "tables=" ) ) );

//		for( int i = 0; i < tables.size(); i ++ )
//		{
//			fileList.append( connectionString + tr( "tables=" ) + tables.at( i ) );
//		}

//		if( fileList.size() > 1 )
//		{
//			ui->txtSourceProj->setEnabled( false );
//			ui->txtSourceQuery->setEnabled( false );

//			ui->radTargetFile->setEnabled( false );
//			ui->radTargetFolder->setChecked( true );
//		}
//		else
//		{
//			ui->radTargetFile->setEnabled( true );
//			ui->radTargetFile->setChecked( true );
//		}
    }

    UpdateParameters();
}

void MainWindow::evtCmbSourceFormat(int i)
{
    ui->txtSourceName->clear();
    ui->txtSourceProj->clear();
    ui->txtSourceQuery->clear();

    UpdateParameters();
}

void MainWindow::evtCmbTargetFormat( int i )
{
    ui->txtTargetName->clear();
    ogrconfig.setOutputFormat(ui->cmbTargetFormat->currentText());

    UpdateParameters();
}

void MainWindow::evtRadSourceFile( void )
{
    ui->btnSourceName->setText( tr( "&Open" ) );

    ui->cmbSourceFormat->clear();

    for( int i = 0; i < formatsCount; i ++ )
    {
        ui->cmbSourceFormat->addItem( formats[ i ][ 0 ] );
    }

    ui->radTargetFile->setEnabled( true );
    ui->radTargetFolder->setEnabled( false );
    ui->radTargetDatabase->setEnabled( true );

    ui->radTargetFile->setChecked( true );

    ui->txtSourceName->clear();
    ui->txtSourceProj->clear();
    ui->txtSourceQuery->clear();

    ui->txtSourceProj->setEnabled( true );
    ui->txtSourceQuery->setEnabled( true );

    UpdateParameters();
}

void MainWindow::evtRadSourceFolder( void )
{
    ui->btnSourceName->setText( tr( "&Browse" ) );

    ui->cmbSourceFormat->clear();

    for( int i = 0; i < formatsCount; i ++ )
    {
        ui->cmbSourceFormat->addItem( formats[ i ][ 0 ] );
    }

    ui->radTargetFile->setEnabled( false );
    ui->radTargetFolder->setEnabled( true );
    ui->radTargetDatabase->setEnabled( true );

    ui->radTargetFolder->setChecked( true );

    ui->txtSourceName->clear();
    ui->txtSourceProj->clear();
    ui->txtSourceQuery->clear();

    ui->txtSourceProj->setEnabled( true );
    ui->txtSourceQuery->setEnabled( true );

    UpdateParameters();
}



void MainWindow::evtRadSourceDatabase( void )
{

    ui->btnSourceName->setText( tr( "&Connect" ) );

    ui->cmbSourceFormat->clear();

    for( int i = 0; i < databasesCount; i ++ )
    {
        ui->cmbSourceFormat->addItem( databases[ i ][ 0 ] );
    }

    ui->radTargetFile->setEnabled( true );
    ui->radTargetFolder->setEnabled( true );
    ui->radTargetDatabase->setEnabled( true );

    ui->radTargetFile->setChecked( true );

    ui->txtSourceName->clear();
    ui->txtSourceProj->clear();
    ui->txtSourceQuery->clear();

    ui->txtSourceProj->setEnabled( true );
    ui->txtSourceQuery->setEnabled( true );

    UpdateParameters();
}


void MainWindow::evtRadTargetFile( void )
{
    ui->btnTargetName->setText( tr( "&Save" ) );

    ui->cmbTargetFormat->clear();

    for( int i = 0; i < formatsOutput; i ++ )
    {
        ui->cmbTargetFormat->addItem( formats[ i ][ 0 ] );
    }

    ui->txtTargetName->clear();
    ui->txtTargetProj->clear();

    ui->cmbTargetProj->setCurrentIndex( 0 );

    UpdateParameters();
}

void MainWindow::evtRadTargetFolder( void )
{
    ui->btnTargetName->setText( tr( "&Browse" ) );

    ui->cmbTargetFormat->clear();

    for( int i = 0; i < formatsOutput; i ++ )
    {
        ui->cmbTargetFormat->addItem( formats[ i ][ 0 ] );
    }

    UpdateParameters();
}

void MainWindow::evtRadTargetDatabase( void )
{
    ui->btnTargetName->setText( tr( "&Connect" ) );

    ui->cmbTargetFormat->clear();

    for( int i = 0; i < databasesOutput; i ++ )
    {
        ui->cmbTargetFormat->addItem( databases[ i ][ 0 ] );
    }

    UpdateParameters();
}

void MainWindow::evtTxtTargetName( void )
{
    ui->btnExecute->setEnabled( true );
    ogrconfig.setTargetName( ui->txtTargetName->text());

    UpdateParameters();
}


void MainWindow::evtBtnTargetName( void )
{
    QString type;

    int idx = ui->cmbTargetFormat->currentIndex();

    if( ui->radTargetDatabase->isChecked() )
    {
        databaseDialog->show();
        //inf->setDialogStyle( 0 );

        //inf->setConnectionType( databases[ cmbTargetFormat->currentIndex() ][ 1 ] );

        //if( inf->exec() == QDialog::Accepted )
        //{
        //	ui->txtTargetName->setText( inf->getConnectionString() );
        //}
    }
    else if( ui->radTargetFolder->isChecked() )
    {
        if( ui->radSourceFile->isChecked() )
        {
            type = tr( "\"" ) + formats[ idx ][ 0 ] + tr( " (*." ) + formats[ idx ][ 1 ] + tr( ") | *." ) + formats[ idx ][ 1 ];

            ui->txtTargetName->setText( QFileDialog::getSaveFileName( this, tr( "Save File" ), tr( "" ), type ) );
        }
        else if( ui->radTargetFolder->isChecked() )
        {
            ui->txtTargetName->setText( QFileDialog::getExistingDirectory( this, tr( "Target Folder" ), tr( "" ), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ) );
        }
    }
    else
    {
        type = tr( "\"" ) + formats[ idx ][ 0 ] + tr( "\" | *." ) + formats[ idx ][ 1 ];

        ui->txtTargetName->setText( QFileDialog::getSaveFileName( this, tr( "Target File" ), tr( "" ), type ) );
    }

    ui->btnExecute->setEnabled( true );

    UpdateParameters();
}

void MainWindow::evtRadTargetAppend( void )
{
    ogrconfig.setToAppend( ui->radTargetAppend->isChecked() );

    UpdateParameters();
}

void MainWindow::evtRadTargetOverwrite( void )
{
    ogrconfig.setToOverwrite( ui->radTargetOverwrite->isChecked() );

    UpdateParameters();
}

void MainWindow::evtRadTargetUpdate( void )
{
    ogrconfig.setToUpdate( ui->radTargetUpdate->isChecked() );

    UpdateParameters();
}

void MainWindow::evtBtnExecute( void )
{
    int argcount = this->ogrconfig.getArgumentCount();
    char ** papszArgv = this->ogrconfig.preparePapszArgv();

    QStringList args;
    for (int i=0; i<argcount; i++)
    {
        if ( i > 0 ) {
            args << QString::fromLatin1(papszArgv[i]);
        }
    }
    qDebug() << args;
    //ui->txtParameters->setPlainText(args);

    QProcess process;
    process.start("ogr2ogr", args);
    bool ok = process.waitForFinished(-1);
    QString out = QString::fromUtf8(process.readAllStandardOutput().data());
    QString err = QString::fromUtf8(process.readAllStandardError().data());
    ui->txtParameters->appendPlainText(out);
    ui->txtParameters->appendPlainText(err);

//    try {
//        run(argcount, papszArgv);
//    } catch (const std::exception &ex) {
//        //qDebug() << ex;
//    }
}

void MainWindow::evtBtnQuit( void )
{
    this->close();
}

//void MainWindow::on_source_entered()
//{
//    this->ogrconfig.source = "/home/inovauk/Downloads/airports/aaaaa.shp";
//}

