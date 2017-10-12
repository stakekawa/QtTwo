/*!
 *  \file QCenteredComboBox.h
 *
 *  \brief This file contains the declaration of QCenteredComboBox class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QEvent>
#include <QLineEdit>
#include "QCenteredComboBox.h"


QT_BEGIN_NAMESPACE


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
QCenteredComboBox::QCenteredComboBox(QWidget* p_parent /* = 0 */) :
    QComboBox(p_parent)
{
    QComboBox::setEditable(true);
    QComboBox::lineEdit()->setReadOnly(true);
    QComboBox::lineEdit()->setAlignment(Qt::AlignHCenter);

    QPalette l_palette = QComboBox::palette();

    l_palette.setBrush(QPalette::Base,     l_palette.brush(QPalette::Window));
    l_palette.setBrush(QPalette::Button,   l_palette.brush(QPalette::Window));
    l_palette.setBrush(QPalette::Light,    l_palette.brush(QPalette::Window));
    l_palette.setBrush(QPalette::Midlight, l_palette.brush(QPalette::Window));
    l_palette.setBrush(QPalette::Dark,     l_palette.brush(QPalette::Window));
    l_palette.setBrush(QPalette::Mid,      l_palette.brush(QPalette::Window));
    l_palette.setBrush(QPalette::Shadow,   l_palette.brush(QPalette::Window));

    QComboBox::setPalette(l_palette);
    QComboBox::lineEdit()->setPalette(l_palette);

    QComboBox::lineEdit()->installEventFilter(this);
}


/* virtual */
QCenteredComboBox::~QCenteredComboBox()
{

}


/* virtual */
void QCenteredComboBox::addItem(const QString& p_text, const QVariant& p_data /* = QVariant() */)
{
    QComboBox::addItem(p_text, p_data);

    for (int i = 0; i < QComboBox::count(); ++i)
    {
        QComboBox::setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}


/*                                                                            */
/* Protected members                                                          */
/*                                                                            */


/* virtual */
bool QCenteredComboBox::eventFilter(QObject* p_object, QEvent* p_event)
{
    bool l_return = true;

    if ((NULL != p_event) &&
        (QEvent::MouseButtonRelease == p_event->type()))
    {
        QComboBox::showPopup();
    }
    else
    {
        l_return = QObject::eventFilter(p_object, p_event);
    }

    return l_return;
}


QT_END_NAMESPACE
