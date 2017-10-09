/*!
 *  \file QTabHorizontalLabelsProxyStyle.h
 *
 *  \brief This file contains the declaration of the QTabHorizontalLabelsProxyStyle class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef QTABHORIZONTALLABELSPROXYSTYLE_H
#define QTABHORIZONTALLABELSPROXYSTYLE_H


#include <QProxyStyle>
#include <QStyleOption>


/*!
 *  \brief The QTabHorizontalLabelsProxyStyle class implements a style for the
 *         QTabWidget to allow to have horizontal aligned labels on tabs on
 *         East and West.
 *
 *         How to use:
 *         QTabWidget* tabW;
 *         tabW->tabBar()->setStyle(new QTabHorizontalLabelsProxyStyle());
 */
class QTabHorizontalLabelsProxyStyle : public QProxyStyle
{
    Q_OBJECT


public:

    explicit QTabHorizontalLabelsProxyStyle(QStyle* p_style = 0);

    virtual ~QTabHorizontalLabelsProxyStyle();

    virtual QSize sizeFromContents(ContentsType p_type, const QStyleOption* p_option, const QSize& p_size, const QWidget* p_widget) const;

    virtual void drawControl(ControlElement p_element, const QStyleOption* p_option, QPainter* p_painter, const QWidget* p_widget) const;


};


#endif // QTABHORIZONTALLABELSPROXYSTYLE_H
