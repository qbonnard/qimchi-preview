#include "chilitagscamera.h"

#include <QPainter>
#include <QVideoRendererControl>
#include <myvideosurface.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

ChilitagsCamera::ChilitagsCamera(QQuickItem *parent)
  :  QQuickPaintedItem(parent)
  , m_camera(0)
  , m_myVideoSurface(0)
  , m_chilitags()
{
}

ChilitagsCamera::~ChilitagsCamera()
{
    freeResources();
}

void ChilitagsCamera::freeResources()
{
    if (m_myVideoSurface)
        m_myVideoSurface->stop();

    if (m_camera) {
        m_camera->stop();
        delete m_camera;
        m_camera = 0;
    }
}


void ChilitagsCamera::paint(QPainter *painter) {
    painter->fillRect(0,0,100,200,QColor(255,0,0));
    m_imageRect.moveCenter(boundingRect().center().toPoint());
    painter->drawImage(m_imageRect.topLeft(), m_targetImage);
}

bool ChilitagsCamera::updateItem(const QVideoFrame &frame)
{
    m_frame = frame;

    m_gray.create(m_frame.height(), m_frame.width(), CV_8UC1);
    if (m_frame.map(QAbstractVideoBuffer::ReadOnly)) {
        if (m_frame.pixelFormat() == QVideoFrame::Format_UYVY) {

            cv::Mat yuv(m_frame.height(), m_frame.width(), CV_8UC2, m_frame.bits());
            m_rgb.create(m_frame.height(), m_frame.width(), CV_8UC4);
            cv::cvtColor(yuv, m_rgb, CV_YUV2RGBA_UYVY);
            cv::cvtColor(yuv, m_gray, CV_YUV2GRAY_UYVY);

            m_targetImage = QImage(m_rgb.data, m_rgb.cols,
                                   m_rgb.rows, QImage::Format_RGB32);
        } else if (m_frame.pixelFormat() == QVideoFrame::Format_RGB32) {
            m_targetImage = QImage(m_frame.bits(), m_frame.width(),
                                   m_frame.height(), m_frame.bytesPerLine(),
                                   QImage::Format_RGB32);
        } else {

            m_targetImage = QImage();
        }

        update();

        m_imageRect = m_targetImage.rect();

        m_tags = m_chilitags.estimate(m_gray);
        emit inputUpdate();
        emit tagsChanged(tags());

        m_frame.unmap();
    }

    return true;
}

void ChilitagsCamera::start()
{
    freeResources();

    m_camera = new QCamera(QCamera::availableDevices()[0]);
    m_camera->load();

    m_myVideoSurface = new MyVideoSurface(this, this);

    QMediaService *mediaService = m_camera->service();
    QVideoRendererControl *rendererControl = mediaService->requestControl<QVideoRendererControl *>();
    rendererControl->setSurface(m_myVideoSurface);

    m_camera->start();
}
