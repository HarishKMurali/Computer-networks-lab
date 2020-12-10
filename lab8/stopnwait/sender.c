#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

int main()
{
	
	int c_sock;
	//char buf[100];
	//char bufr[100];
	c_sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr=INADDR_ANY;

	if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
	{
			printf("server is busy\nconnection failure");
			return 0;
	}

	char buf[2];
	buf[1]='\0';
	char msg[50];
	printf("\nEnter message to be sent:\n");
	gets(msg);
	char stringend[2];
	stringend[1]='\0';
	
	for(int i=0;i<strlen(msg);++i)
	{
		buf[0]=msg[i];
		char ack[2];
		stringend[0]='0';
		send(c_sock,stringend,sizeof(stringend),0);
		send(c_sock,buf,sizeof(buf),0);
		recv(c_sock,ack,sizeof(ack),0);
		printf("%c ",ack[0]);
		if(ack[0]=='0')i-=1;
	}
	stringend[0]='1';
	send(c_sock,stringend,sizeof(stringend),0);
	printf("\nmessage sent\n");
	close(c_sock);
	return 0;
}
