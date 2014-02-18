SOURCES +=  $$PWD/GroupRelatedModelBase.cpp \
			$$PWD/GroupsModel.cpp \
			$$PWD/MembersModel.cpp \
			$$PWD/TransactionsModel.cpp \
			$$PWD/applicationui.cpp \
			$$PWD/blink/qmlblink.cpp \
			$$PWD/main.cpp \

HEADERS +=  $$PWD/GroupRelatedModelBase.h \
			$$PWD/GroupsModel.h \
			$$PWD/MembersModel.h \
			$$PWD/TransactionsModel.h \
			$$PWD/applicationui.hpp \
			$$PWD/blink/qmlblink.h \
			$$PWD/dbinfo.h \

include(subsetsum/subsetsum.pri)
