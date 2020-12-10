#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int s_sock,c_client;
	//char buf[100];
	//char buf2[100];
	s_sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server,other;
	memset(&server,0,sizeof(server));
	memset(&other,0,sizeof(other));
	server.sin_family=AF_INET;
	server.sin_port=htons(9009);
	server.sin_addr.s_addr=INADDR_ANY;
	socklen_t addr_size;
	bind(s_sock,(struct sockaddr*)&server,sizeof(server));
	listen(s_sock,5);
	addr_size=sizeof(other);
	c_client=accept(s_sock,(struct sockaddr*)&other,&addr_size);

	char msg[50];
	char stringend[2],buf[2],ack[2];
	int window_size=2;

	int ws[1];
	recv(c_client,ws,sizeof(ws),0);
	window_size=ws[0];
	printf("\nEnter window size is ",ws);
	int msglen=0;
	recv(c_client,stringend,sizeof(stringend),0);
	while(stringend[0]=='0')
	{
		for(int i=0;i<window_size;i++)
					{
						recv(c_client, buf, sizeof(buf), 0);
						printf("Buf: %s\n", buf);
						msg[msglen] = buf[0];
						msglen++;
					}
					
					char ack_temp[2];
					for(int i=0;i<window_size;i++)
					{
						printf("Ack: ");
						//scanf("%s", ack_temp);
						gets(ack_temp);
						//printf("*%c",ack_temp[0]);
						ack[0] = ack_temp[0];
						
						send(c_client, ack, sizeof(ack), 0);
						if(ack[0] == '0')
						{
							msglen = msglen - window_size + i;
							i = window_size;
						}
					}
		recv(c_client,stringend,sizeof(stringend),0);
	}
	msg[msglen++]='\0';
	printf("\nReceived msg!\n");
	for(int i=0;i<msglen;++i)
	printf("%c",msg[i]);
	printf("\n");
	close(s_sock);
	close(c_client);
	return 0;
}