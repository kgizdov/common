# Much of this makefile is nicked from RapidFit and slimmed down considerably
# Compiler and shell
CC         = g++
SHELL      = /bin/bash
RM         = rm -f

ifndef ROOTSYS
	ROOTCFLAGS = $(shell root-config --cflags)
	ROOTLIBS   = $(shell root-config --libs)
else
	ROOTCFLAGS = $(shell $(ROOTSYS)/bin/root-config --cflags | awk -F "-I" '{print $$1" -isystem"$$2}' )
	ROOTLIBS   = $(shell $(ROOTSYS)/bin/root-config --libs)
endif
EXTRA_ROOTLIBS = -lRooFit -lRooStats -lRooFitCore

# Extensions
SRCEXT     = cpp
HDREXT     = h
OBJEXT     = o
LIBEXT     = so

# Directories
SRCDIR     = src
HDRDIR     = include
OBJDIR     = build
LIBDIR     = lib

# Get files and make list of objects and libraries
SRCS      := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
HDRS      := $(shell find $(HDRDIR) -name '*.$(HDREXT)')
OBJS      := $(patsubst $(SRCDIR)/%.$(SRCEXT),$(OBJDIR)/%.$(OBJEXT),$(SRCS))
LIBS      := $(patsubst $(SRCDIR)/%.$(SRCEXT),$(LIBDIR)/lib%.$(LIBEXT),$(SRCS))

# Where the output is
OUTPUT     = $(OBJDIR)/*.$(OBJEXT) $(LIBDIR)/*.$(LIBEXT)

# Compiler flags
CXXFLAGS   = -Wall -Werror -fPIC -std=c++11 -I$(HDRDIR) $(ROOTCFLAGS)
LIBFLAGS   = $(ROOTLIBS) $(EXTRA_ROOTLIBS)

# Make the libraries
all : $(LIBS)
# Make object files
objects : $(OBJS)
# Build libraries
$(LIBDIR)/lib%.$(LIBEXT) : $(OBJDIR)/%.$(OBJEXT)
	$(CC) -shared $< -o $@ -Wl,--as-needed $(LIBFLAGS)
# Build objects
$(OBJDIR)/%.$(OBJEXT) : $(SRCDIR)/%.$(SRCEXT) $(HDRS)
	$(CC) $(CXXFLAGS) -c $< -o $@
# Remove all the output
clean :
	$(RM) $(OUTPUT)
.PHONY : all objects clean
