/**
 * @file address_table.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage address_table
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __ADDRESS_TABLE_H__
#define __ADDRESS_TABLE_H__

#include <stdlib.h>

#define DEFAULT_SIZE_ADDRESS_TABLE 10

/**
 * @brief An entry in the address table
 * 
 */
typedef struct
{
	off_t position;
	size_t size;
} entry_address_table_t;

/**
 * @brief An address table
 * 
 */
typedef struct{
	entry_address_table_t table[DEFAULT_SIZE_ADDRESS_TABLE];
	off_t position;
} address_table_t;

/**
 * @brief Initialize an address table
 * 
 * @param address_table The address table that is initialized
 */
void initialize_address_table(address_table_t* address_table);

/**
 * @brief Allows to know if an address table is full or not
 * 
 * @param address_table The address table which we want to know if it is full or not
 * @return int True if the address table is full, false otherwise
 */
int address_table_full(address_table_t address_table);

/**
 * @brief Write an address table to a file descriptor
 * 
 * @param file_descriptor The file descriptor
 * @param address_table The address table
 */
void write_address_table_in_file_descriptor(int file_descriptor, address_table_t address_table);
/**
 * @brief Reads an address table from a file descriptor
 * 
 * @param file_descriptor The file descriptor
 * @return address_table_t The address table
 */
address_table_t read_address_table_in_file_descriptor(int file_descriptor);

/**
 * @brief Saves changes to the address table in the file descriptor
 * 
 * @param file_descriptor The file descriptor
 * @param address_table The address table
 * @param id_table The identifier of the table entry to be saved
 */
void save_modification_address_table(int file_descriptor, address_table_t address_table, int id_table);

/**
 * @brief Adds an entry in the address table
 * 
 * @param address_table The address table
 * @param entry The input that is addeds
 * @return int The position of the entry in the address table or -1 if the table is fulls
 */
int add_entry_in_address_table(address_table_t* address_table, entry_address_table_t entry);
/**
 * @brief Delete an entry from the address table
 * 
 * @param address_table The address table
 * @param id_table The identifier of the entry to be deleted
 */
void remove_entry_in_address_table(address_table_t* address_table, int id_table);

/**
 * @brief The necessary size of an address table
 * 
 * @return size_t The necessary size
 */
size_t necessary_size_address_table();

#endif