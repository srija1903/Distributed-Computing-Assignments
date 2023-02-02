#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
void *server_thread(void *arg)
{
	int client_sockfd;
	char instr[80],name[80];
	int count=0;
	while(1) {
		client_sockfd=(int)arg;
		count=read(client_sockfd,instr,20);
		instr[count]='\0';
		printf("Message from client: %s\n",instr);
		// strcpy(name,"Thank you ");
		// strcat(name,instr);
		// strcpy(instr,name);
		if(strncmp("bye", instr, 3) == 0)
    		{
        		printf("OK Bye!\n");
        		close(client_sockfd);
			// pthread_exit(NULL);
        		exit(0);
    		}
		printf("Enter string:");
		fgets(name,80,stdin);
		write(client_sockfd,name,strlen(name)+1);
		if(strncmp("bye",name, 3) == 0)
    		{
        		printf("OK Bye!\n");
        		close(client_sockfd);
			// pthread_exit(NULL);
        		exit(0);
    		}
	}
	// close(client_sockfd);
	// pthread_exit(NULL);
}
int main()
{
	int server_sockfd,client_sockfd;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	pthread_t t;
	server_sockfd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("192.168.1.13");
	server_address.sin_port=9139;
	server_len=sizeof(server_address);
	if(bind(server_sockfd,(struct sockaddr*)&server_address,server_len)==-1)
	{
		printf("server error");
		exit(1);
	}
	printf("server waiting....\n");
	listen(server_sockfd,5);
	while(1)
	{
		client_len=sizeof(client_address);
		client_sockfd=accept(server_sockfd,(struct sockaddr*)&client_address,&client_len);
		printf("Created new client thread  %d\n",client_sockfd);
		pthread_create(&t,NULL,server_thread,(void *)client_sockfd);
	}
	return 0;
}















