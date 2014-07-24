#ifndef CHILITAGSDETECTION_H
#define CHILITAGSDETECTION_H

#include <QAbstractVideoSurface>

#include <chilitags/chilitags.hpp>
#include <QMatrix4x4>

#include <QTime>

class ChilitagsDetection : public QAbstractVideoSurface
{
    Q_OBJECT
    Q_PROPERTY(QObject *source READ getSource WRITE setSource)
    Q_PROPERTY(QVariantMap tags READ tags NOTIFY tagsChanged)
    Q_PROPERTY(QAbstractVideoSurface* videoSurface
               READ getVideoSurface WRITE setVideoSurface)

public:
    explicit ChilitagsDetection(QObject *parent = 0);
    virtual ~ChilitagsDetection();

    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(
                QAbstractVideoBuffer::HandleType handleType =
                    QAbstractVideoBuffer::NoHandle) const;

    virtual bool isFormatSupported(const QVideoSurfaceFormat &format) const ;

    virtual QVideoSurfaceFormat nearestFormat(const QVideoSurfaceFormat &) const ;


    virtual bool start(const QVideoSurfaceFormat &format) ;

    virtual void stop() ;

    virtual bool present(const QVideoFrame &frame) ;


    QObject *getSource() const {  return m_source; }

    void setSource(QObject *source);


    QAbstractVideoSurface *getVideoSurface() const {
        return m_videoSurface;
    }
    void setVideoSurface(QAbstractVideoSurface *videoSurface) {
        m_videoSurface = videoSurface;
    }


    Q_INVOKABLE QStringList tagIds() const ;

    Q_INVOKABLE bool isPresent(QString id) const ;

    Q_INVOKABLE QMatrix4x4 transform(QString id) const ;

    QVariantMap tags() const ;

signals:
    void tagsChanged(QVariantMap tags);

public slots:

private:
    chilitags::Chilitags3D m_chilitags;
    std::map<std::string, cv::Matx44d> m_tags;

    QObject *m_source;
    cv::Mat m_converted;
    QAbstractVideoSurface* m_videoSurface;

    QTime m_timer;
};

#endif // CHILITAGSDETECTION_H
