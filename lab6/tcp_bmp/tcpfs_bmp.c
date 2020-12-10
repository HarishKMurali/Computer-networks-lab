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
	char buf[100];
	char buf2[100];
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

	
	FILE *fp;
	fp=fopen("bitmap_copy.bmp","wb");
	int ch[1];
	
	read(c_client,ch,sizeof(ch));
	while(ch[0]!=EOF)
	{
		fputc(ch[0],fp);
		read(c_client,ch,sizeof(ch));
	}
	printf("\nfile received successfully\n");
	printf("data copied into file bitmap_copy.bmp\n");
	
	fclose(fp);
	close(s_sock);
	return 0;
}
