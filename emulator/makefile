FSOURCES = framework/main.cpp framework/gfx.cpp framework/debugger.cpp 
CSOURCES = common/sys_debug_scmp.cpp common/sys_processor.cpp 

CC = g++

all: mk14emu wmscmpmc

clean:
	rm -f wmscmpmc *.o

.PHONY: all clean

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

CFLAGS := $(SDL_CFLAGS) -O2 -Wall -DINCLUDE_DEBUGGING_SUPPORT -I. -I./framework -I./common -Wno-unused-variable
LDFLAGS := $(SDL_LDFLAGS) -lSDL2_image

wmscmpmc : $(FSOURCES) $(CSOURCES) williamson/hardware.cpp
	$(CC) $(FSOURCES) $(CSOURCES) -DWILLIAMSON -I./williamson williamson/hardware.cpp $(CFLAGS) $(LDFLAGS) -o $@

mk14emu : $(FSOURCES) $(CSOURCES) mk14/hardware.cpp
	$(CC) $(FSOURCES) $(CSOURCES) -DMK14 -I./mk14 mk14/hardware.cpp $(CFLAGS) $(LDFLAGS) -o $@


