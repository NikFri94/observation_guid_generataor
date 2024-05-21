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

#include <memory>

#include <QMainWindow>
#include <QDialogButtonBox>

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
		void newFile(); //!< Event handler for Menu->File->NewFile

		void NewFileDlgOnApply(); //!< Slot for action "New file"
		void NewFileDlgOnCancel(); //!< Slot for cancelling the new file dialog

	private:
		Ui::MainWindow m_MainWindowGUI; //!< UI-Resource for MainWindow

		// Dialogs
		std::unique_ptr<NewFileDlg> m_NewFileDlg;
	};
}