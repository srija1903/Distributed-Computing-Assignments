#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result,count;
	char str[80],instr[80];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("192.168.1.13");
	address.sin_port=9139;
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr*)&address,len);
	if(result==-1)
	{
		printf("error\n");
		exit(1);
	}
	fflush(stdout);
	while(1) 
	{
		printf("\nEnter string:");
		fgets(instr,80,stdin);
		write(sockfd,instr,strlen(instr)+1);
		count=read(sockfd,str,20);
		if(strncmp("bye", instr, 3) == 0)
    		{
        		printf("OK Bye!\n");
        		close(sockfd);
			// pthread_exit(NULL);
        		exit(0);
    		}
		printf("Received message from server:");
		printf("%s\n",str);
		if(strncmp("bye", str, 3) == 0)
    		{
        		printf("OK Bye!\n");
        		close(sockfd);
        		exit(0);
    		}
}
// close(sockfd);
// exit(0);
}







