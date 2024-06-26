/*!
 *
 *  @file      ObservationGuideGenerator.cpp
 *  @brief     This file contains the implementation of the applications main class
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright � Niklas Frings, 2024. All right reserved.
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
		m_MainWindow = std::make_unique<MainWindow>();
		m_MainWindow->show();

		// Create a new Observation
		m_CurrentObservation = std::make_unique<Observation>();
		m_MainWindow->setCurrentObservationRef(m_CurrentObservation.get());
	}

	// Destrutcor implementation
	ObservationGuideGenerator::~ObservationGuideGenerator()
	{
		qInfo() << "Application will be quit.";
	}
}