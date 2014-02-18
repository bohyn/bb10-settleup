QT += declarative xml
QT += sql

#CONFIG += c++11
enable_cxx11 {
qnx {
	QMAKE_CXXFLAGS += -Wc,-std=c++0x
}
else {
	QMAKE_CXXFLAGS += -std=c++0x
}
}

TARGET = settleup

TEMPLATE = app

LIBS += -lbbdata -lbb -lbbcascades
LIBS += -lbbsystem -lbbcascadesdatamanager

include(src/src.pri)

OTHER_FILES += \
	bar-descriptor.xml \

