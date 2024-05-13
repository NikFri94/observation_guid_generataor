/*!
 *
 *  @file      loggingMessageHandler.cpp
 *  @brief     Implementation of the new logging-message-handler
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "loggingMessageHandler.h"

namespace OGG
{
	void LoggingMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& strMessage)
	{
		QString txt;

		switch (type)
		{
		case QtDebugMsg:
#ifndef QGG_DIST
			txt = QString("[DBG] %1").arg(strMessage);
#endif
			break;
		case QtWarningMsg:
			txt = QString("[WRN] %1").arg(strMessage);
			break;
		case QtCriticalMsg:
			txt = QString("[CEM] %1").arg(strMessage);
			break;
		case QtFatalMsg:
			txt = QString("[FEM] %1").arg(strMessage);
			break;
		case QtInfoMsg:
			txt = QString("[INF] %1").arg(strMessage);
			break;
		default:
			txt = QString("[UKN] %1").arg(strMessage);
			break;
		}

		QFile outFile("logfile.txt");
		outFile.open(QIODevice::WriteOnly | QIODevice::Append);
		QTextStream ts(&outFile);
		ts << txt << "\n";
		outFile.close();

		// Zusätzlich: Standard-Out wenn nicht in DIST-Mode
#ifndef QGG_DIST
		std::cout << txt.toStdString() << std::endl;
#endif
	}
}

