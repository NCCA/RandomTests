TARGET=Noise
SOURCES+=main.cpp
HEADERS+=Noise.h
CONFIG+=c++11
INCLUDEPATH+=/usr/local/include
LIBS+= -L/usr/local/lib -lOpenImageIO
CONFIG -=app_bundle
QT-= core gui
