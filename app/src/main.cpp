/*!
 *
 *  @file      main.cpp
 *  @brief     Haupteinstiegspunkt der Anwendung
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      10.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "logging/loggingMessageHandler.h"
#include "ObservationGuideGenerator.h"

int main(int argc, char* argv[])
{
	// Override the default Qt-debug-message-handler
	qInstallMessageHandler(OGG::LoggingMessageHandler);

	OGG::ObservationGuideGenerator app(argc, argv);

	return app.exec();
}