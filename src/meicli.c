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
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>


int main(int argc, char *argv[]) {
	int res;
	int sock = socket(AF_UNIX, SOCK_STREAM, 0);
	char out_buff[250] = {0};
	strcpy(out_buff,argv[1]);
	struct sockaddr_un address;
do
{
	memset(&address, 0x00, sizeof(address));
	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, "mei_command.sock", strlen("mei_command.sock"));
	res = connect(sock, (struct sockaddr *)&address, sizeof(address));
	//printf("connect = %d\n",res);//DEBUG
	usleep(100000);
}

while(res < 0);

	//printf("connect = %d\n",res);//DEBUG
	res = write(sock, out_buff, strlen(out_buff));
	//printf("write = %d\n",res);//DEBUG
	close(sock);
	return res;
}
