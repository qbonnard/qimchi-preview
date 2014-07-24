#ifndef PROJECTEDORIGIN_H
#define PROJECTEDORIGIN_H

#include <QMatrix4x4>

class ProjectedOrigin : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMatrix4x4 transform READ transform NOTIFY transformChanged)
    Q_PROPERTY(float x READ x NOTIFY xChanged)
    Q_PROPERTY(float y READ y NOTIFY yChanged)
    Q_CLASSINFO("DefaultProperty", "transform")

public:
    explicit ProjectedOrigin(QObject *parent = 0)
        : QObject(parent)
    {
    }

    float x() const { return m_x;}
    float y() const { return m_y;}
    QMatrix4x4 transform() const { return m_transform;}

signals:
    void xChanged(float x);
    void yChanged(float y);
    void transformChanged(QMatrix4x4 transform);

public slots:

private:
    float m_x, m_y;
    QMatrix4x4 m_transform;
};

#endif // PROJECTEDORIGIN_H
