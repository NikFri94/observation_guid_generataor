/*!
 *
 *  @file      Observation.h
 *  @brief     Definition of the basic observation class
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      13.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#pragma once

#include <memory>

#include <QString>
#include <QDate>
#include <QList>

namespace OGG
{
	/*!
	 * @brief This enum defines the different possible types of Observations
	*/
	enum ObservationTopic
	{
		OT_GENERAL_DESCRIPTION,
		OT_COMMUNICATION,
		OT_INTERACTION,
		OT_ACTIVITIES,
		OT_ACTIONS,
		OT_SUBJECTIVE_OBSERVATIONS
	};

	/*!
	 * @brief Thsi enum defines the differend methods for the documentation structure which are available
	*/
	enum ObservationDocumentationSystem
	{
		ODS_NONE,
		ODS_TOP,
		ODS_CIRCLE
	};

	/*!
	 * @brief This struct represents one element which the observation can be focused on.
	*/
	struct ObservationDataField
	{
	public:
		// Public constructor
		ObservationDataField(ObservationTopic _topic,
							ObservationDocumentationSystem _docSystem = ObservationDocumentationSystem::ODS_NONE,
							QString _observationHints = QString());

	public:
		// Public members
		ObservationTopic				topic;
		ObservationDocumentationSystem	documentationSystem;
		QString							observationHints;
	};

	/*!
	 * @brief Class represents a basic observation
	*/
	class Observation
	{
	public:
		/*!
		 * @brief Default constructor for initialisation
		 * @param _projectName
		 * @param _date
		 * @param _location
		 * @param _mainObjective
		 * @param _excluded
		 * @param _observationObjectDescription
		 * @param _isParticipational
		 * @param _isUndercover
		 * @param _isSystematic
		 * @param _isFieldObservation
		*/
		Observation(QString _projectName,
			QDate _date,
			QString _location,
			QString _mainObjective,
			QString _excluded,
			QString _observationObjectDescription,
			bool _isParticipational = false,
			bool _isUndercover = false,
			bool _isSystematic = true,
			bool _isFieldObservation = true,
			bool _isInitialized=true);

		/*!
		 * @brief Constructor for creating a unitialized Observation
		*/
		Observation();

		/*!
		 * @brief Initialize this observation object
		 * @param _projectName 
		 * @param _date 
		 * @param _location 
		 * @param _mainObjective 
		 * @param _excluded 
		 * @param _observationObjectDescription 
		 * @param _isParticipational 
		 * @param _isUndercover 
		 * @param _isSystematic 
		 * @param _isFieldObservation 
		 * @return Returns true if the initialization was successfull
		*/
		bool Initialize(QString _projectName,
			QDate _date,
			QString _location,
			QString _mainObjective,
			QString _excluded,
			QString _observationObjectDescription,
			bool _isParticipational = false,
			bool _isUndercover = false,
			bool _isSystematic = true,
			bool _isFieldObservation = true);

		/*
		* Zugriffsmethoden
		*/
		QString getProjectName() const {
			return this->m_projectName;
		}
		QDate getDate() const {
			return this->m_date;
		}
		QString getLocation() const {
			return this->m_locatiom;
		}
		QString getMainObjective() const {
			return this->m_MainObjective;
		}
		QString getExcluded() const {
			return this->m_exclude;
		}
		QString getObservationObjectDescription() const {
			return this->m_observationObjectDescription;
		}
		bool isParticipational() const {
			return this->m_isParticipational;
		}
		bool isUndervocer() const {
			return this->m_isUndercover;
		}
		bool isSystematic() const {
			return this->m_isSystematic;
		}
		bool isFieldObservation() const {
			return this->m_isFieldObservation;
		}

		QList<ObservationDataField>* getObservationModulesLstPtr() {
			return this->m_lstObservationModules.get();
		}

		void includeFreetext(bool _freetext) {
			this->m_includeFreetext = _freetext;
		}
		bool hasFreetextIncluded() const {
			return this->m_includeFreetext;
		}

	private:
		QString m_projectName; //!< Name of the project in which context the observation takes place

		QDate	m_date; //!< Date of the observation
		QString	m_locatiom; //!< Location, in which the observation takes place

		QString	m_MainObjective;	 //!< Describes the main goal of the observation
		QString	m_exclude;	 //!< What should NOT be observed?
		QString	m_observationObjectDescription; //!< Brief description of the Object or Person which should be observed.

		bool	m_isParticipational;	 //!<  True if the observation is in participal mode
		bool	m_isUndercover;		 //!< False if the observation is covered, true for open observations
		bool	m_isSystematic;	 //!< True for systematic observations
		bool	m_isFieldObservation; //!< True if this is a field observation, false for laboritory

		bool m_isInitialized; //!< Indiciates if this object is initialized

		std::unique_ptr<QList<ObservationDataField>> m_lstObservationModules;

		bool m_includeFreetext;
	};
}