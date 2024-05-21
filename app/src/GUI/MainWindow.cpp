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

	void MainWindow::NewFileDlgOnApply()
	{
		qDebug() << "APPLY";
	}

	/*!
	 * @brief Slot for handling the cancel-event of the New-File-Dialog
	*/
	void MainWindow::NewFileDlgOnCancel()
	{
		qDebug() << "Cancel new file dialog.";
		// Destroy the dialog object if initialized
		if (m_NewFileDlg.get() != nullptr)
			m_NewFileDlg.reset();
	}

	/*!
	 * @brief Slot for Action "New File"
	*/
	void MainWindow::newFile()
	{
		qDebug() << "actNewFile Triggered";

		// Create and show "New File"-Dialog
		m_NewFileDlg = std::make_unique<NewFileDlg>(this);
		m_NewFileDlg->setModal(true);
		m_NewFileDlg->show();

		// Initialize Signal-Slot-connections
		QDialogButtonBox* dlgBtBox = m_NewFileDlg->findChild<QDialogButtonBox*>(QString("btBox"), Qt::FindDirectChildrenOnly);

		connect(dlgBtBox, SIGNAL(rejected()),
			this, SLOT(NewFileDlgOnCancel()));
		connect(dlgBtBox, SIGNAL(accepted()),
			this, SLOT(NewFileDlgOnApply()));
		connect(m_NewFileDlg.get(), SIGNAL(rejected()),
			this, SLOT(NewFileDlgOnCancel()));
	}
}
