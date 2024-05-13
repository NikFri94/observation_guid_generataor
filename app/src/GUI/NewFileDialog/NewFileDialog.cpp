/*!
 *
 *  @file      NewFileDialog.cpp
 *  @brief     Implementation of the new file dialog.
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "NewFileDialog.h"

namespace OGG
{
	NewFileDlg::NewFileDlg(QWidget* parent)
	{
		qDebug() << "Start loading the New File Dialog...";

		// Load Dialog from resource file
		this->m_UI.setupUi(this);

		qDebug() << "New File Dialog started successfully.";
	}
}
