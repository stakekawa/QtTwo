/*!
 *  \file QtTwoUtils.h
 *
 *  \brief This file collects declaration of utility functions
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef QTTWOUTILS_H
#define QTTWOUTILS_H


#include <functional> // std::function
#include <QLayout>
#include <QMessageBox>
#include <QWidget>


QT_BEGIN_NAMESPACE


class QComboBox;
class QDoubleSpinBox;
class QObject;
class QSpinBox;


/*!
 *  \brief Configure all the QPushButton of a widget
 *
 *  \param p_widget pointer to the QWidget whose QPushButton have to be configured
 *  \param p_width width of QPushButton
 *  \param p_height height of QPushButton
 */
void configureQPushButtons(QWidget* p_widget, const int p_width, const int p_height);


/*!
 *  \brief Configure all the QComboBox of a widget
 *
 *  \param p_widget pointer to the QWidget whose QComboBox have to be configured
 *  \param p_width width of QComboBox
 *  \param p_height height of QComboBox
 */
void configureQComboBox(QWidget* p_widget, const int p_width, const int p_height);


/*!
 *  \brief Configure all the QSpinBox and QDoubleSpinBox of a widget
 *
 *  \param p_widget pointer to the QWidget whose QComboBox and QDoubleSpinBox have to be configured
 *  \param p_width width of QSpinBox
 *  \param p_height height of QSpinBox
 */
void configureQSpinBox(QWidget* p_widget, const int p_width, const int p_height);


/*!
 *  \brief Configure a QSpinBox with range values, default value, step value
 *  \param p_spinBox
 *  \param p_min
 *  \param p_max
 *  \param p_default
 *  \param p_step
 */
void configureQSpinBoxValues(QSpinBox*& p_spinBox, const int p_min, const int p_max, const int p_default, const int p_step);


/*!
 *  \brief Configure a QDoubleSpinBox with range values, default value, step value
 *  \param p_spinBox
 *  \param p_min
 *  \param p_max
 *  \param p_default
 *  \param p_step
 *  \param p_nDecimals
 */
void configureQDoubleSpinBoxValues(QDoubleSpinBox*& p_spinBox, const double p_min, const double p_max, const double p_default, const double p_step, const int p_nDecimals);


/*!
 *  \brief Configure a QObject blocking its signals and restoring its signaling status
 *
 *  \param p_object
 *  \param p_function
 */
inline void configureNotSignaling(QObject* p_object, const std::function<void()>& p_function)
{
    if (NULL != p_object)
    {
        const bool p_previousState = p_object->blockSignals(true);

        p_function();

        static_cast<void>(p_object->blockSignals(p_previousState));
    }
}


/*!
 *  \brief Center the QWidget on the center of the screen
 *
 *  \param p_widget pointer to the QWidget to center
 */
void centerQWidgetOnScreen(QWidget* p_widget);


/*!
 *  \brief Center the QWidget on the center of given widget
 *
 *  \param p_widget pointer to the QWidget to center
 *  \param p_widgetBelow pointer to the QWidget to center on
 *
 */
void centerQWidgetOnWidget(QWidget* p_widget, const QWidget* p_widgetBelow);


/*!
 *  \brief Disable an item in a QComboBox
 *
 *  \param p_comboBox pointer to QComboBox
 *  \param p_index index of the item to be disabled
 *  \param p_disabled true to disable, false to enable
 */
void disableQComboBoxItem(QComboBox* p_comboBox, const int p_index, const bool p_disabled);


/*!
 *  \brief Show a QWidget non blocking the background QWidgets
 *
 *  \param p_widget pointer to QWidget
 *  \param p_setDeleteOnClose set true if the modal widget should be deleted when it is closed
 */
void showNonModalQWidget(QWidget* p_widget, const bool p_setDeleteOnClose);


/*!
 *  \brief Set the color of text of a QWidget
 */
void setQWidgetTextColor(const QColor& p_color, QWidget* p_widget);


/*!
 *  \brief Properly delete a QWidget and set the pointer the NULL
 */
template <typename T_Widget>
inline void deleteWidget(T_Widget*& p_widget)
{
    QWidget* l_widget = dynamic_cast<QWidget*>(p_widget);

    if (NULL != l_widget)
    {
        l_widget->disconnect();

        if ((NULL != l_widget->parentWidget()) &&
            (NULL != l_widget->parentWidget()->layout()))
        {
            l_widget->parentWidget()->layout()->removeWidget(l_widget);
        }

        l_widget->setParent(NULL);
        delete l_widget;
        p_widget = NULL; /* this is right: set the function parameter to NULL */
    }
}


/*!
 *  \brief Show a QMessageBox
 *
 *  \param p_windowTitle title of the window
 *  \param p_iconEnum icon to show
 *  \param p_text text to show
 *  \param p_informativeText informative text to show
 */
void showQMessage(const QString& p_windowTitle, const QMessageBox::Icon p_iconEnum, const QString& p_text, const QString& p_informativeText, QWidget* p_parent = 0);


/*!
 *  \brief Show a warning QMessageBox
 *
 *  \param p_windowTitle title of the window
 *  \param p_text text to show
 *  \param p_informativeText informative text to show
 */
inline void showQMessageWarning(const QString& p_text, const QString& p_informativeText, QWidget* p_parent = 0)
{
    showQMessage(QObject::tr("Warning"), QMessageBox::Warning, p_text, p_informativeText, p_parent);
}


/*!
 *  \brief Show an error QMessageBox
 *
 *  \param p_windowTitle title of the window
 *  \param p_text text to show
 *  \param p_informativeText informative text to show
 */
inline void showQMessageError(const QString& p_text, const QString& p_informativeText, QWidget* p_parent = 0)
{
    showQMessage(QObject::tr("Error"), QMessageBox::Critical, p_text, p_informativeText, p_parent);
}


/*!
 *  \brief Show an informative QMessageBox
 *
 *  \param p_windowTitle title of the window
 *  \param p_text text to show
 *  \param p_informativeText informative text to show
 */
inline void showQMessageInfo(const QString& p_text, const QString& p_informativeText, QWidget* p_parent = 0)
{
    showQMessage(QObject::tr("Info"), QMessageBox::Information, p_text, p_informativeText, p_parent);
}


QT_END_NAMESPACE


#endif // QTTWOUTILS_H
