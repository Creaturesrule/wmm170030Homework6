#
# Filename:		Makefile
# Date:			04/28/2020
# Author:		William Minchew
# Email:		wmm170030@utdallas.edu
# Version:		1.0
# Copyright:		2020, All Rights Reserved
# Course     CS 3377.501 Spring 20202
#
# Description:
#    Makefile for program6
#	

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -g -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

# Executable Name
EXECFILE = program6

# Auto include all .cc files
SOURCES := $(wildcard *.cc)
OBJS = $(SOURCES:.cc=.o)

# Rely on implicit rules for compilation

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

