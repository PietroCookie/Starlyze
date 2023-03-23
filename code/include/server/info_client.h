#ifndef __INFO_CLIENT_H__
#define __INFO_CLIENT_H__

#define MAX_MSG 255

struct info_client_t{
    int id; 
    char pseudo[MAX_MSG]; 
    char* client_address; 
    struct info_client_t* next;
    struct info_client_t* prev;
};
typedef struct info_client_t info_client_t;

// Liste
typedef struct{
    info_client_t* head; 
}list_info_client_t;


void init_list_info_client(list_info_client_t* list); 

info_client_t* init_info_client(int id, char pseudo[MAX_MSG], char* client_address); 

int is_empty(list_info_client_t* list); 

void add_client(list_info_client_t* list, info_client_t* client); 

void print_list_client(list_info_client_t list); 

info_client_t* search_client(list_info_client_t* list, int id); 

void delete_client(list_info_client_t* list, info_client_t* client);

void delete_list(list_info_client_t* list);




#endif