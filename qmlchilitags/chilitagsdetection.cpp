#include "chilitagscamera.h"

#include <QVideoSurfaceFormat>

#include <QMediaObject>
#include <QMediaService>
#include <QVideoRendererControl>

//TODO: move conversion to chilitags
#include <opencv2/imgproc/imgproc.hpp>

ChilitagsCamera::ChilitagsCamera(QObject *parent)
      :  QAbstractVideoSurface(parent)
      , m_chilitags()
      , m_videoSurface(0)
    {
    }

ChilitagsCamera::~ChilitagsCamera(){}

QList<QVideoFrame::PixelFormat> ChilitagsCamera::supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType) const {
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                //adding this makes the framerate slower for some reason
                //<< QVideoFrame::Format_UYVY
                << QVideoFrame::Format_Y8
                << QVideoFrame::Format_BGR24;
    }
    return QList<QVideoFrame::PixelFormat>();
}

bool ChilitagsCamera::isFormatSupported(const QVideoSurfaceFormat &format) const {
    if (m_videoSurface) return m_videoSurface->isFormatSupported(format)
            && QAbstractVideoSurface::isFormatSupported(format);
    return QAbstractVideoSurface::isFormatSupported(format);
}

QVideoSurfaceFormat ChilitagsCamera::nearestFormat(const QVideoSurfaceFormat &) const
{
    qDebug() << "Not implemented: ChilitagsCamera::nearestFormat";
    return QVideoSurfaceFormat();
}


bool ChilitagsCamera::start(const QVideoSurfaceFormat &format) {
    QVideoSurfaceFormat outputFormat(format.frameSize(),
                                     QVideoFrame::Format_ARGB32);
    //if (m_videoSurface) {
    //    qDebug() << m_videoSurface->supportedPixelFormats();
    //    qDebug() << m_videoSurface->isFormatSupported(outputFormat);
    //    qDebug() << outputFormat;
    //}
    if (m_videoSurface) return m_videoSurface->start(outputFormat)
            && QAbstractVideoSurface::start(format);
    return QAbstractVideoSurface::start(format);
}

void ChilitagsCamera::stop() {
    if (m_videoSurface) m_videoSurface->stop();
    QAbstractVideoSurface::stop();
}


bool ChilitagsCamera::present(const QVideoFrame &frame) {

    //qDebug("time: %d", m_timer.elapsed());
    //qDebug("newFrame: %dx%d", frame.width(), frame.height());
    m_timer.restart();

    QVideoFrame copy = frame;
    //if (m_frame.pixelFormat() == QVideoFrame::Format_UYVY) {
    if (copy.map(QAbstractVideoBuffer::ReadOnly)) {
        const cv::Mat mat(copy.height(), copy.width(), CV_8UC3,
                          copy.bits());
        if (m_videoSurface) {
            m_converted.create(copy.height(), copy.width(), CV_8UC4);
            //FIXME: I thought we had BGR...
            cv::cvtColor(mat, m_converted, CV_RGB2RGBA);
        }

        m_tags = m_chilitags.estimate(mat);
        emit tagsChanged(tags());

        copy.unmap();
    }
    //qDebug("%lu tags", m_tags.size());

    if (m_videoSurface) {
        QImage image(m_converted.data,
                     m_converted.cols, m_converted.rows,
                     QImage::Format_ARGB32);
        return m_videoSurface->present(QVideoFrame(image));
    }

    return true;
}

void ChilitagsCamera::setSource(QObject *source) {
    m_timer.start();
    QVariant mediaObjectProperty = source->property("mediaObject");
    QMediaObject *mediaObject =
            qvariant_cast<QMediaObject *>(mediaObjectProperty);
    QMediaService *mediaService = mediaObject->service();
    QVideoRendererControl *rendererControl =
            mediaService->requestControl<QVideoRendererControl *>();
    rendererControl->setSurface(this);

    m_source = source;
}


Q_INVOKABLE QStringList ChilitagsCamera::tagIds() const {
    QStringList tagIds;
    for (auto tag : m_tags) {
        tagIds.append(QString::fromStdString(tag.first));
    }
    return tagIds;
}

Q_INVOKABLE bool ChilitagsCamera::isPresent(QString id) const {
    return m_tags.find(id.toStdString()) != m_tags.end();
}

Q_INVOKABLE QMatrix4x4 ChilitagsCamera::transform(QString id) const {
    auto it = m_tags.find(id.toStdString());
    if (it == m_tags.end()) return QMatrix4x4();
    float values[16];
    for (int i = 0; i<16; ++i) values[i] = it->second.val[i];
    return QMatrix4x4(values);
}

QVariantMap ChilitagsCamera::tags() const {
    QVariantMap tags;
    for (auto tag : m_tags) {
        QString id = QString::fromStdString(tag.first);
        tags.insert(id, transform(id));
    }
    return tags;
}
