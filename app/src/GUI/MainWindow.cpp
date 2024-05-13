/*!
 *
 *  @file      MainWindow.cpp
 *  @brief     Implementation of the MainWindow-Class
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "MainWindow.h"

namespace OGG
{
	MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent)
	{
		qDebug() << "Start loading the MainWindow...";

		// Load the UI from ui-file
		this->m_MainWindowGUI.setupUi(this);

		qDebug() << "MainWindow-Components successfully loaded.";
	}

	/*!
	 * @brief Slot for Action "New File"
	*/
	void MainWindow::newFile()
	{
		qDebug() << "actNewFile Triggered";

		// Create and show "New File"-Dialog
		NewFileDlg* dlg = new NewFileDlg(this);
		dlg->setModal(true);
		dlg->show();
	}
}
