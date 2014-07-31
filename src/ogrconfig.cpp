#include "inc/ogrconfig.h"
#include "cpl_string.h"
#include "iostream"


OgrConfig::OgrConfig()
{
    this->bUpdate = false;
    this->bOverwrite = false;
    this->argcount = 1;
    //papszArgv = NULL;
}

OgrConfig::~OgrConfig()
{
    //papszArgv;
}

void OgrConfig::add(QString flag, QString value)
{
    this->arguments["-"+flag] = value;

    if (value.isEmpty())
    {
        this->argcount += 1;
    } else
    {
        this->argcount += 2;
    }
}

char **OgrConfig::preparePapszArgv()
{
    // Create argi=ument list for the run program
    char ** papszArgv = NULL;
//    papszOpti/*o*/ns = CSLSetNameValue( papszOptions, "DIM", "2" );
    // this first argument replaces ogr2ogr self
    papszArgv = CSLAddString( papszArgv, "gdal" );
    //papszArgv = CSLAddString( papszArgv, arguments.at(i).toStdString().c_str() );
    QHashIterator<QString, QString> i(arguments);
    while (i.hasNext()) {
        i.next();
        std::cout << i.key().toStdString() << ": " << i.value().toStdString() << std::endl;
        //QString argument = i.key() + " " + i.value();
        //std::cout << argument.toStdString() << std::endl;
        //papszArgv = CSLAddString( papszArgv, argument.toStdString().c_str() );
        if ( i.value().isEmpty())
        {
            papszArgv = CSLAddString( papszArgv, i.key().toStdString().c_str() );
        }
        else
        {
            //QString argument = i.key() + " " + i.value();
            //papszArgv = CSLAddString( papszArgv, argument.toStdString().c_str() );
            papszArgv = CSLAddString( papszArgv, i.key().toStdString().c_str() );
            papszArgv = CSLAddString( papszArgv, i.value().toStdString().c_str() );
            //papszArgv = CSLSetNameValue( papszArgv, i.key().toStdString().c_str(), i.value().toStdString().c_str() );
        }
        //cout << i.key() << ": " << i.value() << endl;
    }
    //papszArgv = CSLAddString( papszArgv, arg.toStdString().c_str() );

    //dst_datasource_name
    papszArgv = CSLAddString( papszArgv, this->dst_datasource_name.toStdString().c_str() );
    //src_datasource_name
    papszArgv = CSLAddString( papszArgv,  this->src_datasource_name.toStdString().c_str() );



    return papszArgv;


    //run(3, papszArgv);
}

int OgrConfig::getArgumentCount()
{
    return this->argcount;
}


QHash<QString, QString> OgrConfig::getArguments()
{
    // todo: need ot parse out empty args, e.g. -update has no arg, just a flag
    return this->arguments;
}

void OgrConfig::setSourceName(QString src_datasource_name)
{
    this->src_datasource_name = src_datasource_name;
    this->argcount += 1;
}

void OgrConfig::setSourceFileList(QStringList src_file_list)
{
}


void OgrConfig::setTargetName(QString dst_datasource_name)
{
    this->dst_datasource_name = dst_datasource_name;
    this->argcount += 1;
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

void OgrConfig::setToUpdate(bool update)
{
    if (update == true)
    {
        this->bUpdate = update;
        this->add("update", "");
    }
}

void OgrConfig::setToOverwrite(bool overwrite)
{
    if (overwrite == true)
    {
        this->bOverwrite = overwrite;
        this->add("overwrite", "");
    }
}


