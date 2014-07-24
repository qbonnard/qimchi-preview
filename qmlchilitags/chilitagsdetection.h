#ifndef CHILITAGSDETECTION_H
#define CHILITAGSDETECTION_H

#include <QQuickItem>

#include <chilitagssurface.h>
#include <QMatrix4x4>

//TODO: we don't need a QQuickItem here, just use
//Q_CLASSINFO("DefaultProperty", "objects")
class ChilitagsDetection : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QObject *source READ getSource WRITE setSource)
    //TODO: would a QMap<QString,QMatrix> do ?
    Q_PROPERTY(QVariantMap tags READ tags NOTIFY tagsChanged)
    Q_PROPERTY(QAbstractVideoSurface* videoSurface
               READ getVideoSurface WRITE setVideoSurface)

public:
    explicit ChilitagsDetection(QQuickItem *parent = 0);
    virtual ~ChilitagsDetection();


    QObject *getSource() const {  return m_source; }

    void setSource(QObject *source);


    QAbstractVideoSurface *getVideoSurface() const {
        return m_surface.getVideoSurface();
    }
    void setVideoSurface(QAbstractVideoSurface *videoSurface) {
        m_surface.setVideoSurface(videoSurface);
    }

    QVariantMap tags() const {return m_tags;}

    void setTags(const std::map<std::string, cv::Matx44d> &tags);

signals:
    void tagsChanged(QVariantMap tags);

public slots:

private:
    QObject *m_source;
    ChilitagsSurface m_surface;
    QVariantMap m_tags;
};

#endif // CHILITAGSDETECTION_H
