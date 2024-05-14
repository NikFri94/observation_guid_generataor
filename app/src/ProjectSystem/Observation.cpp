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
		bool _isFieldObservation) : m_projectName(_projectName), 
									m_date(_date),
									m_locatiom(_location),
									m_MainObjective(_mainObjective),
									m_exclude(_excluded),
									m_observationObjectDescription(_observationObjectDescription),
									m_isParticipational(_isParticipational),
									m_isUndercover(_isUndercover),
									m_isSystematic(_isSystematic),
									m_isFieldObservation(_isFieldObservation)
	{
		// Debug-Log-Output
		qDebug() << "Created new observation:";
		qDebug() << QString("\t\tProject name:\t{1}").arg(this->m_projectName);
		qDebug() << QString("\t\tDate:\t{1}").arg(this->m_date.toString(Qt::DateFormat::ISODate));
		qDebug() << QString("\t\tLocation:\t{1}").arg(this->m_locatiom);
		qDebug() << QString("\t\tMain objective:\t{1}").arg(this->m_MainObjective);
		qDebug() << QString("\t\tExclude:\t{1}").arg(this->m_exclude);
		qDebug() << QString("\t\tObservation object description:\t{1}").arg(this->m_observationObjectDescription);
		qDebug() << QString("\t\tIs Participational:\t{1}").arg(this->m_isParticipational?"TRUE":"FALSE");
		qDebug() << QString("\t\tIs Undercover:\t{1}").arg(this->m_isUndercover ? "TRUE" : "FALSE");
		qDebug() << QString("\t\tIs systematically:\t{1}").arg(this->m_isSystematic ? "TRUE" : "FALSE");
		qDebug() << QString("\t\tIs field observation:\t{1}").arg(this->m_isFieldObservation ? "TRUE" : "FALSE");
	}
}