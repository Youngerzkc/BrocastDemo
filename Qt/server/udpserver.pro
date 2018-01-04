QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE	= app
TARGET		= udpserver


HEADERS		= udpserver.h
SOURCES		= udpserver.cpp \
		  main.cpp
QT += network
