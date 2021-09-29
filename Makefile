#
# Created by gmakemake (Ubuntu Jul 25 2014) on Tue Aug  3 14:14:11 2021
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak


CFLAGS = -ggdb -std=c99 -Wall -Wextra -pedantic 


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	commands.c offspring.c queueADT.c tree.c trimit.c
PS_FILES =	
S_FILES =	
H_FILES =	commands.h queueADT.h tree.h trimit.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	commands.o queueADT.o tree.o trimit.o 

#
# Main targets
#

all:	offspring 

offspring:	offspring.o $(OBJFILES)
	$(CC) $(CFLAGS) -o offspring offspring.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

commands.o:	queueADT.h tree.h trimit.h
offspring.o:	commands.h queueADT.h tree.h trimit.h
queueADT.o:	queueADT.h
tree.o:	tree.h trimit.h
trimit.o:	trimit.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) offspring.o core

realclean:        clean
	-/bin/rm -f offspring 
