/*!
 *
 *  @file      NewFileDialog.h
 *  @brief     Defines the new file dialog.
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#pragma once

#include <QDialog>

#include "../../../res/GUI/ui_NewFileDialog.h"
#include "../../ProjectSystem/Observation.h"

namespace OGG
{
	class NewFileDlg : public QDialog
	{
		Q_OBJECT

	public:
		/*!
		 * @brief Default constructor
		 * @param parent 
		*/
		NewFileDlg(QWidget* parent = nullptr);

	private:
		Ui::NewFileDialog m_UI;	 //!< UI From resource file
	};
}