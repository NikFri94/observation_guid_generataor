/*!
 *
 *  @file      BinaryObservationFile.cpp
 *  @brief     Neccessary implementations for the binary file system
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      22.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#include "BinaryObservationFile.h"

namespace OGG
{
	void BinaryObservationFileHandler::SaveToFile(Observation* _observation, QString _filename)
	{
		// File Metadata
		BOFFileMetaData metadata = BOFFileMetaData(0);
	}
	void BinaryObservationFileHandler::LoadFromFile(Observation* _observation, QString _filename)
	{
	}
}
