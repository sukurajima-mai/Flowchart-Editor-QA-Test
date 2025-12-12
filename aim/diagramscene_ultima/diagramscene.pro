QT += widgets
QT += svg

requires(qtConfig(fontcombobox))

HEADERS	    =   mainwindow.h \
		deletecommand.h \
		diagramitem.h \
		diagramitemgroup.h \
		diagrampath.h \
		diagramscene.h \
		arrow.h \
		diagramtextitem.h \
		findreplacedialog.h \
		snapshotcommand.h
SOURCES	    =   mainwindow.cpp \
		deletecommand.cpp \
		diagramitem.cpp \
		diagramitemgroup.cpp \
		diagrampath.cpp \
		findreplacedialog.cpp \
		main.cpp \
		arrow.cpp \
		diagramtextitem.cpp \
		diagramscene.cpp \
		snapshotcommand.cpp
RESOURCES   =	diagramscene.qrc \
    newpic.qrc


# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target

FORMS +=
