cmake_minimum_required(VERSION 3.16)

project(laba5 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем модуль Widgets вместо Quick
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Список всех твоих файлов (заголовочные и исходники)
qt_add_executable(applaba5
    main.cpp
    americanperson.h americanperson.cpp
    russianperson.h russianperson.cpp
    person.h
    date.h
    mainwindow.h mainwindow.cpp
    passform.h passform.cpp
)

# Связываем проект с библиотекой виджетов
target_link_libraries(applaba5 PRIVATE Qt6::Widgets)

# Настройки для Windows и macOS (иконки, бандлы)
set_target_properties(applaba5 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS applaba5
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)