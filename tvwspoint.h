#ifndef TVWSPOINT_H
#define TVWSPOINT_H

#include <QGeoCoordinate>
#include <QString>

class TvwPoint
{
public:
    TvwPoint(QString TVid, double power, int radius, double latitude, double longitude)
    {
        m_tvid = TVid;
        m_power =power;
        m_radius = radius;
        m_position.setLatitude(latitude);
        m_position.setLongitude(longitude);
        m_position.setAltitude(0.0);

    }

    void setPosition(const QGeoCoordinate &c) { //assign new coordinates
        m_position = c;
    }

    QGeoCoordinate position() const{
        return m_position;
    }

    QString idCode() const {
        return m_tvid;
    }

    QString countryCode() const {
        return m_type;
    }

private:
    QGeoCoordinate m_position;
    QString m_tvid;
    QString m_type;
    double m_power;
    int m_radius;
    double m_x;
    double m_y;
};

#endif // TVWSPOINT_H
