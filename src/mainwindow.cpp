#include "inc/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/ogr2ogr.cpp"
#include "inc/ogrconfig.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ogrconfig.setSourceName("/home/inovauk/Downloads/airports/foo.shp");
    this->ogrconfig.setTargetName("/home/inovauk/Downloads/airports/out.shp");
    this->InitSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitSlots()
{
    QObject::connect( ui->txtSourceName, SIGNAL( textChanged( QString ) ), this, SLOT( evtTxtSourceName( void ) ) );
    ui->cmbFormat;
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
    int argcount = 3;
    char ** papszArgv = this->ogrconfig.preparePapszArgv();

    run(argcount, papszArgv);
}

void MainWindow::evtTxtSourceName()
{
//    if( ui->txtSourceName->text().startsWith( tr( "file://" ) ) )
//    {
//        ui->txtSourceName->setText( QUrl( ui->txtSourceName->text() ).authority().trimmed() );
//    }

    this->ogrconfig.setSourceName(ui->txtSourceName->text());
}

//void MainWindow::on_source_entered()
//{
//    this->ogrconfig.source = "/home/inovauk/Downloads/airports/aaaaa.shp";
//}

