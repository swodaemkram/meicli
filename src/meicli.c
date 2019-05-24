/*
 ============================================================================
 Name        : meicli.c
 Author      : Mark Meadows
 Version     : 01.00.00
 Copyright   : Copyright (c) 2019 Fireking Security Group
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
//#include <fcntl.h>
//#include <sys/epoll.h>
//#include <errno.h>
#include <netinet/in.h>

void help(void);

int main(int argc, char *argv[]) {
	int timeout = 0;
	int res;
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	char out_buff[250] = {0};
	system("clear");
	printf("Connecting please stand by ...\n");
	struct sockaddr_un address;

if(strlen(argv[1])<= 4)
{
	help();
}

strcpy(out_buff,argv[1]);

if(strcmp(out_buff,"help") == 0)
{
	help();
}

do
{
	memset(&address, 0x00, sizeof(address));
	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, "mei_command.sock", strlen("mei_command.sock"));
	res = connect(sock, (struct sockaddr *)&address, sizeof(address));
	//printf("connect = %d\n",res);//DEBUG
	usleep(100000);
	if (timeout > 50)
	{
		printf("Time out check server ....!\n");
		return(1);
	}
timeout++;
}
while(res < 0);
    printf("Command %s sent\n",out_buff);
	//printf("connect = %d\n",res);//DEBUG
	res = write(sock, out_buff, strlen(out_buff));
	//printf("write = %d\n",res);//DEBUG
	close(sock);
	return res;
}

void help(void)

{
	printf("\033[1;32m=========================================\n");
	printf("\033[1;33m           meicli ver 1.0.1\n");
	printf("\033[1;34m            By Mark Meadows \n");
	printf("\033[1;31m(c)Copyright 2019 Fireking Security Group\n");
	printf("\033[1;32m=========================================\n\033[0m");
	printf("is a command line Domain Socket Connector\n");
	printf("for the mei_service an API server for the\n");
	printf("    MEI family of Bill Validators\n");
	printf("\033[1;34m----------------------------------------\n\033[0m");
	printf(" The following commands are recognized \n");
	printf("\033[1;33mstack\n");
	printf("verify\n");
	printf("reset\n");
	printf("idle\n");
	printf("appver\n");
	printf("bootver\n");
	printf("model\n");
	printf("serial\n");
	printf("varname\n\033[0m");
	printf("[Usage: sudo meicli model]\n");
exit(0);
}

