#-------------------------------------------------
#
# Project created by QtCreator 2019-02-11T15:46:26
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtPythonTest
TEMPLATE = app
CONFIG += no_keywords
INCLUDEPATH += -I /usr/local/anaconda3/include/python3.6m
LIBS += -L/usr/local/anaconda3/lib \
        -lpython3.6m -lpthread -ldl  -lutil -lrt -lm  -Xlinker -export-dynamic
QMAKE_CXXFLAGS +=   -Wsign-compare \
                    -march=nocona \
                    -ftree-vectorize \
                    -fPIC \
                    -O3 \
                    -pipe \
                    -DNDEBUG \
                    -fwrapv \
                    -O3 -Wall

SOURCES += main.cpp\
    pyrun.cpp

HEADERS  += pyrun.h

FORMS    +=

OTHER_FILES += runtest.py \
               /home/yzy/myStudy/PythonTest/VideoSuperResolution/Train/run.py
