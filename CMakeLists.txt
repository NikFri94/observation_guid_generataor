# (C) Niklas Frings, 2024
# University of Wuppertal
# Makefile für die Projektmappe
# QT erfordert mindestens CMak 3.16
cmake_minimum_required(VERSION 3.16)

project(ObserveGG VERSION 1.0.0 LANGUAGES CXX)

# Mindestens C++17 erforderlich (QT)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Konfiguration für ET2
option(OGG_BUILD_TESTS "Compile unit tests" ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Ergänze den cmake-Ordner als Include-dir
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# DOXYGEN
include(UseDoxygenDoc)

# Setzen der QT6-Distro
set(CMAKE_PREFIX_PATH "E:\\Qt\\6.5.3\\msvc2019_64")

# QT6 suchen
find_package(Qt6 
	REQUIRED COMPONENTS 
	Core
	Core5Compat
	Widgets
	Test)

# Erzeuge Einstellungen für qt-projekt
qt_standard_project_setup()

# Festlegen der Output-Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 
	${PROJECT_SOURCE_DIR}/bin/lib/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM}_${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 
	${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM}_${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
	${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM}_${CMAKE_SYSTEM_PROCESSOR})


# Konfigurationen
# Dies für DIST-Version im Releasebuild auskommentieren.
#add_compile_definitions(ET_DIST=1)

# Subdirectories hinzufügen und verwalten
add_subdirectory(app)

# DOXYGEN Dokumentation 
add_doxygen_doc(
	BUILD_DIR
		${CMAKE_SOURCE_DIR}/docs
	DOXY_FILE
		${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
	TARGET_NAME
		docs
	COMMENT
		"HTML documentation"
)

# Wenn Option aktiv, dann auch Unit.-Tests erzeugen
if(ET2_BUILD_TESTS)
	enable_testing(true)
	add_subdirectory(app/test)
endif()