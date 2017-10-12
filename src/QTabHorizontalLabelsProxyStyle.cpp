/*!
 *  \file QTabHorizontalLabelsProxyStyle.h
 *
 *  \brief This file contains the implementation of the QTabHorizontalLabelsProxyStyle class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include "QTabHorizontalLabelsProxyStyle.h"


QT_BEGIN_NAMESPACE


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


QTabHorizontalLabelsProxyStyle::QTabHorizontalLabelsProxyStyle(QStyle* p_style) :
    QProxyStyle(p_style)
{

}


QTabHorizontalLabelsProxyStyle::~QTabHorizontalLabelsProxyStyle()
{

}


/* virtual */
QSize QTabHorizontalLabelsProxyStyle::sizeFromContents(ContentsType p_type, const QStyleOption* p_option, const QSize& p_size, const QWidget* p_widget) const
{
    QSize l_s = QProxyStyle::sizeFromContents(p_type, p_option, p_size, p_widget);

    if (p_type == QStyle::CT_TabBarTab)
    {
        l_s.transpose();
    }

    return l_s;
}


/* virtual */
void QTabHorizontalLabelsProxyStyle::drawControl(ControlElement p_element, const QStyleOption* p_option, QPainter* p_painter, const QWidget* p_widget) const
{
    if (CE_TabBarTabLabel == p_element)
    {
        const QStyleOptionTab* l_tab = qstyleoption_cast<const QStyleOptionTab*>(p_option);

        if (NULL != l_tab)
        {
            QStyleOptionTab l_opt(*l_tab);
            l_opt.shape = QTabBar::RoundedNorth;
            QProxyStyle::drawControl(p_element, &l_opt, p_painter, p_widget);
            return;
        }
    }

    QProxyStyle::drawControl(p_element, p_option, p_painter, p_widget);
}


QT_END_NAMESPACE
