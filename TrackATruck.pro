QT += quick
QT += sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        dataprovider.cpp \
        lists/clientslist.cpp \
        lists/driverslist.cpp \
        lists/orderslist.cpp \
        lists/refuelingslist.cpp \
        lists/truckslist.cpp \
        main.cpp \
        timecontrol.cpp

RESOURCES += qml.qrc

DEFAULT_PGVERSION = 16
PGVERSION = $$getenv(PGVERSION)
isEmpty(PGVERSION) {
    message("PGVERSION not set, using default ($$DEFAULT_PGVERSION)")
    PGVERSION = $$DEFAULT_PGVERSION
}
message("using PostgreSQL $$PGVERSION")

win32:INCLUDEPATH += "C:/Program Files/PostgreSQL/" + $${PGVERSION} + "/include"
win32:LIBS += "C:/Program Files/PostgreSQL/" + $${PGVERSION} + "/lib/libpq.lib"

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dataprovider.h \
    lists/clientslist.h \
    lists/driverslist.h \
    lists/orderslist.h \
    lists/refuelingslist.h \
    lists/truckslist.h \
    timecontrol.h \
    types.h
