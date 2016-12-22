# Much of this makefile is nicked from RapidFit and slimmed down considerably
# Compiler and shell
CC         = g++
SHELL      = /bin/bash
RM         = rm -f

ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS   = $(shell root-config --libs)
ROOTLIBDIR = $(shell root-config --libdir)
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
LIBFLAGS   = -Wl,--as-needed $(ROOTLIBS) $(EXTRA_ROOTLIBS) -Wl,-rpath,$(LIBDIR):$(ROOTLIBDIR)

# Make the libraries
all : $(LIBS)
# Make object files
objects : $(OBJS)
# Build libraries
$(LIBDIR)/lib%.$(LIBEXT) : $(OBJDIR)/%.$(OBJEXT)
	$(CC) -shared $< -o $@ $(LIBFLAGS)
# Build objects
$(OBJDIR)/%.$(OBJEXT) : $(SRCDIR)/%.$(SRCEXT) $(HDRS)
	$(CC) $(CXXFLAGS) -c $< -o $@
# Remove all the output
clean :
	$(RM) $(OUTPUT)
.PHONY : all objects clean
