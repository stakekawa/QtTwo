/*!
 *  \file QUnixSignalCatcher.h
 *
 *  \brief This file contains the declaration of QUnixSignalCatcher class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef QTTWO_QUNIXSIGNALCATHER_H
#define QTTWO_QUNIXSIGNALCATHER_H


#include <QObject>
#include <QSocketNotifier>


QT_BEGIN_NAMESPACE


/*!
 *  \brief The QUnixSignalCatcher is class wrapping functionality to catch Unix signals
 */
class Q_CORE_EXPORT QUnixSignalCatcher : public QObject
{
    Q_OBJECT


public:

    /*!
     *  \enum UnixSignalEnum maps the Unix signal handled by QUnixSignalCatcher
     */
    enum UnixSignalEnum
    {
        UnixSignalHup,  /*!< Signal SIGHUP                  */
        UnixSignalInt,  /*!< Signal SIGINT                  */
        UnixSignalTerm, /*!< Signal SIGTERM                 */
        UnixSignalSize  /*!< Number of handled Unix signals */
    };

    /*!
     *  \brief Constructor
     */
    explicit QUnixSignalCatcher(QObject* p_parent = Q_NULLPTR);

    /*!
     *  \brief Destructor
     */
    virtual ~QUnixSignalCatcher();

    /*!
     *  \brief Function registered with SIGHUP signal
     */
    static void UnixSignalHupHandler(int);

    /*!
     *  \brief Function registered with SIGINT signal
     */
    static void UnixSignalIntHandler(int);

    /*!
     *  \brief Function registered with SIGTERM signal
     */
    static void UnixSignalTermHandler(int);

    /*!
     *  \brief Function to register Unix signals
     */
    static int SetupUnixSignalHandlers();


private Q_SLOTS:

    /*!
     *  \brief Function called when the SIGHUP is signalled
     */
    void HandleUnixSignalHup()  { HandleUnixSignal(UnixSignalHup);  }

    /*!
     *  \brief Function called when the SIGINT is signalled
     */
    void HandleUnixSignalInt()  { HandleUnixSignal(UnixSignalInt);  }

    /*!
     *  \brief Function called when the SIGTERM is signalled
     */
    void HandleUnixSignalTerm() { HandleUnixSignal(UnixSignalTerm); }

    /*!
     *  \brief Function called when the a Unix signal is signalled
     */
    void HandleUnixSignal(const UnixSignalEnum p_signal);


Q_SIGNALS:

    /*!
     *  \brief Signal emitted when the SIGHUP is handled
     */
    void SignalHup();

    /*!
     *  \brief Signal emitted when the SIGINT is handled
     */
    void SignalInt();

    /*!
     *  \brief Signal emitted when the SIGTERM is handled
     */
    void SignalTerm();

    /*!
     *  \brief Signal emitted when a Unix signal is handled
     */
    void Signal(const UnixSignalEnum p_signal);


private:

    Q_DISABLE_COPY(QUnixSignalCatcher)

    QSocketNotifier* m_socketNotifier[UnixSignalSize];


};


QT_END_NAMESPACE


#endif // QTTWO_QUNIXSIGNALCATHER_H
