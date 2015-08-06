/**********************************
tcp_ser4.c: the source file of the server in tcp transmission 
***********************************/
#include "headsock4.h"

#define BACKLOG 10
#define ERROR_PROBABILITY 10

void str_ser(int sockfd);

int main(void)
{
	int sockfd, con_fd, ret;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;

	pid_t pid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);//create socket
	if (sockfd <0)
	{
		printf("error in socket!");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYTCP_PORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("172.0.0.1");
	bzero(&(my_addr.sin_zero), 8);
	ret = bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));//bind socket
	if (ret <0)
	{
		printf("error in binding");
		exit(1);
	}
	
	ret = listen(sockfd, BACKLOG); //listen
	if (ret <0) {
		printf("error in listening");
		exit(1);
	}

	while (1)
	{
		printf("waiting for data\n");
		sin_size = sizeof (struct sockaddr_in);
		con_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); //accept the packet
		
		if (con_fd <0)
		{
			printf("error in accept\n");
			exit(1);
		}

		if ((pid = fork())==0) // create acception process
		{
			close(sockfd);
			str_ser(con_fd); //receive packet and response
			close(con_fd);
			exit(0);
		}
		else close(con_fd); //parent process
	}
	close(sockfd);
	exit(0);
}

void str_ser(int sockfd){
	char buf[BUFSIZE];
	FILE *fp;
	struct ack_so ack;
	struct pack_so pack;	
	int end, n = 0;
	long lseek=0;
	end = 0;
	
	printf("receiving data!\n");
	srand ( time(NULL) );
	
	ack.len = 0;
	ack.num = 0;
	
	while (!end){
		int error_chance = rand() % 100 + 1;
		//printf("Error_chance is %d\n", error_chance);
		
		if ((n = recv(sockfd, &pack, PACKLEN, 0)) == -1){
			printf("error when receiving\n");
			exit(1);
		}
			
		if (pack.data[pack.len-1] == '\0'){	//if it is the end of the file
			end = 1;
			pack.len--;
		}
	
		if (pack.num <= ack.num) {
			if (pack.num == ack.num){
				ack.num++;
				memcpy((buf+lseek), pack.data, pack.len);
				lseek += pack.len;
			}
			
			if (error_chance > ERROR_PROBABILITY){
				if ((n = send(sockfd, &ack, 2, 0))==-1){
					printf("send error!");	//send the ack
					exit(1);
				}
			}	
		}
	}
	
	if ((fp = fopen ("myTCPreceive.txt","wt")) == NULL)
	{
		printf("File doesn't exit\n");
		exit(0);
	}
	fwrite (buf , 1 , lseek , fp);//write data into file
	fclose(fp);
	printf("a file has been successfully received!\nthe total data received is %d bytes\n", (int)lseek);
}
