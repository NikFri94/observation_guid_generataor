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

		/*!
		 * @brief This function shows the dialog and fills out the given data structure if dialog is accepted.
		 * @param _data Pointer to the Observation-Object which should be filled with the new Data. If the object already has been ibnitialized, it will also be used for filling the dialog with the currently stored data.
		 * @param _showModal Set this to false if the dialog should not be shown as modal dialog.
		 * @return Returns true if the Dialog recieves the "accepted" sigbnal, otherwise it will be false.
		*/
		bool getNewObservation(Observation* _data ,bool _showModal = true);

	private:




		Ui::NewFileDialog m_UI;	 //!< UI From resource file
	};
}