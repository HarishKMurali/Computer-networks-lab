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
	char buf[100];
	char bufr[100];
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
	FILE *fp;
	fp=fopen("india-flag.gif","rb");;
	if(fp==NULL)
	{
		printf("\nfile doesnot exist!\n");
		exit(1);
	}
	int ch[1];
	clock_t start,end;
	double cpu_time_used;
	start= clock();
	while((ch[0]=fgetc(fp))!=EOF)
	{
		write(c_sock,ch,sizeof(ch));
	}
	ch[0]=EOF;
	write(c_sock,ch,sizeof(ch));
	printf("\nfile sent successfully\n");
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("Time taken for file transfer %f\n",cpu_time_used);
	fclose(fp);
	close(c_sock);
	return 0;
}
