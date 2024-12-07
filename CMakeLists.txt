cmake_minimum_required(VERSION 3.16)

project(WeatherBoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWeatherBoard
    main.cpp
)

qt_add_qml_module(appWeatherBoard
    URI WeatherBoard
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES apiweatherdatarequesthandler.h apiweatherdatarequesthandler.cpp
        SOURCES currentweatherdata.h currentweatherdata.cpp
        SOURCES apiweatherimagerequesthandler.h apiweatherimagerequesthandler.cpp
        RESOURCES .gitignore
        QML_FILES Parameter.qml
        QML_FILES CityInfo.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWeatherBoard PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWeatherBoard
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeatherBoard
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appWeatherBoard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
