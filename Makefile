#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#
.DEFAULT_GOAL := all

# define the C compiler to use
CC = clang

#define RM command for make clean
RM = rm

# define any compile-time flags
CFLAGS = -m32 -g -std=c99
CFLAGS += -framework SDL
CFLAGS += -framework SDL_ttf
CFLAGS += -framework SDL_mixer
CFLAGS += -framework Cocoa

WARNINGS = -Wall -w

# define any directories containing header files other than /usr/include
#
# INCLUDES = -I/home/newhall/include  -I../include
INCLUDES = -I./Headers

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm 

# define the C source files
#SRCS = SDLMain.m main.c event.c graph.c init.c physic.c list.c keyboard.c MusicManagement.c

SRCS = $(wildcard Sources/*.c)


# define the C object files 
OBJS = Build/SDLMain.o
OBJS += $(patsubst Sources/%.c,Build/%.o,$(SRCS))

$(OBJS): | Build

Build: 
	mkdir ${@}
  

# define the executable file 
MAIN = cometbuster

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:  $(MAIN)
	@echo  "Everything has been compiled"

$(MAIN): $(OBJS) 
	$(CC) $(OBJS) $(CFLAGS) $(WARNINGS) $(INCLUDES) -o $(MAIN) $(LFLAGS) $(LIBS)

Build/SDLMain.o: SDL_ObjectiveC/SDLMain.m
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c SDL_ObjectiveC/SDLMain.m  -o Build/SDLMain.o -w

Build/%.o: Sources/%.c
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) -rf Build $(wildcard Sources/*~) $(wildcard Headers/*~)  $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
