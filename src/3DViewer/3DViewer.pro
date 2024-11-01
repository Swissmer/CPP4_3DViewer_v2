QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include(QtGifImage/src/gifimage/qtgifimage.pri)

SOURCES += \
    main.cc \
    ./view/opengl.cc \
    ./view/view.cc \
    ./controller/controller.cc \
    ./model/model.cc \
    ./model/parser.cc \
    ./model/helpinfo.cc \
    ./model/normalization.cc \
    ./pattern/pattern_command.cc \
    ./pattern/pattern_facade.cc \
    ./pattern/pattern_strategy.cc

HEADERS += \
    ./view/opengl.h \
    ./view/view.h \
    ./controller/controller.h \
    ./model/model.h \
    ./model/parser.h \
    ./model/helpinfo.h \
    ./model/normalization.h \
    ./pattern/pattern_command.h \
    ./pattern/pattern_facade.h \
    ./pattern/pattern_strategy.h

FORMS += \
    ./view/view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
