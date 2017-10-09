/*!
 *  \file QDpiHelper.cpp
 *
 *  \brief This file contains the implementation of QDpiHelper class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QApplication>
#include <QDesktopWidget>
#include "QDpiHelper.h"


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr float k_aspectRatio = 1.;
float QDpiHelper::s_aspectRatio = k_aspectRatio;


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


QDpiHelper::QDpiHelper()
{

}


QDpiHelper::~QDpiHelper()
{

}


/* static */
void QDpiHelper::setAspectRatio(const QWidget* p_widget)
{
    if (NULL != p_widget)
    {
        /* aspect ratio should increase if the current dpi  */
        /* is gtreater w.r.t. the reference dpi             */

        const int l_screenNumber = QApplication::desktop()->screenNumber(p_widget);
        s_aspectRatio = k_aspectRatio * QApplication::desktop()->screen(l_screenNumber)->logicalDpiX() / s_referenceDpi;
    }
}


/* static */
int QDpiHelper::dpi(const QWidget* p_widget)
{
    const int l_screenNumber = QApplication::desktop()->screenNumber(p_widget);
    return QApplication::desktop()->screen(l_screenNumber)->logicalDpiX();
}
