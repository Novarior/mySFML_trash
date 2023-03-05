########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = clang++
CXXFLAGS = -std=c++17 -ferror-limit=100 -fcolor-diagnostics -fansi-escape-codes main.cpp Core.cpp states/State.cpp states/MainMenu.cpp states/PauseMenu.cpp states/Process.cpp states/gfx.cpp states/NoiceView.cpp math/mymath.cpp math/ProcessGenerationNoice.cpp GUI/GUISYS.cpp GUI/tabMenu.cpp entitys/entity.cpp entitys/player.cpp entitys/properties/hitbox.cpp entitys/properties/movement.cpp Content/rotationCircle.cpp Content/Map/block.cpp Content/Map/TileMap.cpp Content/Map/genTree.cpp -Isource/include/ -o ${workspaceFolder}/main.app -Lsource/lib -lsfml-graphics -lsfml-window -lsfml-system -w 
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = myapp
EXT = .cpp
SRCDIR = src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(DEP) $(APPNAME)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(DEP)