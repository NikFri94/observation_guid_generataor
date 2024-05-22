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
			if (cbActivities->currentText() == QString("Führungskreislauf / Kreisprozess"))
				odsActivities = ObservationDocumentationSystem::ODS_CIRCLE;
			else
				odsActivities = ObservationDocumentationSystem::ODS_NONE;

			QTextEdit* edActivitiesHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edActivitiesHints"));
			m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_ACTIVITIES,
				odsActivities,
				edActivitiesHints->toPlainText()));
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
			if (cbActions->currentText() == QString("Führungskreislauf / Kreisprozess"))
				odsActions = ObservationDocumentationSystem::ODS_CIRCLE;
			else if (cbActions->currentText() == QString("TOP"))
				odsActions = ObservationDocumentationSystem::ODS_TOP;
			else
				odsActions = ObservationDocumentationSystem::ODS_NONE;

			QTextEdit* edActionHints = m_NewFileDlg->findChild<QTextEdit*>(QString("edActionHints"));
			m_CurrentObservation->getObservationModulesLstPtr()->append(ObservationDataField(ObservationTopic::OT_ACTIONS,
				odsActions,
				edActionHints->toPlainText()));
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
