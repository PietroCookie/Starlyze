##########################################################################################
### Cette partie est a adapter en fonction de votre projet
##########################################################################################

CC = gcc
CFLAGS = -Wall -O3 -Werror
LDFLAGS = -lncurses

# DEBUG FLAGS (make debug : [#define _DEBUG_])
CFLAGS_DEBUG = -fsanitize=address
LDFLAGS_DEBUG = -fsanitize=address

# Le nom du projet (utile pour le nom de l'archive)
PROJECT_NAME = Mon_Super_Projet
# Le nom du fichier C ou se trouve le main
PRINCIPAL = main
# Le nom de l'executable a creer
EXE = main

DIR_SRC=./src/
DIR_INCLUDE=./include/
DIR_OBJ=./build/

# Fichiers a inclure dans l'archive (make archive)
ARCHIVE_FILES = *


##########################################################################################
### Cette partie (tout ce qui suit) ne devrait pas etre modifiee, en theorie
##########################################################################################


# Pour eviter de specifier le chemin des includes 
# [#include "exemple.h"], au lieu de [#include "../includes/exemple.h"]
CPATH = -I$(DIR_INCLUDE)


DEP=$(wildcard $(DIR_INCLUDE)*.h)
SRC=$(wildcard $(DIR_SRC)*.c)
OBJTEMP=$(subst $(DIR_SRC),$(DIR_OBJ), $(SRC))
OBJ=$(subst .c,.o, $(OBJTEMP))


##############################
### regle principale (la 1ere)
all : $(EXE)

			
##############################
### generation des modules objet
$(DIR_OBJ)$(PRINCIPAL).o : $(DIR_SRC)$(PRINCIPAL).c $(DEP)
	$(CC) $(CFLAGS) $(CPATH) $< -c -o $@
$(DIR_OBJ)%.o : $(DIR_SRC)%.c $(DIR_INCLUDE)%.h
	$(CC) $(CFLAGS) $(CPATH) $< -c -o $@
		
##############################
### regle principale : edition de lien
$(EXE) : $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) 
	
##############################
### regles complementaires usuelles
.PHONY : clean mrproper archive debug

clean : 
	@rm -f $(DIR_OBJ)*.o
	@rm -f *.o
mrproper : clean
	@rm -f *~ a.out $(EXE)


##############################
### creation archive

archive: mrproper
	@echo "Creating the archive : $(PROJECT_NAME)_$(shell date '+%y%m%d.tar.gz')..."
	@REP=`basename "$$PWD"`; cd .. && tar zcf $(PROJECT_NAME)_$(shell date '+%y%m%d.tar.gz') $(addprefix "$$REP"/,$(ARCHIVE_FILES))
	@echo "Done."

##############################
### Debug

CFLAGS_DEBUG += -D _DEBUG_

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: LDFLAGS += $(LDFLAGS_DEBUG)
debug: all