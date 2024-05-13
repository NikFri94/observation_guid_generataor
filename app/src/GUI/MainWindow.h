/*!
 *
 *  @file      MainWindow.h
 *  @brief     Definition of the MainWindow-Class
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#pragma once

#include <QMainWindow>

namespace OGG
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		/*!
		 * @brief Default constructor
		 * @param parent 
		*/
		MainWindow(QWidget* parent = nullptr);
	};
}