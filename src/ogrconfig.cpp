#include "inc/ogrconfig.h"
#include "cpl_string.h"



OgrConfig::OgrConfig()
{
    this->update = false;
    //papszArgv = NULL;
}

OgrConfig::~OgrConfig()
{
    //papszArgv;
}

void OgrConfig::add(QString flag, QString value)
{
    QHash<QString, QString> argument;
    argument["-"+flag] = value;
    this->arguments.append(argument);
}

char **OgrConfig::preparePapszArgv()
{
    // Create argi=ument list for the run program
    char ** papszArgv = NULL;
//    papszOpti/*o*/ns = CSLSetNameValue( papszOptions, "DIM", "2" );
    // this first argument replaces ogr2ogr self
    papszArgv = CSLAddString( papszArgv, "gdal" );
    //dst_datasource_name
    papszArgv = CSLAddString( papszArgv, this->dst_datasource_name.toStdString().c_str() );
    //src_datasource_name
    papszArgv = CSLAddString( papszArgv,  this->src_datasource_name.toStdString().c_str() );

    int argcount = 3;

    return papszArgv;


    //run(3, papszArgv);
}


QList<QHash<QString, QString> > OgrConfig::getArguments()
{
    // todo: need ot parse out empty args, e.g. -update has no arg, just a flag
    return this->arguments;
}

void OgrConfig::setSourceName(QString src_datasource_name)
{
    this->src_datasource_name = src_datasource_name;
}

void OgrConfig::setTargetName(QString dst_datasource_name)
{
    this->dst_datasource_name = dst_datasource_name;
}

void OgrConfig::setFormat(QString format_name)
{
    this->format_name = format_name;
    this->add("f", format_name);
}

void OgrConfig::setCoordDims(int nCoordDims)
{
    this->nCoordDims = nCoordDims;
    this->add("dim", QString::number(nCoordDims));
}

void OgrConfig::setUpdate(bool update)
{
    if (update == true)
    {
        this->update = true;
        this->add("update", "");
    }
}


