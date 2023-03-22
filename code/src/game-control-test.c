#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "game_control.h"

int main(int argc, char const *argv[])
{
	pid_t game_pid;


	if((game_pid = fork()) == -1){
		perror("Error creating child process");
		exit(EXIT_FAILURE);
	}

	if(game_pid > 0) {
		if(wait(NULL) == -1) {
			perror("Error waiting child process");
			exit(EXIT_FAILURE);
		}
	}
	else {
		game_control(1);
	}

	return EXIT_SUCCESS;
}
