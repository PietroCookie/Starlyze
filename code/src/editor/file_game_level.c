#include "file_game_level.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

game_level_t open_file_game_level(const char* name_file, file_game_level_t* file_game_level){
	game_level_t game_level;
	int file_exist = 1;
	
    if ((file_game_level->file_descriptor = open(name_file, O_RDWR, S_IWUSR | S_IRUSR)) == -1){
        if (errno == ENOENT){
			if((file_game_level->file_descriptor = open(name_file, O_RDWR | O_CREAT, S_IRUSR|S_IWUSR )) == -1){
				
				perror("Error create file");
				exit(EXIT_FAILURE);
			}
            file_exist = 0;
        }else{		
            perror("Error open file");
            exit(EXIT_FAILURE);
        }
    }

	file_game_level->current_index_address_table = 0;
	
	if(file_exist){
		file_game_level->address_table = read_address_table_in_file_descriptor(file_game_level->file_descriptor);
		file_game_level->address_table_void = read_address_table_in_file_descriptor(file_game_level->file_descriptor);

		load_level_in_file(file_game_level, &game_level, 1);
	}else{
		initialize_address_table(&file_game_level->address_table);
		file_game_level->address_table.position = 0;
		file_game_level->address_table.table[0].position = 0;
		file_game_level->address_table.table[0].size = 0;
		write_address_table_in_file_descriptor(file_game_level->file_descriptor, file_game_level->address_table);

		initialize_address_table(&file_game_level->address_table_void);
		file_game_level->address_table_void.position = necessary_size_address_table();
		write_address_table_in_file_descriptor(file_game_level->file_descriptor, file_game_level->address_table_void);
		
		initialise_game_level(&game_level);
		first_save_game_level_in_file(file_game_level, game_level);
	}

	return game_level;
}

void delete_file_game_level(file_game_level_t* file_game_level){
	if(close(file_game_level->file_descriptor)){
		perror("Error closing file");
		exit(EXIT_FAILURE);
	}
}

void add_address_table(file_game_level_t* file_game_level){
	address_table_t address_table_new;
	entry_address_table_t entry;
	off_t position;
	int id_table;

	initialize_address_table(&address_table_new);

	entry.position = file_game_level->address_table.position;
	entry.size = necessary_size_address_table();
	add_entry_in_address_table(&address_table_new, entry);

	id_table = search_position_free(file_game_level, entry.size);
	if(id_table == -1){
		if((position = lseek(file_game_level->file_descriptor, 0, SEEK_END)) == -1){
			perror("Error with lseek in add_address_table");
			exit(EXIT_FAILURE);
		}
	}else{
		position = file_game_level->address_table_void.table[id_table].position;

		if((file_game_level->address_table_void.table[id_table].size -= entry.size) == 0){
			file_game_level->address_table_void.table[id_table].position = -1;
		}else{
			file_game_level->address_table_void.table[id_table].position += entry.size;
		}
		save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table_void, id_table);

		if(lseek(file_game_level->file_descriptor, position, SEEK_SET) == -1){
			perror("Error with lseek in add_address_table");
			exit(EXIT_FAILURE);
		}
	}

	address_table_new.position = position;
	write_address_table_in_file_descriptor(file_game_level->file_descriptor, address_table_new);

	entry.position = position;
	
	file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1] = entry;
	save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table, DEFAULT_SIZE_ADDRESS_TABLE-1);

	file_game_level->address_table = address_table_new;
}

void add_address_table_void(file_game_level_t* file_game_level){
	address_table_t address_table_new;
	entry_address_table_t entry;
	off_t position;
	int id_table;

	initialize_address_table(&address_table_new);

	entry.position = file_game_level->address_table_void.position;
	entry.size = necessary_size_address_table();
	add_entry_in_address_table(&address_table_new, entry);

	id_table = search_position_free(file_game_level, entry.size);
	if(id_table == -1){
		if((position = lseek(file_game_level->file_descriptor, 0, SEEK_END)) == -1){
			perror("Error with lseek in add_address_table_void");
			exit(EXIT_FAILURE);
		}
	}else{
		position = file_game_level->address_table_void.table[id_table].position;

		if((file_game_level->address_table_void.table[id_table].size -= entry.size) == 0)
			file_game_level->address_table_void.table[id_table].position = -1;
		else
			file_game_level->address_table_void.table[id_table].position += entry.size;
		
		save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table_void, id_table);

		if(lseek(file_game_level->file_descriptor, position, SEEK_SET) == -1){
			perror("Error with lseek in add_address_table_void");
			exit(EXIT_FAILURE);
		}
	}

	address_table_new.position = position;
	write_address_table_in_file_descriptor(file_game_level->file_descriptor, address_table_new);

	entry.position = position;
	
	while (file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position != -1)
	{
		if(lseek(file_game_level->file_descriptor, file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position, SEEK_SET) == -1){
			perror("Error with lseek in add_address_table_void");
			exit(EXIT_FAILURE);
		}
		file_game_level->address_table_void = read_address_table_in_file_descriptor(file_game_level->file_descriptor);
	}
	
	file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1] = entry;
	save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table, DEFAULT_SIZE_ADDRESS_TABLE-1);

	file_game_level->address_table = address_table_new;
}

void first_save_game_level_in_file(file_game_level_t* file_game_level, game_level_t game_level){
	int id_table;
	off_t position;
	entry_address_table_t entry;

	entry.size = necessary_size_game_level(game_level);
	id_table = search_position_free(file_game_level, entry.size);

	if(id_table == -1){
		if((position = lseek(file_game_level->file_descriptor, 0, SEEK_END)) == -1){
			perror("Error with lseek in first_save_game_level_in_file");
			exit(EXIT_FAILURE);
		}
	}else{
		position = file_game_level->address_table_void.table[id_table].position;

		if((file_game_level->address_table_void.table[id_table].size -= entry.size) == 0){
			file_game_level->address_table_void.table[id_table].position = -1;
		}else{
			file_game_level->address_table_void.table[id_table].position += entry.size;
		}
		save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table_void, id_table);

		if(lseek(file_game_level->file_descriptor, position, SEEK_SET) == -1){
			perror("Error with lseek in first_save_game_level_in_file");
			exit(EXIT_FAILURE);
		}
	}

	write_game_level_in_file_descriptor(file_game_level->file_descriptor, game_level);
	
	entry.position = position;

	search_void_entry_address_table(file_game_level);
	id_table = add_entry_in_address_table(&file_game_level->address_table, entry);

	file_game_level->current_index_address_table = id_table;
	
	save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table, id_table);
}

void save_modification_game_level(file_game_level_t* file_game_level, game_level_t game_level, int posX, int posY){
	save_modification_game_level_in_file_descriptor(file_game_level->file_descriptor, file_game_level->address_table.table[file_game_level->current_index_address_table].position, game_level, posX, posY);
}

void delete_game_level_in_file(file_game_level_t* file_game_level){
	entry_address_table_t entry;

	entry = file_game_level->address_table.table[file_game_level->current_index_address_table];

	file_game_level->address_table.table[file_game_level->current_index_address_table].position = -1;
	file_game_level->address_table.table[file_game_level->current_index_address_table].size = 0;
	save_modification_address_table(file_game_level->file_descriptor, file_game_level->address_table, file_game_level->current_index_address_table);
	
	while (address_table_full(file_game_level->address_table_void))
	{
		if(file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position != -1){
			if(lseek(file_game_level->file_descriptor, file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position, SEEK_SET) == -1){
				perror("Error with lseek in delete_game_level_in_file");
				exit(EXIT_FAILURE);
			}
			file_game_level->address_table_void = read_address_table_in_file_descriptor(file_game_level->file_descriptor);
		}else{
			add_address_table_void(file_game_level);
		}
	}
	
	add_entry_in_address_table(&file_game_level->address_table_void, entry);
}

void load_level_in_file(file_game_level_t* file_game_level, game_level_t* game_level, int next){
	int valid = 0;
	address_table_t address_table = file_game_level->address_table;
	int next_index = file_game_level->current_index_address_table;

	if(next != 0){
		do
		{
			if(next > 0)
				next_index++;
			else
				next_index--;
			
			if(next_index >= DEFAULT_SIZE_ADDRESS_TABLE-1 || next_index <= 0){
				if(next_index >= DEFAULT_SIZE_ADDRESS_TABLE-1)
					next_index = DEFAULT_SIZE_ADDRESS_TABLE-1;
				else
					next_index = 0;

				if(file_game_level->address_table.table[next_index].position != -1){
					if(lseek(file_game_level->file_descriptor, file_game_level->address_table.table[next_index].position, SEEK_SET) == -1){
						perror("Error with lsekk in load_level_in_file");
						exit(EXIT_FAILURE);
					}

					file_game_level->address_table = read_address_table_in_file_descriptor(file_game_level->file_descriptor);

					if(next_index > 0 || address_table.table[0].size == 0){
						next_index = 1;
						next = 1;
					}
					else
						next_index = DEFAULT_SIZE_ADDRESS_TABLE-2;

				}else{
					valid = 1;
					file_game_level->address_table = address_table;
					if(next > 0){
						initialise_game_level(game_level);
						first_save_game_level_in_file(file_game_level, *game_level);
					}
					next_index = file_game_level->current_index_address_table;
				}
			}

			if(file_game_level->address_table.table[next_index].position != -1)
				valid = 1;

		} while (!valid);
	}

	file_game_level->current_index_address_table = next_index;
	
	if(lseek(file_game_level->file_descriptor, file_game_level->address_table.table[file_game_level->current_index_address_table].position, SEEK_SET) == -1){
		perror("Error with lseek in load_level_in_file");
		exit(EXIT_FAILURE);
	}

	read_game_level_in_file_descriptor(file_game_level->file_descriptor, game_level);
}

int search_position_free(file_game_level_t* file_game_level, size_t size_necessary){
	int id_table = 0;
	int nothing = 0;

	if(lseek(file_game_level->file_descriptor, necessary_size_address_table(), SEEK_SET) == -1){
		perror("Error with lseek in search_position_free");
		exit(EXIT_FAILURE);
	}
	file_game_level->address_table_void = read_address_table_in_file_descriptor(file_game_level->file_descriptor);

	while (!nothing && file_game_level->address_table_void.table[id_table].size < size_necessary)
	{
		id_table++;
		if(id_table >= DEFAULT_SIZE_ADDRESS_TABLE-1){
			if(file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position != -1){
				if(lseek(file_game_level->file_descriptor, file_game_level->address_table_void.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position, SEEK_SET) == -1){
					perror("Error with lseek in search_position_free");
					exit(EXIT_FAILURE);
				}
				file_game_level->address_table_void = read_address_table_in_file_descriptor(file_game_level->file_descriptor);
				id_table = 0;
			}else{
				id_table = -1;
				nothing = 1;
			}
		}
	}
	
	return id_table;
}

int search_void_entry_address_table(file_game_level_t* file_game_level){
	int index = 1, valid = 0;
	
	if(lseek(file_game_level->file_descriptor, 0, SEEK_SET) == -1){
		perror("Error with lseek in search_void_entry_address_table");
		exit(EXIT_FAILURE);
	}

	file_game_level->address_table = read_address_table_in_file_descriptor(file_game_level->file_descriptor);

	while (!valid)
	{
		if(index >= DEFAULT_SIZE_ADDRESS_TABLE-1){
			if(file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position != -1){
				if(lseek(file_game_level->file_descriptor, file_game_level->address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position, SEEK_SET) == -1){
					perror("Error with lseek in search_void_entry_address_table");
					exit(EXIT_FAILURE);
				}
				file_game_level->address_table = read_address_table_in_file_descriptor(file_game_level->file_descriptor);
			}else{
				add_address_table(file_game_level);
			}

			index = 1;
		}

		if(file_game_level->address_table.table[index].position != -1)
			index++;
		else
			valid = 1;
	}
	
	return index;
}
