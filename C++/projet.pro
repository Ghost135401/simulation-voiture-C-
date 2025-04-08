INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtCore
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtGui
INCLUDEPATH += /usr/include/x86_64-linux-gnu/qt5/QtWidgets

QT += core gui widgets

CONFIG += c++11

TARGET = QtApp
TEMPLATE = app

SOURCES += main.cpp \
           Voiture.cpp \
           MainWindow.cpp \
           VoitureDAO.cpp \
           Historique.cpp \
           HistoriqueDAO.cpp

HEADERS += Voiture.h \
           Database.h \
           MainWindow.h \
           VoitureDAO.h \
           Historique.h \
           HistoriqueDAO.h

LIBS += -lmysqlcppconn
