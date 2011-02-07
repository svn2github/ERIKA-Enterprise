# makemodel.mk - elaborate, compile and link a CAL network/model
#                Assumed to be used in sub-make from main Makefile

# delete the built-in suffixes to avoid surprises
.SUFFIXES:   

ifeq "$(strip $(MODEL))" ""
  $(error MODEL not set)
endif

EXE?=$(MODEL)
srcdir?=.

MODEL_PATH=$(srcdir):/home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/cal

.PHONY: all
all: $(EXE)

# Dependences of MODEL (re-generated if necessary)
include $(MODEL).depend

# Default definitions of tools and directories
include /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/actors-make/definitions.mk

#
# Set CFLAGS, CPPFLAGS, LDFLAGS and LDLIBS
#

# Include path goes into CPPFLAGS (C pre-processor)
override CPPFLAGS += -I$(ACTORS_INCLUDE)

ifdef DEBUG
override CPPFLAGS += -DDEBUG
endif

override LDLIBS  += -lactors-rts -lpthread
override LDFLAGS += -L$(ACTORS_LIB)

ifdef PROFILE
override CFLAGS += -pg -fno-omit-frame-pointer
override LDFLAGS += -pg
endif


#
# Staging directory for ARM
#
ifdef ARM
ARMDIR=$(HOME)/work/actor/arm/usr/local
override  LDLIBS += -L$(ARMDIR)/lib -lxml2 -lz
else
override  LDLIBS += `xml2-config --libs`
endif

#
# Additional C file for "null" display (no display)
#
ifdef NULL_DISPLAY

override SYS_OBJECTS += display-null.o

display-null.o: /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/c/display-null.c
	$(CC) -c -O3 -Wall $(CPPFLAGS) $(CFLAGS)  -o $@ $<

endif

#
# Additional C file for frame-buffer display
#
ifdef FB_DISPLAY
override SYS_OBJECTS += display-fb.o

display-fb.o: /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/c/display-fb.c
	$(CC) -c -O3 -Wall $(CPPFLAGS) $(CFLAGS)  -o $@ $<

endif

#
# Additional C files, compiler flags and libraries when using GTK display
#
ifdef GTK_DISPLAY
override SYS_OBJECTS += display-gtk.o
override LDLIBS += `pkg-config --libs gtk+-2.0`
GTK_CFLAGS = $(CFLAGS) `pkg-config --cflags gtk+-2.0`

display-gtk.o: /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/c/display-gtk.c
	$(CC) -c -O3 -Wall $(CPPFLAGS) $(GTK_CFLAGS)  -o $@ $<

endif

#
# Additional C files, compiler flags and libraries when using SDL display
#
ifdef SDL_DISPLAY

override SYS_OBJECTS += display-sdl.o

ifdef ARM

override LDLIBS  += -L$(ARMDIR)/lib -lSDL -lts
SDL_CFLAGS = -I$(ARMDIR)/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -DSDL

else

override LDLIBS  += `sdl-config --libs`
SDL_CFLAGS += `sdl-config --cflags`

endif

display-sdl.o: /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/c/display-sdl.c
	$(CC) -c -O3 -Wall $(CPPFLAGS) $(SDL_CFLAGS) -o $@ $<

endif

#
# Additional C files, compiler flags and libraries when using dBus system actor 
#
ifdef RM_CLIENT
override SYS_OBJECTS += art_DBus_test.o genericdbushandler.o
ifdef ARM
override CXX_INCLUDES += -I$(ARMDIR)/include/dbus-1.0 -I$(ARMDIR)/lib/dbus-1.0/include
override LDLIBS += -L$(ARMDIR)/lib -ldbus-1 $(ARMDIR)/lib/libgcc_s.so.1 $(ARMDIR)/lib/libstdc++.so.6
else
override CXX_INCLUDES += -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include
override LDLIBS += -ldbus-1 /lib/libgcc_s.so.1 /usr/lib/libstdc++.so.6
endif

art_DBus_test.o: /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/c/art_DBus_test.cpp
	$(CXX) -c -O3 -Wall $(CPPFLAGS) $(CXX_INCLUDES) -o $@ $<

genericdbushandler.o: /home/antonio/Evidence/svn/opendf/trunk/contrib/actorsproject/share/sysactors/c/genericdbushandler.cpp
	$(CXX) -c -O3 -Wall $(CPPFLAGS) $(CXX_INCLUDES)  -o $@ $<
endif

override LDLIBS += -lpthread -lc

ifdef MERGE
override MODEL_DEPEND = $(MODEL)_new.xdf 
else
override MODEL_DEPEND = $(MODEL).xdf
endif

#
# We get the actor instances from the CALML-files 
# (we have to do elaboration first, to get *.calml).
#

ACTOR_C_FILES=$(XLIM_FILES:.xlim=.c)
PAR_FILES=$(XLIM_FILES:.xlim=.par)
EXTRA_OBJECTS=$(notdir $(C_FILES:.c=.o))
OBJECTS=$(ACTOR_C_FILES:.c=.o) $(EXTRA_OBJECTS) $(SYS_OBJECTS) $(MODEL).o

$(EXE): $(OBJECTS)
	$(CC) -g $^ $(LDFLAGS) $(LDLIBS) -o $@

#
# Rule for additional C files
#

$(EXTRA_OBJECTS) : %.o : $(srcdir)/%.c
	$(CC) -c -O3 -Wall $(CPPFLAGS) $(CFLAGS) -o $@ $<

#
# Implicit rules .xlim -> .c -> .o
#

%.o : %.c
	$(CC) -c -O3 -Wall $(CPPFLAGS) $(CFLAGS) -o $@ $<


# Preserve generated C files (make otherwise considers them temporary files)
.SECONDARY: $(ACTOR_C_FILES)

%.c : %.xlim
	$(XLIM2C) $< $@

#
# Generate network configuration from .xdf
#
$(MODEL).c: $(MODEL_DEPEND)
	$(SAXON8) -o $@ $< $(GENERATECONFIG_XSL)

#
# If enabled, run model compiler
#
$(MODEL)_new.xdf: $(MODEL).xdf $(XLIM_FILES)
	$(MODELCOMPILER) $(MODEL).xdf
	@cp $(MODEL)_new.xdf $(MODEL).xdf
	@touch $(MODEL).timestamp

#
# Generate .xlim from .cal and .par
# (dependence of .xlim on .cal and .par is given by $(MODEL).depend)
#
$(XLIM_FILES): %.xlim :
	$(SSAGENERATOR) -mp "$(srcdir)" `cat $(basename $(@F)).par` $(<F)
	mv $(basename $(<F)).xlim $@


#
# Generate parameter (.par) files from $(MODEL).xdf
# (dependence of .par files on $(MODEL).xdf via $(MODEL).timestamp)
#

$(PAR_FILES): $(MODEL).timestamp

$(MODEL).timestamp: $(MODEL).xdf
	$(XDF2PAR) $<
	@touch $@

#
# Generate dependences from .xdf
#
$(MODEL).depend: $(MODEL).xdf
	$(SAXON8) -o $@ $< $(XDF2DEPEND_XSL)


#
# Generate xdf from network (nl) files
# (dependence of $(MODEL).xdf on network (.nl) files is
#  given in $(MODEL).depend). 
#
$(MODEL).xdf: $(srcdir)/$(MODEL).nl $(SUB_NETWORKS)
	$(ELABORATOR) -mp $(MODEL_PATH) $(MODEL)

.PHONY: clean

# C files to clean (filter out C_FILES in case srcdir is current directory)
CLEAN_C_FILES=$(filter-out $(C_FILES),$(wildcard *.c))

clean:
	rm -f $(EXE) $(MODEL).xdf $(MODEL).depend $(MODEL).timestamp \
            *.par *.xlim $(CLEAN_C_FILES) *.o
