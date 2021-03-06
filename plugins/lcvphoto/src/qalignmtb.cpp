#include "qalignmtb.h"
#include "live/engine.h"
#include "live/exception.h"
#include "live/plugincontext.h"

QAlignMTB::QAlignMTB(QObject *parent)
    : QObject(parent)
    , m_input(0)
    , m_output(new QMatList)
    , m_alignMTB(cv::createAlignMTB())
    , m_componentComplete(false)
{
}

QAlignMTB::~QAlignMTB(){
    delete m_output;
}

void QAlignMTB::componentComplete(){
    m_componentComplete = true;
    filter();
}

void QAlignMTB::setParams(const QVariantMap &params){
    if (m_params == params)
        return;

    m_params = params;
    emit paramsChanged();

    int maxBits = 6;
    int excludeRange = 4;
    bool cut = true;

    if ( params.contains("maxBits") )
        maxBits = params["maxBits"].toInt();
    if ( params.contains("excludeRange") )
        excludeRange = params["excludeRange"].toInt();
    if ( params.contains("cut") )
        cut = params["cut"].toInt();

    m_alignMTB = cv::createAlignMTB(maxBits, excludeRange, cut);

    filter();
}

void QAlignMTB::filter(){
    if ( m_componentComplete && m_input && m_input->size() > 0 && m_alignMTB ){
        try{
            std::vector<cv::Mat> result = m_output->asVector();
            m_alignMTB->process(m_input->asVector(), result);
            m_output->fromVector(result);
            emit outputChanged();
        } catch ( cv::Exception& e ){
            lv::Exception lve = CREATE_EXCEPTION(lv::Exception, e.what(), e.code);
            lv::PluginContext::engine()->throwError(&lve, this);
            return;
        }
    }
}

bool QAlignMTB::isComponentComplete(){
    return m_componentComplete;
}
