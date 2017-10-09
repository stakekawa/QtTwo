/*!
 *  \file QCenteredComboBox.h
 *
 *  \brief This file contains the declaration of QCenteredComboBox class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef QCENTEREDCOMBOBOX_H
#define QCENTEREDCOMBOBOX_H


#include <QComboBox>


/*!
 *  \brief The QCenteredComboBox class is a QComboBox which automatically keeps
 *         each item with Qt::AlignCenter alignment.
 */
class QCenteredComboBox : public QComboBox
{
    Q_OBJECT


public:

    explicit QCenteredComboBox(QWidget* p_parent = 0);

    virtual ~QCenteredComboBox();

    virtual void addItem(const QString& p_text, const QVariant& p_data = QVariant());


protected:

    bool eventFilter(QObject* p_object, QEvent* p_event) override;


};


#endif // QCENTEREDCOMBOBOX_H
