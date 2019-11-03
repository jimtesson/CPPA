QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testmyapp.cpp \
            ../src/MyApp/Lib/iashape.cpp\
            ../src/MyApp/Lib/cppalgo.cpp

HEADERS +=  ../src/MyApp/Lib/iashape.h\
            ../src/MyApp/Lib/cppalgo.h

INCLUDEPATH = ../src/MyApp/Lib
