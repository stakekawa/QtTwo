/*!
 *  \file QDpiHelper.h
 *
 *  \brief This file contains the declaration of QDpiHelper class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef QDPIHELPER_H
#define QDPIHELPER_H


class QWidget;


/*!
 *  \brief The QDpiHelper class is a service class for DPI aware app. Reference
 *         is a 1920 x 1080 screen size with 96 DPI.
 */
class QDpiHelper
{


public:

    /*!
     *  \brief Constructor
     */
    QDpiHelper();

    /*!
     *  \brief Destructor
     */
    ~QDpiHelper();

    /*!
     *  \brief Compute the current aspect ratio based on reference dpi
     *         and reference screen width
     */
    static void setAspectRatio(const QWidget* p_widget);

    /*!
     *  \brief Get the current aspect ratio
     */
    static float aspectRatio() { return s_aspectRatio; }

    /*!
     *  \brief Get the detected DPI of screen where the QWidget is shown
     */
    static int dpi(const QWidget* p_widget);


private:

    /*!
     *  \brief Copy constructor (deleted)
     */
    QDpiHelper(const QDpiHelper&) = delete;

    /*!
     *  \brief Copy assignment operator (deleted)
     */
    QDpiHelper& operator=(const QDpiHelper&) = delete;

    static float           s_aspectRatio;                  /*!< Ratio of the application w.r.t. to 96 dpi screen */

    static constexpr float s_referenceDpi = 96.;           /*!< Reference screen dpi                             */
    static constexpr float s_referenceScreenWidth = 1920.; /*!< Reference screen width                           */


};


#endif // QDPIHELPER_H
