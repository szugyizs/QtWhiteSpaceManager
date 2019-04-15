#ifndef TVWSMODEL_H
#define TVWSMODEL_H
#include "tvwspoint.h"
#include <QAbstractListModel>
#include <QFile>
#include <QTextStream>

#include <QDebug>

class TVModel : public QAbstractListModel
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

    Q_INVOKABLE void readFromCSV(const QString &filename){
        QFile file(filename);
        if(!file.open(QFile::ReadOnly | QFile::Text))
            return;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList elements = line.split(",");
            if(elements.count()==6){
                QString Tvid = elements[0];
                double power = elements[2].toDouble();
                int radius = elements[3].toInt();
                double longitude = elements[4].toDouble();
                double latitude = elements[5].toDouble();
                TvwPoint p(Tvid, power, radius, latitude, longitude);
               addPoint(p);
            }
        }
    }

    void addPoint(const TvwPoint &point){
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

protected:
    QHash<int, QByteArray> roleNames() const {
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
