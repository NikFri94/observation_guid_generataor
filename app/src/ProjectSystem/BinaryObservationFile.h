/*!
 *
 *  @file      BinaryObservationFile.h
 *  @brief     In this file neccessary structures for handling the binary observation file system are defined
 *  @details   ~
 *  @author    Niklas Frings
 *  @date      22.05.2024
 *  @copyright © Niklas Frings, 2024. All right reserved.
 *
 */
#pragma once

#include <qtypes.h>
#include <QDataStream>
#include <QFile>

#include "Observation.h"

#define BOF_FILE_POSTFIX ".bof"
#define BOF_FILE_VERSION 0x00000001
#define BOF_FILE_MAGIC 0xD57C2C17

namespace OGG
{
	/*!
	 * @brief This enumeration defines all possible entry types which can be saved in a binary observation file (*.bof)
	*/
	enum BOFFileEntryType {
		FET_META,
		FET_FILE_TABLE,
		FET_PROJECT_NAME,
		FET_OBSERVATION_DATE,
		FET_OBSERVATION_LOCATION,
		FET_OBSERVATION_MAIN_OBJECTIVE,
		FET_OBSERVATION_EXCLUDE,
		FET_OBSERVATION_OBJECT_DESCRIPTION,
		FET_OBSERVATION_FLAGS,
		FET_OBSERVATION_MODULE_INFO
	};

	/*!
	 * @brief This struct defines one entry in the bof file table
	*/
	struct BOFTableEntry {
		quint32 iOffset;
		quint32 iEntrySize;
		BOFFileEntryType iEntryType;
	};

	/*!
	 * @brief This structure defines the metadata held in a bof file
	*/
	struct BOFFileMetaData
	{
		quint8 iFileTableEntryCount;
		quint16 iFileVersion;
		quint16 iMagic;

		BOFFileMetaData(quint8 _fileTableEntryCount,
			quint16 _fileVersion = BOF_FILE_VERSION,
			quint16 _fileMagic = BOF_FILE_MAGIC) : 
				iFileTableEntryCount(_fileTableEntryCount),
				iFileVersion(_fileVersion),
				iMagic(_fileMagic)
		{
		}
	};

	/*!
	 * @brief This class provides basic fnctions for dealing with binary observation files
	*/
	class BinaryObservationFileHandler
	{
	public:
		static void SaveToFile(Observation* _observation, QString _filename);
		static void LoadFromFile(Observation* _observation, QString _filename);
	};
}