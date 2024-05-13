# (C) Niklas Frings, 2023
# University of Wuppertal
# Makefile für Subprojekt Hauptanwendung

# Set paths to resource files
# Example:
#set(CMAKE_AUTOUIC_SEARCH_PATHS "res/MainWindow")

qt_add_executable(OGG_App
	src/main.cpp

    src/ObservationGuideGenerator.cpp
    src/GUI/MainWindow.cpp
    src/GUI/NewFileDialog/NewFileDialog.cpp
    src/ProjectSystem/Observation.cpp
    src/logging/loggingMessageHandler.cpp
)

# Linker
target_link_libraries(OGG_App
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

#add_dependencies(OGG_App)

if(QGG_DIST)
    # Setzen der Anwendungseigenschaften so, dass kein Konsolenfesnter angezeigt wird
    set_target_properties(ET2_App
        PROPERTIES
            WIN32_EXECUTABLE ON
            MACOSX_BUNDLE ON
    )
endif()

# Notwendige DLLs für Windows kopieren
if(WIN32)
    # Run winddeployqt if it can be found
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
    add_custom_command(TARGET OGG_App POST_BUILD COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:OGG_App>)
endif()