/*!
 *
 *  @file      Observation.cpp
 *  @brief     Implementation of the basic observation class
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "Observation.h"

namespace OGG {
	// Implementation of the constructor for ObservationDataField
	ObservationDataField::ObservationDataField(ObservationTopic _topic, ObservationDocumentationSystem _docSystem, QString _observationHints) :
		topic(_topic), documentationSystem(_docSystem), observationHints(_observationHints)
	{
	}

	/*!
	 * @brief Implementation of the default initialisation constructor
	*/
	Observation::Observation(QString _projectName,
		QDate _date,
		QString _location,
		QString _mainObjective,
		QString _excluded,
		QString _observationObjectDescription,
		bool _isParticipational,
		bool _isUndercover,
		bool _isSystematic,
		bool _isFieldObservation,
		bool _isInitialized) : m_projectName(_projectName),
		m_date(_date),
		m_locatiom(_location),
		m_MainObjective(_mainObjective),
		m_exclude(_excluded),
		m_observationObjectDescription(_observationObjectDescription),
		m_isParticipational(_isParticipational),
		m_isUndercover(_isUndercover),
		m_isSystematic(_isSystematic),
		m_isFieldObservation(_isFieldObservation),
		m_isInitialized(_isInitialized)
	{
		// Debug-Log-Output
		qDebug() << "Created new observation:";
		qDebug() << QString("    Project name:  %1").arg(this->m_projectName);
		qDebug() << QString("    Date:  %1").arg(this->m_date.toString(Qt::DateFormat::ISODate));
		qDebug() << QString("    Location:  %1").arg(this->m_locatiom);
		qDebug() << QString("    Main objective:  %1").arg(this->m_MainObjective);
		qDebug() << QString("    Exclude:  %1").arg(this->m_exclude);
		qDebug() << QString("    Observation object description:  %1").arg(this->m_observationObjectDescription);
		qDebug() << QString("    Is Participational:  %1").arg(this->m_isParticipational ? "TRUE" : "FALSE");
		qDebug() << QString("    Is Undercover:  %1").arg(this->m_isUndercover ? "TRUE" : "FALSE");
		qDebug() << QString("    Is systematically:  %1").arg(this->m_isSystematic ? "TRUE" : "FALSE");
		qDebug() << QString("    Is field observation:  %1").arg(this->m_isFieldObservation ? "TRUE" : "FALSE");
		qDebug() << QString("    Is initialized:  %1").arg(this->m_isInitialized ? "TRUE" : "FALSE");

		// Initialise the Data List
		this->m_lstObservationModules = std::make_unique<QList<ObservationDataField>>();
	}

	// Create an uninitialized Observation object
	Observation::Observation() :
		Observation::Observation(QString(), QDate(), QString(), QString(), QString(), QString(), false, false, true, true, false)
	{
		this->m_isInitialized = false;
		qDebug() << "Uninitialized Observation object has been created.";
	}


	bool Observation::Initialize(QString _projectName, QDate _date, QString _location, QString _mainObjective, QString _excluded, QString _observationObjectDescription, bool _isParticipational, bool _isUndercover, bool _isSystematic, bool _isFieldObservation)
	{
		m_projectName = _projectName;
		m_date = _date;
		m_locatiom = _location;
		m_MainObjective = _mainObjective;
		m_exclude = _excluded;
		m_observationObjectDescription = _observationObjectDescription;
		m_isParticipational = _isParticipational;
		m_isUndercover = _isUndercover;
		m_isSystematic = _isSystematic;
		m_isFieldObservation = _isFieldObservation;

		m_isInitialized = true;


		// Debug-Log-Output
		qDebug() << "Initialized observation:";
		qDebug() << QString("    Project name:  %1").arg(this->m_projectName);
		qDebug() << QString("    Date:  %1").arg(this->m_date.toString(Qt::DateFormat::ISODate));
		qDebug() << QString("    Location:  %1").arg(this->m_locatiom);
		qDebug() << QString("    Main objective:  %1").arg(this->m_MainObjective);
		qDebug() << QString("    Exclude:  %1").arg(this->m_exclude);
		qDebug() << QString("    Observation object description:  %1").arg(this->m_observationObjectDescription);
		qDebug() << QString("    Is Participational:  %1").arg(this->m_isParticipational ? "TRUE" : "FALSE");
		qDebug() << QString("    Is Undercover:  %1").arg(this->m_isUndercover ? "TRUE" : "FALSE");
		qDebug() << QString("    Is systematically:  %1").arg(this->m_isSystematic ? "TRUE" : "FALSE");
		qDebug() << QString("    Is field observation:  %1").arg(this->m_isFieldObservation ? "TRUE" : "FALSE");
		qDebug() << QString("    Is initialized:  %1").arg(this->m_isInitialized ? "TRUE" : "FALSE");


		return m_isInitialized;
	}
}