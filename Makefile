#============================================
#    Makefile: makefile for mysl
#	Copyright 2012, 2017 Mehta Sanket Satish
#		(mehtasankets@gmail.com)
#	Last Modified: 2012/05/30
#============================================

DESTDIR=
CC=cc
MKDIR=mkdir
CP=cp
CFLAGS=-O

mysl: mysl.c mysl.h
	$(CC) $(CFLAGS) -o mysl mysl.c -lcurses -ltermcap

install:
	$(MKDIR) -p $(DESTDIR)/bin
	$(CP) mysl $(DESTDIR)/bin
