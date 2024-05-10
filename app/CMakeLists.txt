# (C) Niklas Frings, 2023
# University of Wuppertal
# Makefile für Subprojekt Hauptanwendung

# Set paths to resource files
# Example:
#set(CMAKE_AUTOUIC_SEARCH_PATHS "res/MainWindow")

qt_add_executable(OGG_App
	src/main.cpp
)

# Linker
target_link_libraries(OGG_App
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

#add_dependencies(OGG_App)

# Setzen der Anwendungseigenschaften so, dass kein Konsolenfesnter angezeigt wird
#set_target_properties(ET2_App
#    PROPERTIES
        #WIN32_EXECUTABLE ON
        #MACOSX_BUNDLE ON
#)

# Notwendige DLLs kopieren
add_custom_command(TARGET OGG_App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Core> $<TARGET_FILE_DIR:OGG_App>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Widgets> $<TARGET_FILE_DIR:OGG_App>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Gui> $<TARGET_FILE_DIR:OGG_App>
)