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

		// Initialize other fields
		m_CurrentObservation = nullptr;

		qDebug() << "MainWindow-Components successfully loaded.";
	}

	// Implementation of the parsing of the current observation in the central document widget
	void MainWindow::parseObservationToDocumentView()
	{
		qDebug() << "Start parsing the central document...";

		QTextEdit* edCentralDocument = this->findChild<QTextEdit*>(QString("edCentralDocument"));

		QTextDocument* doc = edCentralDocument->document();

		// Set page size and orientation
		QPrinter formatPrinter(QPrinter::PrinterResolution);
		formatPrinter.setPageSize(QPageSize::A4);
		formatPrinter.setPageOrientation(QPageLayout::Landscape);
		doc->setPageSize(formatPrinter.pageRect(QPrinter::Didot).size());

		// Set default font
		doc->setDefaultFont(QFont(QString("Arial"), 12));
		doc->clear();

		QTextCursor cursor(doc);

		cursor.insertTable(1, 5);
		cursor.insertHtml(QString("Projekt:<br>%1").arg(m_CurrentObservation->getProjectName()));
		cursor.movePosition(QTextCursor::NextCell);
		cursor.insertHtml(QString("Datum:<br>%1").arg(m_CurrentObservation->getDate().toString(QString("dd.MM.yyyy"))));
		cursor.movePosition(QTextCursor::NextCell);
		cursor.insertHtml(QString("Ort:<br>%1").arg(m_CurrentObservation->getLocation()));
		cursor.movePosition(QTextCursor::NextCell);
		cursor.insertHtml(QString("Position:<br>"));
		cursor.movePosition(QTextCursor::NextCell);
		cursor.insertHtml(QString("Beobachter:<br>"));
		cursor.insertBlock();

		cursor.movePosition(QTextCursor::End);

		int observationModuleCount = m_CurrentObservation->getObservationModulesLstPtr()->count();
		qDebug() << QString("There are %1 Observation-Modules to be included.").arg(observationModuleCount);

		// General observations
		for (int i = 0; i < observationModuleCount; i++)
		{
			if (m_CurrentObservation->getObservationModulesLstPtr()->at(i).topic == ObservationTopic::OT_GENERAL_DESCRIPTION)
			{
				if (m_CurrentObservation->getObservationModulesLstPtr()->at(i).documentationSystem == ObservationDocumentationSystem::ODS_TOP)
				{
					qDebug() << "General observations need to be documented in TOP-System.";

					QTextTable* generalObservationTable = cursor.insertTable(4, 3);
					cursor.insertHtml(QString("Kategorie"));
					cursor = generalObservationTable->cellAt(0, 1).firstCursorPosition();
					cursor.insertHtml(QString("Allgemeine Beschreibung vor Ort (<b>objektiv</b>)"));
					cursor = generalObservationTable->cellAt(0, 2).firstCursorPosition();
					cursor.insertHtml(QString("Allgemeine Eindr&uuml;cke (<b>subjektiv</b>"));
					cursor = generalObservationTable->cellAt(1, 0).firstCursorPosition();
					cursor.insertHtml(QString("Technische"));
					cursor = generalObservationTable->cellAt(2, 0).firstCursorPosition();
					cursor.insertHtml(QString("Organisatorisch"));
					cursor = generalObservationTable->cellAt(3, 0).firstCursorPosition();
					cursor.insertHtml(QString("Personell"));
					generalObservationTable->mergeCells(1, 2, 3, 1);
				}
				else
				{
					qDebug() << "General observations need to be documented without TOP-System.";

					QTextTable* generalObservationTable = cursor.insertTable(2,2);
					cursor = generalObservationTable->cellAt(0, 0).firstCursorPosition();
					cursor.insertHtml(QString("Allgemeine Beschreibung vor Ort (<b>objektiv</b>)"));
					cursor = generalObservationTable->cellAt(0, 1).firstCursorPosition();
					cursor.insertHtml(QString("Allgemeine Eindr&uuml;cke (<b>subjektiv</b>)"));
				}
			}
		}

		cursor.movePosition(QTextCursor::End);
		cursor.insertBlock();

		// Last: Create table for specific observations
		QList<ObservationDocumentationSystem> docSystemLst;
		int specialDocumentationSystemCounter = 0;

		for (int i = 0; i < observationModuleCount; i++)
		{
			if (!docSystemLst.contains(m_CurrentObservation->getObservationModulesLstPtr()->at(i).documentationSystem) &&
				(m_CurrentObservation->getObservationModulesLstPtr()->at(i).topic != ObservationTopic::OT_GENERAL_DESCRIPTION) &&
				(m_CurrentObservation->getObservationModulesLstPtr()->at(i).topic != ObservationTopic::OT_SUBJECTIVE_OBSERVATIONS))
			{
				if (m_CurrentObservation->getObservationModulesLstPtr()->at(i).documentationSystem != ObservationDocumentationSystem::ODS_NONE)
					specialDocumentationSystemCounter++;

				docSystemLst.append(m_CurrentObservation->getObservationModulesLstPtr()->at(i).documentationSystem);
			}
		}

		qDebug() << QString("There are %1 different documentation systems which need to be considered in the focused observation section.").arg(docSystemLst.count());
		qDebug() << QString("There are %1 special documentation systems which should be used.").arg(specialDocumentationSystemCounter);

		/*!
		* Temporarely: If there is more than one observation system: Error.
		* @todo Implementation of support for more than 1 special dcumentation system
		*/
		if (specialDocumentationSystemCounter > 1)
		{
			qCritical() << QString("Too many special documentation methods selected. Selected: %1, supported: 1").arg(specialDocumentationSystemCounter);
			QMessageBox::critical(this,
				QString("Error"),
				QString("Aktuell wird nur ein spezialisiertes Verfahren zur Dokumentation unterstützt, Sie haben jedoch %1 verfahren ausgefählt.").arg(specialDocumentationSystemCounter),
				QMessageBox::Ok);
			return;
		}

		if (observationModuleCount > 2)
		{
			if ((specialDocumentationSystemCounter == 1))
			{
				// There is one special documentation system which needs to be considered
				if (docSystemLst.contains(ObservationDocumentationSystem::ODS_TOP))
				{
					cursor.insertTable(5, observationModuleCount - 1);
				}
				else
				{
					// Use PDCA-System
					cursor.insertTable(6, observationModuleCount - 1);
				}
			}
			else
			{
				// Do not use any documentation system
				cursor.insertTable(3, observationModuleCount - 1);
			}
		}

		qDebug() << "Parsing finished.";
	}

	void MainWindow::saveToFile()
	{
		qDebug() << "Start saving current observation into binary file...";

		QString filename = QFileDialog::getSaveFileName(this, QString("Datei speichern unter..."), QDir::currentPath(), QString(BOF_FILE_POSTFIX));

		qDebug() << QString("Data will be saved to %1").arg(filename);

		qDebug() << "Saved.";
	}

	void MainWindow::exportToPdf()
	{
		/*!
		* @todo Final implementation
		*/

		QTextDocument* doc = this->findChild<QTextEdit*>(QString("edCentralDocument"))->document();

		QPrinter pdfPrinter(QPrinter::PrinterResolution);
		pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
		pdfPrinter.setPageSize(QPageSize::A4);
		pdfPrinter.setPageOrientation(QPageLayout::Landscape);
		pdfPrinter.setOutputFileName("test.pdf");

		doc->print(&pdfPrinter);
	}

	void MainWindow::exportToHTML()
	{
		QFile file(QString("test.html"));
		file.open(QIODevice::WriteOnly);
		QTextStream stream(&file);
		stream << this->findChild<QTextEdit*>(QString("edCentralDocument"))->document()->toHtml();
		file.close();
	}

	void MainWindow::exportToODF()
	{
		/*!
		* @todo Propper Implementation
		*/
		QTextDocumentWriter writer(QString("test.odf"), "ODF");
		writer.write(this->findChild<QTextEdit*>(QString("edCentralDocument"))->document());
		
		QTextDocumentWriter pdfWriter(QString("test2.pdf"), "PDF");
		pdfWriter.write(this->findChild<QTextEdit*>(QString("edCentralDocument"))->document());
	}

	void MainWindow::NewFileDlgOnApply()
	{
		qDebug() << "Start capturing and verifying New File-Dialog data...";

		// Get the Project name
		QLineEdit* edProjectName = m_NewFileDlg->findChild<QLineEdit*>(QString("edProjectName"));
		QString projectName = edProjectName->text();
		
		// Get the Date
		QDateEdit* edDate = m_NewFileDlg->findChild<QDateEdit*>(QString("deDate"));
		QDate date = edDate->date();

		// Get the location
		QLineEdit* edLocation = m_NewFileDlg->findChild<QLineEdit*>(QString("edLocation"));
		QString location = edLocation->text();

		// Get the main objective
		QTextEdit* edMainObjective = m_NewFileDlg->findChild<QTextEdit*>(QString("edMainObjective"));
		QString mainObjective = edMainObjective->toPlainText();

		// Get excluded Elements
		QTextEdit* edExclude = m_NewFileDlg->findChild<QTextEdit*>(QString("edExcluded"));
		QString excluded = edExclude->toPlainText();

		// Get the description of the observation object
		QTextEdit* edObservationObjectDescription = m_NewFileDlg->findChild<QTextEdit*>(QString("edObservationObjectDescription"));
		QString observationObjectDescr = edObservationObjectDescription->toPlainText();

		// Is the observation participational?
		QCheckBox* cbParticipational = m_NewFileDlg->findChild<QCheckBox*>(QString("cbParticipational"));
		bool isParticipational = cbParticipational->isChecked();

		// Is the observation undercover?
		QCheckBox* cbUndercover = m_NewFileDlg->findChild<QCheckBox*>(QString("cbUndercover"));
		bool isUndercover = cbUndercover->isChecked();

		// Is the observation systematically?
		QCheckBox* cbSystematic = m_NewFileDlg->findChild<QCheckBox*>(QString("cbSystematic"));
		bool isSystematically = cbSystematic->isChecked();

		// Is the observation in the field?
		QCheckBox* cbField = m_NewFileDlg->findChild<QCheckBox*>(QString("cbField"));
		bool isFieldObservation = cbField->isChecked();

		m_CurrentObservation->Initialize(projectName,
			date,
			location,
			mainObjective,
			excluded,
			observationObjectDescr,
			isParticipational,
			isUndercover,
			isSystematically,
			isFieldObservation);

		// Add the general description of the situation
		QComboBox* cbDescriptionSystematic = m_NewFileDlg->findChild<QComboBox*>(QString("cbDescriptionSystematic"));
		QTextEdit* edDescription = m_NewFileDlg->findChild<QTextEdit*>(QString("edDescription"));
		
		m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_GENERAL_DESCRIPTION,
			(cbDescriptionSystematic->currentText() == QString("Unsystematisch")) ? ObservationDocumentationSystem::ODS_NONE : ObservationDocumentationSystem::ODS_TOP,
			edDescription->toPlainText()));

		// Optional fields
		// Communication
		QComboBox* cbCommunicationSystematic = m_NewFileDlg->findChild<QComboBox*>(QString("cbCommunicationSystematic"));
		if (cbCommunicationSystematic->currentText() != QString("Nicht erfassen"))
		{
			ObservationDocumentationSystem odsCommunication;
			if (cbCommunicationSystematic->currentText() == QString("TOP"))
				odsCommunication = ObservationDocumentationSystem::ODS_TOP;
			else
				odsCommunication = ObservationDocumentationSystem::ODS_NONE;

			QTextEdit* edCommunicationHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edCommunicationHints"));
			m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_COMMUNICATION,
				odsCommunication,
				edCommunicationHints->toPlainText()));

			qDebug() << "Include communication with:";
			qDebug() << QString("    Documentation system: %1").arg(odsCommunication);
			qDebug() << QString("    Documentation hints:  %2").arg(edCommunicationHints->toPlainText());
		}
		else
		{
			qDebug() << "Communication will not be included.";
		}

		// Interaktion
		QComboBox* cbInteractionSystematic = m_NewFileDlg->findChild<QComboBox*>(QString("cbInteractionSystematic"));
		if (cbInteractionSystematic->currentText() != QString("Nicht erfassen"))
		{
			QTextEdit* edInteractionHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edInteractionHints"));
			m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_INTERACTION,
				ObservationDocumentationSystem::ODS_NONE,
				edInteractionHints->toPlainText()));

			qDebug() << "Include Interaction with:";
			qDebug() << QString("    Documentation system: %1").arg(ObservationDocumentationSystem::ODS_NONE);
			qDebug() << QString("    Documentation hints:  %2").arg(edInteractionHints->toPlainText());
		}
		else
		{
			qDebug() << "Interaction will not be included.";
		}

		// Activities
		QComboBox* cbActivities = m_NewFileDlg->findChild<QComboBox*>(QString("cbActivities"));
		if (cbCommunicationSystematic->currentText() != QString("Nicht erfassen"))
		{
			ObservationDocumentationSystem odsActivities;
			if (cbActivities->currentText() == QString("Kreisprozess"))
				odsActivities = ObservationDocumentationSystem::ODS_CIRCLE;
			else
				odsActivities = ObservationDocumentationSystem::ODS_NONE;

			QTextEdit* edActivitiesHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edActivitiesHints"));
			m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_ACTIVITIES,
				odsActivities,
				edActivitiesHints->toPlainText()));

			qDebug() << "Include Activities with:";
			qDebug() << QString("    Documentation system: %1").arg(odsActivities);
			qDebug() << QString("    Documentation hints:  %2").arg(edActivitiesHints->toPlainText());
		}
		else
		{
			qDebug() << "Activities will not be included.";
		}

		// Actions
		QComboBox* cbActions = m_NewFileDlg->findChild<QComboBox*>(QString("cbActions"));
		if (cbActions->currentText() != QString("Nicht erfassen"))
		{
			ObservationDocumentationSystem odsActions;
			if (cbActions->currentText() == QString("Kreisprozess"))
				odsActions = ObservationDocumentationSystem::ODS_CIRCLE;
			else if (cbActions->currentText() == QString("TOP"))
				odsActions = ObservationDocumentationSystem::ODS_TOP;
			else
				odsActions = ObservationDocumentationSystem::ODS_NONE;

			QTextEdit* edActionHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edActionHints"));
			m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_ACTIONS,
				odsActions,
				edActionHints->toPlainText()));

			qDebug() << "Include Actions with:";
			qDebug() << QString("    Documentation system: %1").arg(odsActions);
			qDebug() << QString("    Documentation hints:  %2").arg(edActionHints->toPlainText());
		}
		else
		{
			qDebug() << "Actions will not be included.";
		}

		// Add the subjective observations
		QTextEdit* edSubjectiveHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edSubjectiveHints"));
		m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_SUBJECTIVE_OBSERVATIONS,
			ObservationDocumentationSystem::ODS_NONE,
			edSubjectiveHints->toPlainText()));

		// Should a freetextfield be included?
		QCheckBox* cbFreeText = m_NewFileDlg->findChild<QCheckBox*>(QString("cbFreeText"));
		m_CurrentObservation->includeFreetext(cbFreeText->isChecked());

		// Close the dialog and reset the pointer
		m_NewFileDlg->close();
		m_NewFileDlg.reset();

		// Parse the observation into the document
		this->parseObservationToDocumentView();
 
		qDebug() << "New File Dialog Data is verified.";
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
