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
	char buf[50];
	char bufr[20];
	c_sock=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr=INADDR_ANY;

	FILE *fp;
	fp=fopen("sample.mp3","rb");;
	if(fp==NULL)
	{
		printf("\nfile doesnot exist!\n");
		exit(1);
	}
	strcpy(buf,"connected\nwait;sending in process\n");
	printf("connected\n");
	sendto(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));

	int ch[1];
	clock_t start,end;
	double cpu_time_used;
	start= clock();
	
	while((ch[0]=fgetc(fp))!=EOF)
	{
		sendto(c_sock,ch,sizeof(ch),0,(struct sockaddr*)&client,sizeof(client));
		sleep(0.01);
	}
	ch[0]=EOF;

	sendto(c_sock,ch,sizeof(ch),0,(struct sockaddr*)&client,sizeof(client));
	printf("\nmp3 file sent successfully\n");
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("Time taken for file transfer %f\n",cpu_time_used);
	fclose(fp);

	return 0;
}
