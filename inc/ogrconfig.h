#ifndef OGRCONFIG_H
#define OGRCONFIG_H

#include <QString>
#include <QMap>
#include <QHash>
#include <QVariant>
#include <QList>
#include <QStringList>

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

    QStringList src_file_list;

    void setSourceName(QString src_datasource_name);
    void setSourceFileList(QStringList src_file_list);
    void setTargetName(QString dst_datasource_name);

    /**
     * @brief sets -f format_name
     */
    void setOutputFormat(QString format_name);

    /**
     * @brief sets -dialect sql_dialect
     */
    void setSqlDialect(QString sql_dialect);

    /**
     * @brief sets -sql sql_statement
     */
    void setSqlStatement(QString sql_statement);

    /**
     * @brief sets -where sql_where
     */
    void setSqlWhere(QString sql_where);

    /**
     * @brief sets -spat xmin, ymin, xmax, ymax
     */
    void setSpatialExtent(double xmin, double ymin, double xmax, double ymax);

    /**
     * @brief sets -dim
     */
    void setCoordDims(int nCoordDims);

    /**
     * @brief sets -update
     */
    void setToUpdate(bool);

    /**
     * @brief sets -append
     */
    void setToAppend(bool);

    /**
     * @brief sets -overwrite
     */
    void setToOverwrite(bool);

    /**
     * @brief sets -skipfailures
     */
    void setSkipFailures(bool);

    /**
     * @brief preparePapszArgv
     * @param papszArgv arguments for ogr2ogr run()
     * @return argument count
     */
    char ** preparePapszArgv();

    int getArgumentCount();

public:

private:
    QString src_datasource_name;

    QString dst_datasource_name;
    QString output_format;
    QString sql_dialect;
    QString sql_statement;
    QString sql_where;
    double xmin, ymin, xmax, ymax;
    int nCoordDims;
    bool bUpdate;
    bool bAppend;
    bool bOverwrite;
    bool bSkipfailures;

    QHash<QString, QString> arguments;
    QHash<QString, QString> getArguments();

    void add(QString flag, QString value);
    void remove(QString flag);

    int argcount;




};

#endif // OGRCONFIG_H
