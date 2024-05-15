/*!
 *
 *  @file      ObservationGuideGenerator.h
 *  @brief     This file contains the definition of the applications main class.
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#pragma once

#include <QApplication>
#include <QDebug>

#include "GUI/MainWindow.h"
#include "ProjectSystem/Observation.h"

namespace OGG
{
	/*!
	 * @brief Main class of the applications
	 * @details This class captures the main program flow
	*/
	class ObservationGuideGenerator : public QApplication
	{
		Q_OBJECT

	public:
		/*!
		 * @brief Constructor
		 * @param argc Applications start argument count
		 * @param argv List of applications start arguments
		*/
		ObservationGuideGenerator(int& argc, char* argv[]);

		/*!
		 * @brief Default destructor
		*/
		~ObservationGuideGenerator();

	public slots:
		void createNewObservation(); //!< Slot for creating a new observation by using the NewObservation-Dialog

	private:
		MainWindow* m_MainWindow;	 //!< Applications Main-Window 

		Observation* m_currentObservation = nullptr; //!< Currently used observation
	};
}