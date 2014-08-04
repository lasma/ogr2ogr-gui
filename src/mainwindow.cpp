#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/ogr2ogr.cpp"
#include "inc/ogrconfig.h"
#include "QFileDialog"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitData();
    // needs databases from initdata()
    databaseDialog = new DatabaseDialog(this);
    InitProjections();
    InitFormats();



    this->ogrconfig.setSourceName("/home/inovauk/Downloads/airports/foo.shp");
    this->ogrconfig.setTargetName("/home/inovauk/Downloads/airports/out.shp");
    this->ogrconfig.setToOverwrite(true);
    SetFormat("ESRI Shapefile");

    InitSlots();
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
    QObject::connect( ui->cmbTargetFormat, SIGNAL( currentIndexChanged( int ) ), this, SLOT( evtCmbTargetFormat( void ) ) );


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



void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
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
    int argcount = this->ogrconfig.getArgumentCount();
    char ** papszArgv = this->ogrconfig.preparePapszArgv();

    run(argcount, papszArgv);
}

void MainWindow::evtTxtSourceName( void )
{
//    if( ui->txtSourceName->text().startsWith( tr( "file://" ) ) )
//    {
//        ui->txtSourceName->setText( QUrl( ui->txtSourceName->text() ).authority().trimmed() );
//    }

    this->ogrconfig.setSourceName(ui->txtSourceName->text());
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
}

void MainWindow::evtCmbSourceFormat(int i)
{
    ui->txtSourceName->clear();
    ui->txtSourceProj->clear();
    ui->txtSourceQuery->clear();
}

void MainWindow::evtCmbTargetFormat( void )
{
    ui->txtTargetName->clear();
}

void MainWindow::SetFormat(QString format)
{
    ui->cmbSourceFormat;
    this->ogrconfig.setFormat(format);
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
}

//void MainWindow::on_source_entered()
//{
//    this->ogrconfig.source = "/home/inovauk/Downloads/airports/aaaaa.shp";
//}

