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


QT_BEGIN_NAMESPACE


/*!
 *  \brief The QTabHorizontalLabelsProxyStyle class implements a style for the
 *         QTabWidget to allow to have horizontal aligned labels on tabs on
 *         East and West.
 *
 *         How to use:
 *         QTabWidget* tabW;
 *         tabW->tabBar()->setStyle(new QTabHorizontalLabelsProxyStyle());
 */
class Q_WIDGETS_EXPORT QTabHorizontalLabelsProxyStyle : public QProxyStyle
{
    Q_OBJECT


public:

    explicit QTabHorizontalLabelsProxyStyle(QStyle* p_style = Q_NULLPTR);

    virtual ~QTabHorizontalLabelsProxyStyle();

    QSize sizeFromContents(ContentsType p_type, const QStyleOption* p_option, const QSize& p_size, const QWidget* p_widget) const Q_DECL_OVERRIDE;

    void drawControl(ControlElement p_element, const QStyleOption* p_option, QPainter* p_painter, const QWidget* p_widget) const Q_DECL_OVERRIDE;


private:

    Q_DISABLE_COPY(QTabHorizontalLabelsProxyStyle)


};


QT_END_NAMESPACE


#endif // QTABHORIZONTALLABELSPROXYSTYLE_H
