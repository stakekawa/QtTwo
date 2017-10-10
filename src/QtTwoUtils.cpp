/*!
 *  \file QtTwoUtils.cpp
 *
 *  \brief This file contains the implementation of utility functions
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QApplication>
#include <QDesktopWidget>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QStandardItemModel>
#include "QtTwoDefines.h"
#include "QtTwoUtils.h"


void configureQPushButtons(QWidget* p_widget, const int p_width, const int p_height)
{
    if ((NULL != p_widget) &&
        (0 != p_width) &&
        (0 != p_height))
    {
        QList<QPushButton*> l_buttonsList = p_widget->findChildren<QPushButton*>();

        Q_FOREACH (QPushButton* l_button, l_buttonsList)
        {
            l_button->QTTWO_SIZE_FIXED(p_width, p_height);
        }
    }
}


void configureQComboBox(QWidget* p_widget, const int p_width, const int p_height)
{
    if ((NULL != p_widget) &&
        (0 != p_width) &&
        (0 != p_height))
    {
        QList<QComboBox*> l_combosList = p_widget->findChildren<QComboBox*>();

        Q_FOREACH (QComboBox* l_comboBox, l_combosList)
        {
            l_comboBox->QTTWO_SIZE_FIXED(p_width, p_height);

            for (int i=0; i<l_comboBox->count(); ++i)
            {
                l_comboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
            }

            l_comboBox->setEditable(true);
            l_comboBox->lineEdit()->setReadOnly(true);
            l_comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
        }
    }
}


void configureQSpinBox(QWidget* p_widget, const int p_width, const int p_height)
{
    if ((NULL != p_widget) &&
        (0 != p_width) &&
        (0 != p_height))
    {
        QList<QSpinBox*> l_spinsList = p_widget->findChildren<QSpinBox*>();

        Q_FOREACH (QSpinBox* l_spinBox, l_spinsList)
        {
            l_spinBox->QTTWO_SIZE_FIXED(p_width, p_height);
            l_spinBox->setAlignment(Qt::AlignCenter);
        }

        QList<QDoubleSpinBox*> l_dSpinsList = p_widget->findChildren<QDoubleSpinBox*>();

        Q_FOREACH (QDoubleSpinBox* l_dSpinBox, l_dSpinsList)
        {
            l_dSpinBox->QTTWO_SIZE_FIXED(p_width, p_height);
            l_dSpinBox->setAlignment(Qt::AlignCenter);
        }
    }
}


void configureQSpinBoxValues(QSpinBox*& p_spinBox, const int p_min, const int p_max, const int p_default, const int p_step)
{
    if (NULL != p_spinBox)
    {
        p_spinBox->setAlignment(Qt::AlignCenter);
        p_spinBox->setAccelerated(true);
        p_spinBox->setRange(p_min, p_max);
        p_spinBox->setValue(p_default);
        p_spinBox->setSingleStep(p_step);
    }
}


void configureQDoubleSpinBoxValues(QDoubleSpinBox*& p_spinBox, const double p_min, const double p_max, const double p_default, const double p_step, const int p_nDecimals)
{
    if (NULL != p_spinBox)
    {
        p_spinBox->setAlignment(Qt::AlignCenter);
        p_spinBox->setAccelerated(true);
        p_spinBox->setRange(p_min, p_max);
        p_spinBox->setValue(p_default);
        p_spinBox->setSingleStep(p_step);
        p_spinBox->setDecimals(p_nDecimals);
    }
}


void centerQWidgetOnScreen(QWidget* p_widget)
{
    if (NULL != p_widget)
    {
        const int   l_screenNumber = QApplication::desktop()->screenNumber(p_widget);
        const float l_screenWidth  = QApplication::desktop()->screenGeometry(l_screenNumber).width();
        const float l_screenHeight = QApplication::desktop()->screenGeometry(l_screenNumber).height();

        const float l_xPos = (l_screenWidth  - static_cast<float>(p_widget->width() )) / 2;
        const float l_yPos = (l_screenHeight - static_cast<float>(p_widget->height())) / 2;

        p_widget->QTTWO_MOVE(l_xPos, l_yPos);

    } /* end if (NULL != p_widget) */
}


void centerQWidgetOnWidget(QWidget* p_widget, const QWidget* p_widgetBelow)
{
    if ((NULL != p_widget) &&
        (NULL != p_widgetBelow))
    {
        const float l_xPos = static_cast<float>(p_widgetBelow->pos().rx()) + static_cast<float>(p_widgetBelow->width()  - p_widget->width() ) / 2;
        const float l_yPos = static_cast<float>(p_widgetBelow->pos().ry()) + static_cast<float>(p_widgetBelow->height() - p_widget->height()) / 2;

        p_widget->QTTWO_MOVE(l_xPos, l_yPos);

    } /* end if (NULL != p_widget) */
}


void disableQComboBoxItem(QComboBox* p_comboBox, const int p_index, const bool p_disabled)
{
    if ((NULL != p_comboBox) &&
        (p_comboBox->count() > p_index))
    {
        QStandardItemModel* l_itemModel = dynamic_cast<QStandardItemModel*>(p_comboBox->model());

        if (NULL != l_itemModel)
        {
            QStandardItem* l_item = l_itemModel->item(p_index);

            if (true == p_disabled)
            {
                l_item->setFlags(l_item->flags() & ~Qt::ItemIsEnabled);
            }
            else
            {
                l_item->setFlags(l_item->flags() |  Qt::ItemIsEnabled);
            }

        } /* end if (NULL != l_itemModel) else */

    } /* end if ((NULL != p_comboBox) && */

}


void showNonModalQWidget(QWidget* p_widget, const bool p_setDeleteOnClose)
{
    if (NULL != p_widget)
    {
        p_widget->setAttribute(Qt::WA_DeleteOnClose, p_setDeleteOnClose);
        p_widget->setWindowModality(Qt::ApplicationModal);
        p_widget->show();
    }
}


void setQWidgetTextColor(const QColor& p_color, QWidget* p_widget)
{
    if (NULL != p_widget)
    {
        QPalette l_palette = p_widget->palette();

        l_palette.setBrush(QPalette::Normal, QPalette::Text,       p_color);
        l_palette.setBrush(QPalette::Normal, QPalette::WindowText, p_color);

        p_widget->setPalette(l_palette);
    }
}
