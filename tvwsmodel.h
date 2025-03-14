/**
 * @package QTWhiteSpaceManager
 * @module TVWSModel.h
 * The TVWSModel class.
 * ----------------------------
 * Updates
 * @date: 18/04/2019
 * @abstract: Added comments, indented code
 * @author:
 */

#ifndef TVWSMODEL_H
#define TVWSMODEL_H
#include "tvwspoint.h"
#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>
#include <QQmlEngine>

#include <QDebug>

class TVModel : public QAbstractListModel                  // creating custom model to encapsulate the data to be used in qml
{
    Q_OBJECT
public:
    TVModel(QObject *parent = Q_NULLPTR):QAbstractListModel(parent){
    }
    enum TvRoles {
        PositionRole = Qt::UserRole + 1,
        OACICodeRole,
        CountryCodeRole
    };

    Q_INVOKABLE void readFromCSV(const QString &filename){                  //read the data from csv file has number of column
        QFile file(filename);
        if(!file.open(QFile::ReadOnly | QFile::Text))                      //check if its open and read only
            return;
        QTextStream in(&file);                                             //creat txt stream
        while (!in.atEnd()) {
            QString line = in.readLine();                                  //read line
            QStringList elements = line.split(",");                        //split function split the data seperated by (,)
            if(elements.count()==6){                                       //check number of coulmn
                QString Tvid = elements[0];
                double power = elements[2].toDouble();                     //assign element 2 to power befor that convert to double
                int radius = elements[3].toInt();
                double longitude = elements[4].toDouble();                 //assign the element in 4 to longitude
                double latitude = elements[5].toDouble();                  //assign the element in 4 to longitude

                TvwPoint p(Tvid, power, radius, latitude, longitude);

                addPoint(p);
            }
        }
    }

    void addPoint(const TvwPoint &point){                              // add point with indexes to be access when we call the index
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        mPoints << point;
        endInsertRows();
    }

    int rowCount(const QModelIndex & parent = QModelIndex()) const{
        Q_UNUSED(parent)
        return mPoints.count();
    }

    QVariant data(const QModelIndex & index, int role=Qt::DisplayRole) const {
        if (index.row() < 0 || index.row() >= mPoints.count())
            return QVariant();

        const TvwPoint &point = mPoints[index.row()];
        if (role == PositionRole)
            return QVariant::fromValue(point.position());
        else if (role == OACICodeRole)
            return point.idCode();
        else if (role == CountryCodeRole)
            return point.countryCode();
        return QVariant();
    }

//    Q_INVOKABLE void removeItems() const{ }

protected:
    QHash<int, QByteArray> roleNames() const {                   //creat  a hash-table
        QHash<int, QByteArray> roles;
        roles[PositionRole] = "position";
        roles[OACICodeRole] = "id";
        roles[CountryCodeRole] = "power";
        return roles;
    }
private:
    QList<TvwPoint> mPoints;
};

#endif // TVMODEL_H
