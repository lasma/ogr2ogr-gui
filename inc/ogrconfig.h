#ifndef OGRCONFIG_H
#define OGRCONFIG_H

#include <QString>
#include <QMap>
#include <QHash>
#include <QVariant>
#include <QList>

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

struct OgrConfig
{
public:
    OgrConfig();
    ~OgrConfig();

    void setSourceName(QString src_datasource_name);
    void setTargetName(QString dst_datasource_name);
    void setFormat(QString format_name);
    void setSql(QString format_name);
    void setCoordDims(int nCoordDims);
    void setToUpdate(bool);
    void setToOverwrite(bool);

    /**
     * @brief preparePapszArgv
     * @param papszArgv arguments for ogr2ogr run()
     * @return argument count
     */
    char ** preparePapszArgv();

    int getArgumentCount();

private:
    QString src_datasource_name;
    QString dst_datasource_name;
    QString format_name;
    int nCoordDims;
    bool bUpdate;
    bool bOverwrite;

    QHash<QString, QString> arguments;
    QHash<QString, QString> getArguments();

    void add(QString flag, QString value);

    int argcount;




};

#endif // OGRCONFIG_H
