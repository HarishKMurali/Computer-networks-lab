#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int s_sock,c_client;
	char buf[20];
	char buf2[20];
	s_sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server,other;
	server.sin_family=AF_INET;
	server.sin_port=htons(9009);
	server.sin_addr.s_addr=INADDR_ANY;
	int k=bind(s_sock,(struct sockaddr*)&server,sizeof(server));
	if(k==-1)
	{
		printf("connection failed!\n");
		exit(0);
	}
	socklen_t add;
	add=sizeof(other);
	int n=recvfrom(s_sock,buf,sizeof(buf),0,(struct sockaddr*)&other,&add);
	printf("msg from client: %s\n",buf);

	FILE *fp;
	fp=fopen("india-flag1.gif","wb");
	int ch[1];

	n=recvfrom(s_sock,ch,sizeof(ch),0,(struct sockaddr*)&other,&add);
	while(ch[0]!=EOF)
	{
	fputc(ch[0],fp);
	n=recvfrom(s_sock,ch,sizeof(ch),0,(struct sockaddr*)&other,&add);
	}
	printf("\nfile received successfully\n");
	printf("data copied into file sample2.mp3\n");

	fclose(fp);

	return 0;
}
