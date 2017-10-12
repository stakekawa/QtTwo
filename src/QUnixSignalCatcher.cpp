/*!
 *  \file QUnixSignalCatcher.cpp
 *
 *  \brief This file contains the implementation of QUnixSignalCatcher class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <csignal>
#include <sys/types.h>
#include <sys/socket.h>
#include "unistd.h"
#include "QtTwoDefines.h"
#include "QUnixSignalCatcher.h"


QT_BEGIN_NAMESPACE


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr int k_socketArraySize = 2;
static           int s_signalSockets[QUnixSignalCatcher::UnixSignalSize][k_socketArraySize] = { {0, 0}, {0, 0}, {0, 0} };

static QMetaObject::Connection s_connections[QUnixSignalCatcher::UnixSignalSize];


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
QUnixSignalCatcher::QUnixSignalCatcher(QObject* p_parent) :
    QObject(p_parent),
    m_socketNotifier()
{
    qRegisterMetaType<UnixSignalEnum>("UnixSignalEnum");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, s_signalSockets[UnixSignalHup]))  { qFatal("Couldn't create HUP socketpair");  }
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, s_signalSockets[UnixSignalInt]))  { qFatal("Couldn't create INT socketpair");  }
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, s_signalSockets[UnixSignalTerm])) { qFatal("Couldn't create TERM socketpair"); }

    for (int i = 0; i < UnixSignalSize; ++i)
    {
        m_socketNotifier[i] = new QSocketNotifier(s_signalSockets[i][1], QSocketNotifier::Read, this);
    }

    s_connections[UnixSignalHup ] = QTTWO_CONNECT4(m_socketNotifier[UnixSignalHup ], SIGNAL(activated(int)), this, SLOT(HandleUnixSignalHup()));
    s_connections[UnixSignalInt ] = QTTWO_CONNECT4(m_socketNotifier[UnixSignalInt ], SIGNAL(activated(int)), this, SLOT(HandleUnixSignalInt()));
    s_connections[UnixSignalTerm] = QTTWO_CONNECT4(m_socketNotifier[UnixSignalTerm], SIGNAL(activated(int)), this, SLOT(HandleUnixSignalTerm()));

    SetupUnixSignalHandlers();
}


/* virtual */
QUnixSignalCatcher::~QUnixSignalCatcher()
{
    for (int i = 0; i < UnixSignalSize; ++i)
    {
        QTTWO_DISCONNECT(s_connections[i]);

        if (NULL != m_socketNotifier[i])
        {
            delete m_socketNotifier[i];
            m_socketNotifier[i] = NULL;
        }
    }
}


/* static */
void QUnixSignalCatcher::UnixSignalHupHandler(int)
{
    char a = 1;
    ::write(s_signalSockets[UnixSignalHup][0], &a, sizeof(a));
}


/* static */
void QUnixSignalCatcher::UnixSignalIntHandler(int)
{
    char a = 1;
    ::write(s_signalSockets[UnixSignalInt][0], &a, sizeof(a));
}


/* static */
void QUnixSignalCatcher::UnixSignalTermHandler(int)
{
    char a = 1;
    ::write(s_signalSockets[UnixSignalTerm][0], &a, sizeof(a));
}


/* static */
int QUnixSignalCatcher::SetupUnixSignalHandlers()
{
    struct sigaction l_hup;
    struct sigaction l_int;
    struct sigaction l_term;

    l_hup.sa_handler = QUnixSignalCatcher::UnixSignalHupHandler;
    sigemptyset(&l_hup.sa_mask);
    l_hup.sa_flags = 0;
    l_hup.sa_flags |= SA_RESTART;

    if (sigaction(SIGHUP, &l_hup, 0)) { return 1; }

    l_int.sa_handler = QUnixSignalCatcher::UnixSignalIntHandler;
    sigemptyset(&l_int.sa_mask);
    l_int.sa_flags |= SA_RESTART;

    if (sigaction(SIGINT, &l_int, 0)) { return 2; }

    l_term.sa_handler = QUnixSignalCatcher::UnixSignalTermHandler;
    sigemptyset(&l_term.sa_mask);
    l_term.sa_flags |= SA_RESTART;

    if (sigaction(SIGTERM, &l_term, 0)) { return 3; }

    return 0;
}


/*                                                                            */
/* Private slots                                                              */
/*                                                                            */


void QUnixSignalCatcher::HandleUnixSignal(const UnixSignalEnum p_signal)
{
    m_socketNotifier[p_signal]->setEnabled(false);

    char tmp;
    ::read(s_signalSockets[p_signal][1], &tmp, sizeof(tmp));

    switch (p_signal)
    {
        case UnixSignalHup:
            qDebug("Got HUP signal");
            emit SignalHup();
            break;
        case UnixSignalInt:
            qDebug("Got INT signal");
            emit SignalInt();
            break;
        case UnixSignalTerm:
            qDebug("Got TERM signal");
            emit SignalTerm();
            break;
        default:
            break;
    }

    emit Signal(p_signal);

    m_socketNotifier[p_signal]->setEnabled(true);
}



QT_END_NAMESPACE
