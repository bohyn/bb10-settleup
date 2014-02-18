TARGET = settleup

TEMPLATE = app

LIBS += -lbbdata -lbb -lbbcascades
LIBS += -lbbsystem -lbbcascadesdatamanager

QT += declarative xml
QT += sql

include(src/src.pri)

OTHER_FILES += \
	bar-descriptor.xml \
    bar-descriptor.xml

