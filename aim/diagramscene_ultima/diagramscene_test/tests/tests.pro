QT += testlib
QT += widgets testlib
QT += svg
QT -= gui

CONFIG += console
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ..
INCLUDEPATH += ../..

requires(qtConfig(fontcombobox))

SOURCES +=  \
    ../../arrow.cpp \
    ../../deletecommand.cpp \
    ../../diagramitem.cpp \
    ../../diagramitemgroup.cpp \
    ../../diagrampath.cpp \
    ../../diagramscene.cpp \
    ../../diagramtextitem.cpp \
    ../../findreplacedialog.cpp \
    ../../mainwindow.cpp \
    ../../snapshotcommand.cpp \
    tst_arrow.cpp \
    tst_deletecommand.cpp \
    tst_diagramitem.cpp \
    tst_diagramitemgroup.cpp \
    tst_diagrampath.cpp \
    tst_diagramscene.cpp \
    tst_diagramtextitem.cpp \
    tst_snapshotcommand.cpp

DISTFILES +=

HEADERS += \
    ../../arrow.h \
    ../../deletecommand.h \
    ../../diagramitem.h \
    ../../diagramitemgroup.h \
    ../../diagrampath.h \
    ../../diagramscene.h \
    ../../diagramtextitem.h \
    ../../findreplacedialog.h \
    ../../mainwindow.h \
    ../../snapshotcommand.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target
