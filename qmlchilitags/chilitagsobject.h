#ifndef ChilitagsObject_H
#define ChilitagsObject_H

#include <QQuickItem>
#include <QTransform>

#include <chilitags/chilitags.hpp>
#include <QMatrix4x4>

class ChilitagsObject : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QVariantMap tags READ tags WRITE tagUpdate)
    Q_PROPERTY(bool visible READ visible NOTIFY visibilityChanged)
    Q_PROPERTY(QMatrix4x4 transform READ transform NOTIFY transformChanged)
    Q_PROPERTY(QTransform translation READ translation NOTIFY translationChanged)
    Q_PROPERTY(float x READ x NOTIFY xChanged)
    Q_PROPERTY(float y READ y NOTIFY yChanged)

public:
    explicit ChilitagsObject(QQuickItem *parent = 0)
        : QQuickItem(parent)
    {
    }

    QString name() const {return m_name;}
    void setName(const QString &name) {m_name = name;}

    const QVariantMap & tags() const {return m_tags;}
    void tagUpdate(const QVariantMap & tags) {
        m_tags = tags;
        auto tagIt = tags.find(m_name);
        bool wasVisible = m_visible;
        m_visible = tagIt != tags.end();
        if (wasVisible != m_visible) emit visibilityChanged(m_visible);
        if (m_visible) {
            m_transform = tagIt->value<QMatrix4x4>();
            emit transformChanged(m_transform);
            auto data = m_transform.data();
            m_translation = QTransform::fromTranslate(data[12], data[13]);
            emit translationChanged(m_translation);
            m_x = data[12];
            m_y = data[13];
            emit xChanged(m_x);
            emit yChanged(m_y);
        }
    }

    bool visible() const {return m_visible;}
    QMatrix4x4 transform() const {return m_transform;}
    QTransform translation() const { return m_translation;}
    float x() const { return m_x;}
    float y() const { return m_y;}

signals:
    void visibilityChanged(bool visible);
    void transformChanged(QMatrix4x4 transform);
    void translationChanged(QTransform translation);
    void xChanged(float x);
    void yChanged(float y);

public slots:

private:
    QString m_name;
    QVariantMap m_tags;
    bool m_visible;
    QMatrix4x4 m_transform;
    QTransform m_translation;
    float m_x, m_y;
};

#endif
