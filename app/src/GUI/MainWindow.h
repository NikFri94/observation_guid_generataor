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

#include "../../res/GUI/ui_MainWindow.h"

#include "NewFileDialog/NewFileDialog.h"

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

	private slots:
		void newFile(); //!< Slot for action "New file"

	private:
		Ui::MainWindow m_MainWindowGUI; //!< UI-Resource for MainWindow
	};
}