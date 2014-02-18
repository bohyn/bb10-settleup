# Auto-generated by IDE. Any changes made by user will be lost!
BASEDIR =  $$quote($$_PRO_FILE_PWD_)

device {
    CONFIG(debug, debug|release) {
        SOURCES +=  $$quote($$BASEDIR/src/GroupRelatedModelBase.cpp) \
                 $$quote($$BASEDIR/src/GroupsModel.cpp) \
                 $$quote($$BASEDIR/src/MembersModel.cpp) \
                 $$quote($$BASEDIR/src/TransactionsModel.cpp) \
                 $$quote($$BASEDIR/src/applicationui.cpp) \
                 $$quote($$BASEDIR/src/blink/qmlblink.cpp) \
                 $$quote($$BASEDIR/src/main.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/GroupRelatedModelBase.h) \
                 $$quote($$BASEDIR/src/GroupsModel.h) \
                 $$quote($$BASEDIR/src/MembersModel.h) \
                 $$quote($$BASEDIR/src/TransactionsModel.h) \
                 $$quote($$BASEDIR/src/applicationui.hpp) \
                 $$quote($$BASEDIR/src/blink/qmlblink.h) \
                 $$quote($$BASEDIR/src/dbinfo.h)
    }

    CONFIG(release, debug|release) {
        SOURCES +=  $$quote($$BASEDIR/src/GroupRelatedModelBase.cpp) \
                 $$quote($$BASEDIR/src/GroupsModel.cpp) \
                 $$quote($$BASEDIR/src/MembersModel.cpp) \
                 $$quote($$BASEDIR/src/TransactionsModel.cpp) \
                 $$quote($$BASEDIR/src/applicationui.cpp) \
                 $$quote($$BASEDIR/src/blink/qmlblink.cpp) \
                 $$quote($$BASEDIR/src/main.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/GroupRelatedModelBase.h) \
                 $$quote($$BASEDIR/src/GroupsModel.h) \
                 $$quote($$BASEDIR/src/MembersModel.h) \
                 $$quote($$BASEDIR/src/TransactionsModel.h) \
                 $$quote($$BASEDIR/src/applicationui.hpp) \
                 $$quote($$BASEDIR/src/blink/qmlblink.h) \
                 $$quote($$BASEDIR/src/dbinfo.h)
    }
}

simulator {
    CONFIG(debug, debug|release) {
        SOURCES +=  $$quote($$BASEDIR/src/GroupRelatedModelBase.cpp) \
                 $$quote($$BASEDIR/src/GroupsModel.cpp) \
                 $$quote($$BASEDIR/src/MembersModel.cpp) \
                 $$quote($$BASEDIR/src/TransactionsModel.cpp) \
                 $$quote($$BASEDIR/src/applicationui.cpp) \
                 $$quote($$BASEDIR/src/blink/qmlblink.cpp) \
                 $$quote($$BASEDIR/src/main.cpp)

        HEADERS +=  $$quote($$BASEDIR/src/GroupRelatedModelBase.h) \
                 $$quote($$BASEDIR/src/GroupsModel.h) \
                 $$quote($$BASEDIR/src/MembersModel.h) \
                 $$quote($$BASEDIR/src/TransactionsModel.h) \
                 $$quote($$BASEDIR/src/applicationui.hpp) \
                 $$quote($$BASEDIR/src/blink/qmlblink.h) \
                 $$quote($$BASEDIR/src/dbinfo.h)
    }
}

INCLUDEPATH +=  $$quote($$BASEDIR/src/blink) \
         $$quote($$BASEDIR/src)

CONFIG += precompile_header

PRECOMPILED_HEADER =  $$quote($$BASEDIR/precompiled.h)

lupdate_inclusion {
    SOURCES +=  $$quote($$BASEDIR/../src/*.c) \
             $$quote($$BASEDIR/../src/*.c++) \
             $$quote($$BASEDIR/../src/*.cc) \
             $$quote($$BASEDIR/../src/*.cpp) \
             $$quote($$BASEDIR/../src/*.cxx) \
             $$quote($$BASEDIR/../src/blink/*.c) \
             $$quote($$BASEDIR/../src/blink/*.c++) \
             $$quote($$BASEDIR/../src/blink/*.cc) \
             $$quote($$BASEDIR/../src/blink/*.cpp) \
             $$quote($$BASEDIR/../src/blink/*.cxx) \
             $$quote($$BASEDIR/../assets/*.qml) \
             $$quote($$BASEDIR/../assets/*.js) \
             $$quote($$BASEDIR/../assets/*.qs) \
             $$quote($$BASEDIR/../assets/images/*.qml) \
             $$quote($$BASEDIR/../assets/images/*.js) \
             $$quote($$BASEDIR/../assets/images/*.qs)

    HEADERS +=  $$quote($$BASEDIR/../src/*.h) \
             $$quote($$BASEDIR/../src/*.h++) \
             $$quote($$BASEDIR/../src/*.hh) \
             $$quote($$BASEDIR/../src/*.hpp) \
             $$quote($$BASEDIR/../src/*.hxx)
}

TRANSLATIONS =  $$quote($${TARGET}.ts)