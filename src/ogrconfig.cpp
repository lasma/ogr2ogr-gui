#include "inc/ogrconfig.h"
#include "cpl_string.h"
#include "iostream"
#include "QDebug"


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

    qDebug() << flag << value;

    if (arguments.contains("-"+flag) == false )
    {
        if (value.isEmpty())
        {
            this->argcount += 1;
        } else
        {
            this->argcount += 2;
        }
    }

    this->arguments["-"+flag] = value;

    qDebug() << this->argcount << ": " << this->arguments;
}

void OgrConfig::remove(QString flag)
{

    qDebug() << "Removing " << flag;

    QHash<QString, QString>::iterator i = this->arguments.find("-"+flag);
    while ( i != arguments.end() && i.key() == "-"+flag ) {
        if (i.value().isEmpty()) {
            this->argcount -= 1;
        } else {
            this->argcount -= 2;
        }

        if (i.value() == 0 ) {
            i = arguments.erase(i);
        } else {
            ++i;
        }
    }
    //this->arguments.remove("-"+flag);

    qDebug() << this->argcount << ": " << this->arguments;
}

char **OgrConfig::preparePapszArgv()
{
    // Create argument list for the run program
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
    if (this->src_datasource_name.isEmpty()) {
        this->argcount += 1;
    }

    this->src_datasource_name = src_datasource_name;

    qDebug() << argcount << ": " << src_datasource_name;
}

void OgrConfig::setSourceFileList(QStringList src_file_list)
{
}


void OgrConfig::setTargetName(QString dst_datasource_name)
{
    if (this->dst_datasource_name.isEmpty()) {
        this->argcount += 1;
    }

    this->dst_datasource_name = dst_datasource_name;

    qDebug() << argcount << ": " << dst_datasource_name;
}

void OgrConfig::setOutputFormat(QString format_name)
{
    this->output_format = format_name;
    this->add("f", format_name);
}

void OgrConfig::setSqlDialect(QString sql_dialect)
{
    this->sql_dialect = sql_dialect;
    this->add("dialect", sql_dialect);
}

void OgrConfig::setSqlStatement(QString sql_statement)
{
    this->sql_statement = sql_statement;
    this->add("sql", sql_statement);
}

void OgrConfig::setSqlWhere(QString sql_where)
{
    this->sql_where = sql_where;
    this->add("where", sql_where);
}

void OgrConfig::setSpatialExtent(double xmin, double ymin, double xmax, double ymax)
{
    this->xmin = xmin;
    this->ymin = ymin;
    this->xmax = xmax;
    this->ymax = ymax;
    QString sql_extent = QString("%1 %2 %3 %4").arg(xmin).arg(ymin).arg(xmax).arg(ymax);
    this->add("spat", sql_extent);
}

void OgrConfig::setCoordDims(int nCoordDims)
{
    this->nCoordDims = nCoordDims;
    this->add("dim", QString::number(nCoordDims));
}

void OgrConfig::setToUpdate(bool update)
{
    this->bUpdate = update;

    if (update == true)
    {
        this->add("update", "");
        setToOverwrite(false);
        setToAppend(false);
    }
    else
    {
        this->remove("update");
    }
}

void OgrConfig::setToOverwrite(bool overwrite)
{
    this->bOverwrite = overwrite;

    if (overwrite == true)
    {
        this->add("overwrite", "");
        setToUpdate(false);
        setToAppend(false);
    }
    else
    {
        this->remove("overwrite");
    }

}

void OgrConfig::setToAppend(bool append)
{
    this->bAppend = append;

    if (append == true)
    {
        this->add("append", "");
        setToUpdate(false);
        setToOverwrite(false);
    }
    else
    {
        this->remove("append");
    }

}

void OgrConfig::setSkipFailures(bool skipfailures)
{
    if (skipfailures == true)
    {
        this->bSkipfailures = skipfailures;
        this->add("skipfailures", "");
    }
}




