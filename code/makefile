##########################################################################################
### Cette partie est a adapter en fonction de votre projet
##########################################################################################

CC = gcc
CFLAGS = -Wall -O3 -Werror
LDFLAGS = -lncurses
CCLIBS = 

# DEBUG FLAGS (make debug : [#define _DEBUG_])
CFLAGS_DEBUG = -fsanitize=address
LDFLAGS_DEBUG = -fsanitize=address

# Le nom du projet (utile pour le nom de l'archive)
PROJECT_NAME = Starlyze
# Le nom de l'executable a creer
EXE = editor

# Liste des dossiers contenus dans SRC_DIR et INCLUDE_DIR
DIR = editor global ncurses

DIR_OBJ = obj
DIR_EXE = bin
SRC_DIR = src
INCLUDE_DIR = include

# Fichiers a inclure dans l'archive (make archive)
ARCHIVE_FILES = *



##########################################################################################
### Cette partie (tout ce qui suit) ne devrait pas etre modifiee, en theorie
##########################################################################################

.SUFFIXES: .c .o

EXEC_O = $(EXE:=.o)

# Pour eviter de specifier le chemin des includes 
$(foreach d, $(DIR), $(eval CPATH += -I$(INCLUDE_DIR)/$(d)/))

$(foreach d, $(DIR), $(eval SRC += $(wildcard $(SRC_DIR)/$(d)/*.c)))

OBJTEMP=$(subst $(SRC_DIR)/,, $(SRC))
OBJECTS = $(subst .c,.o, $(OBJTEMP))
OBJECTS_O = $(OBJECTS) $(EXEC_O)


##############################
### regle principale (la 1ere)
all : create_folder msg $(addprefix $(DIR_OBJ)/, $(OBJECTS_O))
	@echo "\n####### Create executable #######\n"
	@for exe in $(EXE); do \
		echo "create >>> $$exe"; \
		$(CC) -o $(addprefix $(DIR_EXE)/,$$exe) $(addprefix $(DIR_OBJ)/,$$exe.o) $(addprefix $(DIR_OBJ)/,$(OBJECTS)) $(LDFLAGS) $(CCLIBS) $(CPATH); \
	done
	@echo "\n####### Successfull compilation #######"

msg:
	@echo "####### Create objects #######\n"

create_folder:
	@for d in $(DIR); do \
		mkdir -p $(DIR_OBJ)/$$d; \
	done

delete_folder:
	@for d in $(DIR); do \
		rm -rf $(DIR_OBJ)/$$d; \
	done

##############################
### generation des modules objets
$(addprefix $(DIR_OBJ)/,%.o) : $(addprefix $(SRC_DIR)/,%.c)
	@echo "create >>> $@"
	@${CC} ${CFLAGS} -c $< -o $@ $(CPATH)
			
##############################
### generation des modules objet
# $(DIR_OBJ)$(PRINCIPAL).o : $(DIR_SRC)$(PRINCIPAL).c $(DEP)
# 	$(CC) $(CFLAGS) $(CPATH) $< -c -o $@
# $(DIR_OBJ)%.o : $(DIR_SRC)%.c $(DIR_INCLUDE)%.h
# 	$(CC) $(CFLAGS) $(CPATH) $< -c -o $@
		
##############################
### regle principale : edition de lien
# $(EXE) : $(OBJ)
# 	$(CC) $^ -o $@ $(LDFLAGS) 
	
##############################
### regles complementaires usuelles
.PHONY : clean mrproper archive debug

clean : delete_folder
	@rm -f $(DIR_OBJ)/*.o
	@rm -f $(DIR_EXE)/*
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