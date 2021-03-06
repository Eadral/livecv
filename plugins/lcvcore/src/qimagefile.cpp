#include "qimagefile.h"
#include "live/engine.h"
#include "live/exception.h"
#include "live/plugincontext.h"

#include "opencv2/highgui.hpp"

#include <QFileSystemWatcher>

QImageFile::QImageFile(QQuickItem *parent)
    : QMatDisplay(parent)
    , m_iscolor(CV_LOAD_IMAGE_COLOR)
    , m_monitor(false)
    , m_watcher(nullptr)
{
}

QImageFile::~QImageFile(){
    if ( m_watcher ){
        disconnect(m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(systemFileChanged()));
        m_watcher->deleteLater();
    }
}

void QImageFile::setSource(const QString &source){
    if (m_source == source)
        return;

    if ( m_watcher ){
        if ( !m_source.isEmpty() )
            m_watcher->removePath(m_source);

        if ( !source.isEmpty() )
            m_watcher->addPath(source);
    }

    m_source = source;
    emit sourceChanged();

    loadImage();
}

void QImageFile::setIscolor(int iscolor){
    if (m_iscolor != iscolor){
        m_iscolor = iscolor;
        emit iscolorChanged();
        loadImage();
    }
}

void QImageFile::setMonitor(bool monitor){
    if ( monitor ){
        if ( !m_watcher ){
            m_watcher = new QFileSystemWatcher;
            if ( !m_source.isEmpty() )
                m_watcher->addPath(m_source);
            connect(m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(systemFileChanged(QString)));
        }
    } else if ( m_watcher ){
        disconnect(m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(systemFileChanged(QString)));
        m_watcher->deleteLater();
        m_watcher = 0;
    }

    emit monitorChanged();
}

void QImageFile::systemFileChanged(const QString &){
    loadImage();
}

void QImageFile::open(const QString &file){
    setSource(file);
}


void QImageFile::componentComplete(){
    QQuickItem::componentComplete();
    emit init();
    loadImage();
}

void QImageFile::loadImage(){
    if ( m_source != "" && isComponentComplete() ){
        cv::Mat temp = cv::imread(m_source.toStdString(), m_iscolor);
        if ( temp.empty() ){
            lv::Exception e = CREATE_EXCEPTION(lv::Exception, "Cannot open file: " + m_source, 0);
            lv::PluginContext::engine()->throwError(&e);
            return;
        }

        temp.copyTo(*output()->cvMat());
        setImplicitWidth(output()->cvMat()->size().width);
        setImplicitHeight(output()->cvMat()->size().height);
        emit outputChanged();
        update();
    }
}
