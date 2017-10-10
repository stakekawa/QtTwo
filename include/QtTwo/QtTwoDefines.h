/*!
 *  \file QtTwoDefines.h
 *
 *  \brief This file collects all Qt Two library definitions
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef QTTWODEFINES_H
#define QTTWODEFINES_H


#include <cassert> // assert
#include <QObject>


/*                                                                            */
/* Qt defines                                                                 */
/*                                                                            */
#define QTTWO_SIZE_FIXED(x, y)         setFixedSize(static_cast<int>((x)), static_cast<int>((y)))
#define QTTWO_SIZE_MIN(x, y)         setMinimumSize(static_cast<int>((x)), static_cast<int>((y)))
#define QTTWO_RESIZE(x, y)                   resize(static_cast<int>((x)), static_cast<int>((y)))
#define QTTWO_MOVE(x, y)                       move(static_cast<int>((x)), static_cast<int>((y)))
#define QTTWO_WIDTH_FIXED(x)          setFixedWidth(static_cast<int>((x)))
#define QTTWO_HEIGHT_FIXED(y)        setFixedHeight(static_cast<int>((y)))

#define QTTWO_SPACER_H         new QSpacerItem(k_marginNormal, k_marginNormal, QSizePolicy::Expanding, QSizePolicy::Minimum)
#define QTTWO_SPACER_V         new QSpacerItem(k_marginNormal, k_marginNormal, QSizePolicy::Minimum, QSizePolicy::Expanding)

#define QTTWO_CONNECT(x)                        assert(0 == QObject::connect(x))
#define QTTWO_TR(x)                                               QObject::tr(x)


#endif // QTTWODEFINES_H
