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

int address_table_full(address_table_t address_table){
	int i = 0, stop = 0;

	while (!stop && i < DEFAULT_SIZE_ADDRESS_TABLE-1)
	{
		if(address_table.table[i].position != -1){
			i++;
		}else{
			stop = 1;
		}
	}
	
	return (i >= DEFAULT_SIZE_ADDRESS_TABLE-1);
}

void write_address_table_in_file_descriptor(int file_descriptor, address_table_t address_table){
	int i;

	for (i = 0; i < DEFAULT_SIZE_ADDRESS_TABLE; i++)
	{
		if(write(file_descriptor, &address_table.table[i].position, sizeof(off_t)) == -1){
			perror("Error saving address table");
			exit(EXIT_FAILURE);
		}
		if(write(file_descriptor, &address_table.table[i].size, sizeof(size_t)) == -1){
			perror("Error saving address table");
			exit(EXIT_FAILURE);
		}
	}
}

address_table_t read_address_table_in_file_descriptor(int file_descriptor){
	int i;
	address_table_t address_table;

	if((address_table.position = lseek(file_descriptor, 0, SEEK_CUR)) == -1){
		perror("Error with lseek read_address_table_file");
		exit(EXIT_FAILURE);
	}

	initialize_address_table(&address_table);

	for (i = 0; i < DEFAULT_SIZE_ADDRESS_TABLE; i++)
	{
		if(read(file_descriptor, &address_table.table[i].position, sizeof(off_t)) == -1){
			perror("Error read position of an entry in address table");
			exit(EXIT_FAILURE);
		}
		if(read(file_descriptor, &address_table.table[i].size, sizeof(size_t)) == -1){
			perror("Error read size of an entry in address table");
			exit(EXIT_FAILURE);
		}
	}

	return address_table;
}

void save_modification_address_table(int file_descriptor, address_table_t address_table, int id_table){
	off_t position;

	position = address_table.position + id_table * (sizeof(off_t) + sizeof(size_t));

	if(lseek(file_descriptor, position, SEEK_SET) == -1){
		perror("Error with lseek");
		exit(EXIT_FAILURE);
	}

	if(write(file_descriptor, &address_table.table[id_table].position, sizeof(off_t)) == -1){
		perror("Error write position of entry in save_modification_address_table");
		exit(EXIT_FAILURE);
	}

	if(write(file_descriptor, &address_table.table[id_table].size, sizeof(size_t)) == -1){
		perror("Error write size of entry in save_modification_address_table");
		exit(EXIT_FAILURE);
	}
}

size_t necessary_size_address_table(){
	size_t size = DEFAULT_SIZE_ADDRESS_TABLE * (sizeof(off_t) + sizeof(size_t));

	return size;
}

int add_entry_in_address_table(address_table_t* address_table, entry_address_table_t entry){
	int i = 0, stop = 0;

	if(address_table_full(*address_table)){
		return -1;
	}

	while (!stop && i < DEFAULT_SIZE_ADDRESS_TABLE)
	{
		if(address_table->table[i].position != -1){
			i++;
		}
		else{
			stop = 1;
		}
	}

	address_table->table[i] = entry;

	return i;
}

void remove_entry_in_address_table(address_table_t* address_table, int id_table){
	address_table->table[id_table].position = -1;
	address_table->table[id_table].size = 0;
}