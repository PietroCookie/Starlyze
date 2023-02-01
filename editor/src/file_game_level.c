#include "file_game_level.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "functions.h"
#include "sprite.h"

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

void save_modification_game_level(file_game_level_t* file_game_level, game_level_t game_level, int posX, int posY){
	int write_id_sprite = -1;
	off_t position = file_game_level->address_table.table[file_game_level->current_level_index_address_table].position;
	
	position += 2 * sizeof(int) + posX * game_level.width * sizeof(int) + posY * sizeof(int);

	if(lseek(file_game_level->fd, position, SEEK_SET) == -1){
		ncurses_stop();
		perror("Error with lseek in save_modification_game_level");
		exit(EXIT_FAILURE);
	}

	if(game_level.elements_map[posX][posY] != NULL){
		write_id_sprite = game_level.elements_map[posX][posY]->id_sprite;
	}

	if(write(file_game_level->fd, &write_id_sprite, SEEK_SET) == -1){
		ncurses_stop();
		perror("Error write modification game level in save_modification_game_level");
		exit(EXIT_FAILURE);
	}
}

void first_save_game_level(file_game_level_t* file_game_level, game_level_t game_level){
	off_t position_save;
	size_t size_necessary;
	address_table_t new_address_table;

	file_game_level->current_level_index_address_table++;

	if(file_game_level->current_level_index_address_table >= DEFAULT_SIZE_ADDRESS_TABLE-1){
		initialize_address_table(&new_address_table);
		size_necessary = calculate_necessary_size(new_address_table);
		if((position_save = search_position_free(file_game_level, size_necessary)) == -1){
			if((position_save = lseek(file_game_level->fd, 0, SEEK_END)) == -1){
				ncurses_stop();
				perror("Error with lseek in first_save_game_level");
				exit(EXIT_FAILURE);
			}
		}
		file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position = position_save;
		file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].size = size_necessary;
		save_address_table_file(file_game_level->fd, file_game_level->address_table.position, &file_game_level->address_table);
		new_address_table.table[0].position = file_game_level->address_table.position;
		new_address_table.table[0].size = calculate_necessary_size(file_game_level->address_table);
		file_game_level->address_table = new_address_table;
		save_address_table_file(file_game_level->fd, position_save, &file_game_level->address_table);
		file_game_level->current_level_index_address_table = 1;
	}

	size_necessary = calculate_necessary_size_save_game_level(game_level);

	if((position_save = search_position_free(file_game_level, size_necessary)) == -1){
		if((position_save = lseek(file_game_level->fd, 0, SEEK_END)) == -1){
			ncurses_stop();
			perror("Error with lseek in first_save_game_level");
			exit(EXIT_FAILURE);
		}
	}else{
		if(lseek(file_game_level->fd, position_save, SEEK_SET) == -1){
			ncurses_stop();
			perror("Error with lseek in first_save_game_level");
			exit(EXIT_FAILURE);
		}
	}

	write_game_level_in_file(file_game_level->fd, position_save, game_level);
	file_game_level->address_table.table[file_game_level->current_level_index_address_table].position = position_save;
	file_game_level->address_table.table[file_game_level->current_level_index_address_table].size = size_necessary;
	save_address_table_file(file_game_level->fd, file_game_level->address_table.position, &file_game_level->address_table);
}

void delete_in_file_game_level(file_game_level_t* file_game_level){
	
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

	if(file_game_level->current_level_index_address_table <= 0){
		if(file_game_level->address_table.table[0].position != -1){
			read_address_table_file(file_game_level->fd, file_game_level->address_table.table[0].position, &file_game_level->address_table);
			file_game_level->current_level_index_address_table = DEFAULT_SIZE_ADDRESS_TABLE-2;
		}else{
			file_game_level->current_level_index_address_table = 1;
		}
	}else if(file_game_level->current_level_index_address_table >= DEFAULT_SIZE_ADDRESS_TABLE-1){
		if(file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position != -1){
			read_address_table_file(file_game_level->fd, file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position, &file_game_level->address_table);
			file_game_level->current_level_index_address_table = 1;
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
			address_table_new.table[0].position = file_game_level->address_table.position;
			address_table_new.table[0].size = calculate_necessary_size(file_game_level->address_table);
			file_game_level->address_table = address_table_new;
			save_address_table_file(file_game_level->fd, position, &file_game_level->address_table);
			file_game_level->current_level_index_address_table = 1;
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
	size_t size = 2 * sizeof(int) + game_level.width * game_level.height * sizeof(int);

	return size;
}

void read_game_level_in_file(int fd, off_t position, game_level_t* game_level){
	int width, height, i, j, id_sprite_read;
	element_map_t* element_read;

	if(lseek(fd, position, SEEK_SET) == -1){
		ncurses_stop();
		perror("Error with lseek in read_game_level_in_file");
		exit(EXIT_FAILURE);
	}

	if(read(fd, &width, sizeof(int)) == -1){
		ncurses_stop();
		perror("Error read width game_level in read_game_level_in_file");
		exit(EXIT_FAILURE);
	}

	if(read(fd, &height, sizeof(int)) == -1){
		ncurses_stop();
		perror("Error read height  game_level in read_game_level_in_file");
		exit(EXIT_FAILURE);
	}

	initialise_game_level(game_level, width, height);

	for(i = 0; i < game_level->width; i++){
		for (j = 0; j < game_level->height; j++)
		{
			if(read(fd, &id_sprite_read, sizeof(int)) == -1){
				ncurses_stop();
				perror("Error read id_sprite of element in read_game_level_in_file");
				exit(EXIT_FAILURE);
			}
			if(id_sprite_read != -1){
				if((element_read = malloc(sizeof(element_map_t))) == NULL){
					ncurses_stop();
					perror("Error allocating memory for element_read in read_game_level_in_file");
					exit(EXIT_FAILURE);
				}
				element_read->id_sprite = id_sprite_read;
				element_read->posX = i;
				element_read->posY = j;
				element_read->width = width_sprite(id_sprite_read);
				element_read->height = height_sprite(id_sprite_read);
				add_element_map_in_case(game_level, element_read);
			}
		}
	}
}

void write_game_level_in_file(int fd, off_t position, game_level_t game_level){
	int i, j;
	element_map_t* element;

	if(lseek(fd, position, SEEK_SET) == -1){
		ncurses_stop();
		perror("Error with lseek in first_save_game_level");
		exit(EXIT_FAILURE);
	}

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

	for(i = 0; i < game_level.width; i++){
		for (j = 0; j < game_level.height; j++)
		{
			if((element = game_level.elements_map[i][j]) != NULL && element->posX == i && element->posY == j)	{
				if(write(fd, &element->id_sprite, sizeof(int)) == -1){
					ncurses_stop();
					perror("Error write id_sprite in write_game_level_in_file");
					exit(EXIT_FAILURE);
				}
			}else{
				if(write(fd, -1, sizeof(int)) == -1){
					ncurses_stop();
					perror("Error write case in write_game_level_in_file");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}