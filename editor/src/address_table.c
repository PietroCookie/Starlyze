#include "address_table.h"

#include <stdio.h>
#include <unistd.h>

void initialize_address_table(address_table_t* address_table){
	int i;

	for (i = 0; i < DEFAULT_SIZE_ADDRESS_TABLE; i++)
	{
		address_table->table[i].position = -1;
		address_table->table[i].size = 0;
	}
}

void save_address_table_file(int fd, off_t position, address_table_t* address_table){
	int i;

	if(lseek(fd, position, SEEK_SET) == -1){
		perror("Error with lseek read_address_table_file");
		exit(EXIT_FAILURE);
	}

	address_table->position = position;

	for (i = 0; i < DEFAULT_SIZE_ADDRESS_TABLE; i++)
	{
		if(write(fd, &address_table->table[i].position, sizeof(off_t)) == -1){
			perror("Error saving address table");
			exit(EXIT_FAILURE);
		}
		if(write(fd, &address_table->table[i].size, sizeof(size_t)) == -1){
			perror("Error saving address table");
			exit(EXIT_FAILURE);
		}
	}
}

void read_address_table_file(int fd, off_t position, address_table_t* address_table){
	int i;

	if(lseek(fd, position, SEEK_SET) == -1){
		perror("Error with lseek read_address_table_file");
		exit(EXIT_FAILURE);
	}

	initialize_address_table(address_table);
	address_table->position = position;

	for (i = 0; i < DEFAULT_SIZE_ADDRESS_TABLE; i++)
	{
		if(read(fd, &address_table->table[i].position, sizeof(off_t)) == -1){
			perror("Error read position of an entry in address table");
			exit(EXIT_FAILURE);
		}
		if(read(fd, &address_table->table[i].size, sizeof(size_t)) == -1){
			perror("Error read size of an entry in address table");
			exit(EXIT_FAILURE);
		}
	}
}

size_t calculate_necessary_size(address_table_t address_table){
	size_t size = DEFAULT_SIZE_ADDRESS_TABLE * (sizeof(off_t) + sizeof(size_t));

	return size;
}