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

#include <QList>
#include <QMainWindow>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextCursor>
#include <QTextTable>
#include <QTextDocumentWriter>
#include <QDate>
#include <QPrinter>
#include <QAbstractTextDocumentLayout>
#include <QMessageBox>

#include "../../res/GUI/ui_MainWindow.h"

#include "NewFileDialog/NewFileDialog.h"
#include "../ProjectSystem/BinaryObservationFile.h"

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

		inline void setCurrentObservationRef(Observation* pRef)
		{
			this->m_CurrentObservation = pRef;
		}

	protected:
		void parseObservationToDocumentView(); //!< Parse the currently loaded Observation-object to the document view

	private slots:
		void newFile(); //!< Event handler for Menu->File->NewFile
		void saveToFile(); //!< Event handler for Menu->File.-Save

		void exportToPdf(); //!< Export the current document to pdf
		void exportToHTML(); //!< For Test: Export to HTML file
		void exportToODF(); //!< Export to ODF-File

		void NewFileDlgOnApply(); //!< Slot for action "New file"
		void NewFileDlgOnCancel(); //!< Slot for cancelling the new file dialog

	private:
		Observation* m_CurrentObservation; //!< Reference to the currently loaded Observation

		Ui::MainWindow m_MainWindowGUI; //!< UI-Resource for MainWindow

		// Dialogs
		std::unique_ptr<NewFileDlg> m_NewFileDlg;
	};
}