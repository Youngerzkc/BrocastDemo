QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE	= app
TARGET		= udpclient

HEADERS		= udpclient.h
SOURCES		= udpclient.cpp \
		  main.cpp
QT += network

