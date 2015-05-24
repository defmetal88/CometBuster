#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = clang

# define any compile-time flags
#CFLAGS = `sdl-config --cflags --libs` -g -std=c99 -lSDL_ttf -lSDL_mixer
CFLAGS = -m32 -g -std=c99

#WARNINGS=-Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition -Wextra 
#-Wall 
WARNINGS = 

# define any directories containing header files other than /usr/include
#
# INCLUDES = -I/home/newhall/include  -I../include
INCLUDES =

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm
#LIBS = -lSDL_ttf -lm
LIBS = -lm -framework SDL -framework SDL_ttf -framework Cocoa -framework SDL_mixer

# define the C source files
# TODO: update and complete the following line with your .c files names
SRCS = SDLMain.m main.c event.c graph.c init.c physic.c list.c keyboard.c MusicManagement.c

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = cometbuster

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:  $(MAIN)
	@echo  "Everything has been compiled, w00t!"

$(MAIN): $(OBJS) 
	$(CC) $(OBJS) $(CFLAGS) $(WARNINGS) $(INCLUDES) -o $(MAIN) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
