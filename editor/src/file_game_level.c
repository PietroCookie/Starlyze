#include "file_game_level.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "functions.h"

void open_file_game_level(const char* name_file, file_game_level_t* file_game_level){
	int file_exist = 1;
	
    if ((file_game_level->fd = open(name_file, O_RDWR, S_IWUSR | S_IRUSR)) == -1){
        if (errno == ENOENT){
			if((file_game_level->fd = open(name_file, O_RDWR | O_CREAT, S_IRUSR|S_IWUSR )) == -1){
				ncurses_stop();
				perror("Error create file");
				exit(EXIT_FAILURE);
			}
            file_exist = 0;
        }else{
			ncurses_stop();
            perror("Error open file");
            exit(EXIT_FAILURE);
        }
    }

	file_game_level->current_level_index_address_table = -1;
	
	if(file_exist){
		read_address_table_file(file_game_level->fd, 0, &file_game_level->address_table);
		read_address_table_file(file_game_level->fd, calculate_necessary_size(file_game_level->address_table)+1, &file_game_level->address_table_void);
	}else{
		initialize_address_table(&file_game_level->address_table);
		file_game_level->address_table.position = 0;
		save_address_table_file(file_game_level->fd, 0, &file_game_level->address_table);
		initialize_address_table(&file_game_level->address_table_void);
		file_game_level->address_table_void.position = calculate_necessary_size(file_game_level->address_table)+1;
		save_address_table_file(file_game_level->fd, file_game_level->address_table_void.position, &file_game_level->address_table_void);
	}
}

void delete_file_game_level(file_game_level_t* file_game_level){
	if(close(file_game_level->fd)){
		ncurses_stop();
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
}

void save_in_file_game_level(file_game_level_t* file_game_level, game_level_t game_level){
	off_t position;
	size_t size;
	int index_table = file_game_level->current_level_index_address_table + 1;

	size = calculate_necessary_size_save_game_level(game_level);

	if((position = search_position_free(file_game_level, size)) == -1){
		// TODO : pas de place dispo
	}

	if(lseek(file_game_level->fd, position, SEEK_SET) == -1){
		ncurses_stop();
		perror("Error with lseek in save_in_file_game_level");
		exit(EXIT_FAILURE);
	}

	size = calculate_necessary_size_save_game_level(game_level);

	// while (file_game_level->address_table.table[index_table].position != -1)
	// {
		
	// }
	
	if(file_game_level->address_table.table[index_table].position != -1)

	file_game_level->address_table.table[index_table].position = position;
	file_game_level->address_table.table[index_table].size = size;

	write_game_level_in_file(file_game_level->fd, game_level);
}




void load_level(file_game_level_t* file_game_level, game_level_t* game_level, int next){
	int width, height, i;
	element_map_t* element_read;
	address_table_t address_table_new;
	size_t size;
	off_t position;

	delete_game_level(game_level);
	
	if(next){
		file_game_level->current_level_index_address_table++;
	}else{
		file_game_level->current_level_index_address_table--;
	}

	if(file_game_level->current_level_index_address_table < 0){
		// TODO : Lire table d'adresse précédente et se placer à la fin de celle-ci
		file_game_level->current_level_index_address_table = DEFAULT_SIZE_ADDRESS_TABLE-2;
	}else if(file_game_level->current_level_index_address_table >= DEFAULT_SIZE_ADDRESS_TABLE-1){
		if(file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position != -1){
			read_address_table_file(file_game_level->fd, file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position, &file_game_level->address_table);
			file_game_level->current_level_index_address_table = 0;
		}else{
			initialize_address_table(&address_table_new);
			size = calculate_necessary_size(address_table_new);

			if((position = search_position_free(file_game_level, size)) == -1){
				if((position = lseek(file_game_level->fd, 0, SEEK_END)) == -1){
					ncurses_stop();
					perror("Error with lseek in load_level");
					exit(EXIT_FAILURE);
				}
			}
			file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position = position;
			file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].size = size;
			save_address_table_file(file_game_level->fd, file_game_level->address_table.position, &file_game_level->address_table);
			file_game_level->address_table = address_table_new;
			save_address_table_file(file_game_level->fd, position, &file_game_level->address_table);
		}
	}
	
	if(file_game_level->address_table.table[file_game_level->current_level_index_address_table].size == 0){
		initialise_game_level(game_level, DEFAULT_WIDTH_LEVEL_GAME, DEFAULT_HEIGHT_LEVEL_GAME);
		add_border_game_level(game_level);
	}else{
		read_game_level_in_file(file_game_level->fd, file_game_level->address_table.table[file_game_level->current_level_index_address_table].position, game_level);
	}
}

int search_position_free(file_game_level_t* file_game_level, size_t size_necessary){
	int index = 0, proceed = 1;
	off_t position;
	
	while (proceed)
	{
		if(index >= DEFAULT_SIZE_ADDRESS_TABLE - 1){
			if((position = file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE - 1].position) != -1){ // Si la case réservé pour la table d'adresse suivante est utilisé alors charge la prochaine table de vide
				read_address_table_file(file_game_level->fd, position, &file_game_level->address_table_void);
				index = 0;
			}else{ // Il n'y a pas d'autres tables de vide à tester
				index = -1;
				proceed = 0;
			}
		}else{
			index++;
		}

		if(index >= 0 && file_game_level->address_table_void.table[index].size >= size_necessary){
			proceed = 0;
		}
	}

	return index;
}

size_t calculate_necessary_size_save_game_level(game_level_t game_level){
	size_t size = 3 * sizeof(int);
	int i;

	for (i = 0; i < game_level.nb_elements; i++)
	{
		size += 5 * sizeof(int);
	}

	return size;
}

void read_game_level_in_file(int fd, off_t position, game_level_t* game_level){
	int width, height, i;
	element_map_t* element_read;

	if(lseek(fd, position, SEEK_SET)){
		ncurses_stop();
		perror("Error with lseek in read_game_level_in_file");
		exit(EXIT_FAILURE);
	}

	if(read(fd, &width, sizeof(int))){
		ncurses_stop();
		perror("Error read width game_level in load_level");
		exit(EXIT_FAILURE);
	}

	if(read(fd, &height, sizeof(int))){
		ncurses_stop();
		perror("Error read height  game_level in load_level");
		exit(EXIT_FAILURE);
	}

	initialise_game_level(game_level, width, height);

	if(read(fd, &game_level->nb_elements, sizeof(int))){
		ncurses_stop();
		perror("Error read number elements of game_level in load_level");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < game_level->nb_elements; i++)
	{
		if((element_read = malloc(sizeof(element_map_t))) == NULL){
			ncurses_stop();
			perror("Error allocating memory element_read in load_level");
			exit(EXIT_FAILURE);
		}

		if(read(fd, &element_read->posX, sizeof(int))){
			ncurses_stop();
			perror("Error read posX element of game_level in load_level");
			exit(EXIT_FAILURE);
		}

		if(read(fd, &element_read->posY, sizeof(int))){
			ncurses_stop();
			perror("Error read posY element of game_level in load_level");
			exit(EXIT_FAILURE);
		}

		if(read(fd, &element_read->width, sizeof(int))){
			ncurses_stop();
			perror("Error read width element of game_level in load_level");
			exit(EXIT_FAILURE);
		}

		if(read(fd, &element_read->height, sizeof(int))){
			ncurses_stop();
			perror("Error read height element of game_level in load_level");
			exit(EXIT_FAILURE);
		}

		if(read(fd, &element_read->id_sprite, sizeof(int))){
			ncurses_stop();
			perror("Error read id_sprite element of game_level in load_level");
			exit(EXIT_FAILURE);
		}

		add_element_map_in_case(game_level, element_read);
	}
}

void write_game_level_in_file(int fd, game_level_t game_level){
	int i, j;
	element_map_t* element;

	if(write(fd, &game_level.width, sizeof(int)) == -1){
		ncurses_stop();
		perror("Error write width game_level");
		exit(EXIT_FAILURE);
	}

	if(write(fd, &game_level.height, sizeof(int)) == -1){
		ncurses_stop();
		perror("Error write height game_level");
		exit(EXIT_FAILURE);
	}

	if(write(fd, &game_level.nb_elements, sizeof(int))){
		ncurses_stop();
		perror("Error write number of elements in game_level");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < game_level.width; i++)
	{
		for (j = 0; j < game_level.height; j++)
		{
			element = game_level.elements_map[i][j];
			if(element != NULL && element->posX == i && element->posY == j){
				if(write(fd, &element->posX, sizeof(int))){
					ncurses_stop();
					perror("Error write posX of element in game_level");
					exit(EXIT_FAILURE);
				}

				if(write(fd, &element->posY, sizeof(int))){
					ncurses_stop();
					perror("Error write posY of element in game_level");
					exit(EXIT_FAILURE);
				}

				if(write(fd, &element->width, sizeof(int))){
					ncurses_stop();
					perror("Error write width of element in game_level");
					exit(EXIT_FAILURE);
				}

				if(write(fd, &element->height, sizeof(int))){
					ncurses_stop();
					perror("Error write height of element in game_level");
					exit(EXIT_FAILURE);
				}

				if(write(fd, &element->id_sprite, sizeof(int))){
					ncurses_stop();
					perror("Error write id_sprite of element in game_level");
					exit(EXIT_FAILURE);
				}
			}
		}
		
	}
}