/*!
 *
 *  @file      ObservationGuideGenerator.cpp
 *  @brief     This file contains the implementation of the applications main class
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "ObservationGuideGenerator.h"

namespace OGG {
	// Constructor implementation
	ObservationGuideGenerator::ObservationGuideGenerator(int& argc, char* argv[])
		: QApplication(argc, argv)
	{
		qInfo() << "Starting the application...";

		// Initialize the main Window
		this->m_MainWindow = new MainWindow();
		this->m_MainWindow->show();
	}

	// Destrutcor implementation
	ObservationGuideGenerator::~ObservationGuideGenerator()
	{
		qInfo() << "Application will be quit.";
	}
}