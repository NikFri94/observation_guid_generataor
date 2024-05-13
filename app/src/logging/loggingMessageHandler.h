/*!
 *
 *  @file      loggingMessageHandler.h
 *  @brief     Definition of the message-handler for overwriting the default Qt-Logging-Function
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#pragma once

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <iostream>

namespace OGG
{
	/*!
	 * @brief New message-handler for overwriting the default Qt-logging-function
	 * @param type 
	 * @param  
	 * @param strMessage 
	*/
	void LoggingMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& strMessage);
}