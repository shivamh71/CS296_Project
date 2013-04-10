.SUFFIXES: .cpp .hpp

# Programs
SHELL = bash
CC = g++
LD	= ld
RM 	= rm -rf
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
MV = mv
MKDIR = mkdir -p
MKSTATIC = ar -cr
PDFLATEX = pdflatex
CHDIR = cd
UNTAR = tar -xf
PROF = gprof
PLOT = gnuplot
DOXYGEN = doxygen
PYTHON = python3

######################################
# Project File Names
TARGET = cs296_base_16
LIBTARGET = cs296_exelib_16
REPORT_FILE = g16_prof_report

# Project Paths
PROJECT_ROOT=$(HOME)/Desktop/Project/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
DATADIR = $(PROJECT_ROOT)/data
SCPTDIR = $(PROJECT_ROOT)/scripts
PLOTDIR = $(PROJECT_ROOT)/plots

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
BOX2D_LIB=$(BOX2D_ROOT)/lib/libBox2D.a
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL
ST_LBRY = libCS296.a
SH_LBRY = libCS296.so

# Compiler and Linker flags
CPPFLAGS =-pg -Wall -fPIC -O3
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-pg -L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib
COMPILE_TYPE = Release
PROFILE_TYPE = release

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"

STATIC_LIB = true
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)



.PHONY: all setup exe library exelib doc plot01 plot02 report debug_prof release_prof clean

all: exe exelib

setup: $(BOX2D_LIB)
	@$(ECHO) "Setting up compilation..."
	@mkdir -p $(SRCDIR) $(OBJDIR) $(BINDIR) $(DOCDIR) $(DATADIR) $(SCPTDIR) $(PLOTDIR)

$(BOX2D_LIB):
	@$(CHDIR) $(BOX2D_ROOT)/src ;\
	$(UNTAR) Box2D.tgz ;\
	$(MKDIR) Box2D/build296 ;\
	$(CHDIR) Box2D/build296 ;\
	$(ECHO) "Compile type is " $(COMPILE_TYPE) ;\
	cmake -DCMAKE_BUILD_TYPE=$(COMPILE_TYPE) ../ ;\
	make ;\
	make install
	
exe: setup $(OBJS)
	@$(ECHO) "Creating executable..."
	@$(CC) -o $(BINDIR)/$(TARGET) $(LDFLAGS) $(OBJS) $(LIBS)

$(BINDIR)/$(TARGET): exe

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(ECHO) "Creating object file with " $(CPPFLAGS)
	@$(CC) $(CPPFLAGS) -c $< -o $@

library: $(OBJS)
ifeq ($(STATIC_LIB),true)
	@$(ECHO) "Creating static library..."
	@$(MKSTATIC) $(LIBDIR)/$(ST_LBRY) $(filter-out $(OBJDIR)/main.o, $(OBJS))
	$(eval LIBRARY=$(ST_LBRY))
else
	@$(ECHO) "Creating shared library..."
	@$(CC) -shared -o $(LIBDIR)/$(SH_LBRY) $(filter-out $(OBJDIR)/main.o, $(OBJS))
	$(eval LIBRARY=$(SH_LBRY))
endif

exelib: setup library
	@$(ECHO) "Creating executable using the library" $(LIBRARY) "..."
	@$(CC) -o $(BINDIR)/$(LIBTARGET) $(LDFLAGS) -L$(LIBDIR) $(OBJDIR)/main.o $(LIBDIR)/$(LIBRARY) $(LIBS)

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) $(DOCDIR)/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile
	@$(ECHO) "Done"

#plot:$(BINDIR)/$(TARGET)
#	@$(ECHO) "Generating csv files..."
#	@$(MKDIR) data plots
#	@$(SCPTDIR)/gen_data_csv.sh
#	@$(SCPTDIR)/temp_data.sh
#	@$(ECHO) "Making plots..."
#	@$(PLOT) $(SCPTDIR)/*.gpt

report:$(DOCDIR)/$(REPORT_FILE).tex
	@$(ECHO) "Compiling the profile documentation..."
	@$(MV) $(DOCDIR)/$(REPORT_FILE).tex $(PROJECT_ROOT)/$(REPORT_FILE).tex
	@$(PDFLATEX) $(REPORT_FILE)
	@$(MV) -i $(PROJECT_ROOT)/$(REPORT_FILE).pdf $(DOCDIR)/$(REPORT_FILE).pdf
	@$(MV) -i $(PROJECT_ROOT)/$(REPORT_FILE).tex $(DOCDIR)/$(REPORT_FILE).tex
	@$(RM) $(PROJECT_ROOT)/$(REPORT_FILE)*
	@$(PYTHON) $(SCPTDIR)/g16_gen_html.py

#profile:$(BINDIR)/$(TARGET)
#	@$(ECHO) "Profiling..."
#	@$(BINDIR)/$(TARGET) 10000
#	@$(PROF) $(BINDIR)/$(TARGET) gmon.out > $(DATADIR)/g16_$(PROFILE_TYPE)_prof.dat
#	@$(PROF) $(BINDIR)/$(TARGET) | $(SCPTDIR)/gprof2dot.py | dot -Tpng -o $(PLOTDIR)/g16_$(PROFILE_TYPE)_plot.png

clean:
	@$(ECHO) "Cleaning up..."
	@$(RM) ./gmon.out *~ */*~ $(OBJDIR) $(DATADIR) $(PLOTDIR) bin doc/$(REPORT_FILE).pdf

distclean: clean
	@$(ECHO) "Cleaning up the distribution..."
	@$(CHDIR) $(EXTERNAL_ROOT) ;\
	$(RM) include lib src/Box2D
	@$(RM) $(DOCDIR)/html $(DOCDIR)/$(REPORT_FILE).html

dist: distclean
	@$(CHDIR) .. ;\
	tar -zcf cs296_g16_project.tar.gz $(PROJECT_ROOT)

install: setplace exe report doc clean
	@$(RM) $(DOCDIR)/Doxyfile $(DOCDIR)/$(REPORT_FILE).tex
	@cp doc/$(REPORT_FILE).html $(DOCDIR)

setplace:
	$(eval loc=$(shell read -p "Enter the location for installation: "; echo $$REPLY))
	@$(RM) $(loc)
	@$(MKDIR) $(loc)
	@$(MKDIR) $(loc)/doc
	@cp -r $(DOCDIR) $(loc)
	$(eval BINDIR=$(loc)/bin)
	$(eval DOCDIR=$(loc)/doc)

