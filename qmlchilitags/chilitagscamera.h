#ifndef MYVIDEOOUTPUT_H
#define MYVIDEOOUTPUT_H

#include <QQuickPaintedItem>
#include <QCamera>
class MyVideoSurface;
#include "frameobserver.h"

#include <chilitags/chilitags.hpp>
#include <QMatrix4x4>

class ChilitagsCamera : public QQuickPaintedItem, public FrameObserver
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QSize frameSize READ frameSize NOTIFY frameSizeChanged)
    Q_PROPERTY(QVariantMap tags READ tags NOTIFY tagsChanged)

public:
    explicit ChilitagsCamera(QQuickItem *parent = 0);
    ~ChilitagsCamera();

    QString name() const {return m_name;}
    void setName(const QString &name) {m_name = name;}

    Q_INVOKABLE QStringList tagIds() const {
        QStringList tagIds;
        for (auto tag : m_tags) {
            tagIds.append(QString::fromStdString(tag.first));
        }
        return tagIds;
    }

    Q_INVOKABLE bool isPresent(QString id) const {
        return m_tags.find(id.toStdString()) != m_tags.end();
    }

    Q_INVOKABLE QMatrix4x4 transform(QString id) const {
        auto it = m_tags.find(id.toStdString());
        if (it == m_tags.end()) return QMatrix4x4();
        float values[16];
        for (int i = 0; i<16; ++i) values[i] = it->second.val[i];
        return QMatrix4x4(values);
    }

    QSize frameSize() const {return m_frameSize;}

    void paint(QPainter *painter);

    virtual bool updateItem(const QVideoFrame &frame);

    QVariantMap tags() const {
        QVariantMap tags;
        for (auto tag : m_tags) {
            QString id = QString::fromStdString(tag.first);
            tags.insert(id, transform(id));
        }
        return tags;
    }

signals:
    void frameSizeChanged();
    void inputUpdate();
    void tagsChanged(QVariantMap tags);

public slots:
    void start();

private:
    void freeResources();

    QString m_name;

    QCamera *m_camera;
    MyVideoSurface *m_myVideoSurface;

    cv::Mat m_gray, m_rgb;
    chilitags::Chilitags3D m_chilitags;
    std::map<std::string, cv::Matx44d> m_tags;

    QVideoFrame m_frame;
    QImage m_targetImage;
    QRect m_imageRect;
    QSize m_frameSize;
};

#endif // MYVIDEOOUTPUT_H
