QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ATest.cpp \
    Error.cpp \
    Folder.cpp \
    Interpreter.cpp \
    Parser.cpp \
    Project.cpp \
    Reader.cpp \
    StructClass.cpp \
    main.cpp \
    testpr.cpp

HEADERS += \
    ATest.hpp \
    Error.hpp \
    Folder.hpp \
    Interpreter.hpp \
    Parser.hpp \
    Project.hpp \
    Reader.hpp \
    StructClass.hpp \
    testpr.hpp

FORMS += \
    testpr.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
