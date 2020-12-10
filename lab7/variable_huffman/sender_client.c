#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include"functions.h"



int main()
{
	printf("Huffman Encoding Sender(client-side)\n");

	rptr=NULL;

	int error = ClientCreate(9009, 1, "");
	if(error == 1)
	{
		close(c_socket);
		printf("Connection Issue.\n");
		return 0;
	}
	else 
	{
		Read();
		count();

		printf("\nCharecters: %s\nchar - freq\n", ds);
		for(int i=0;i<nc;i++){
			printf("%c - %d\n", ds[i], f[i]);
		}

		struct node *ptrarr[200];
		for(int i=0;i<nc;i++)ptrarr[i]=NULL;
			BuildTree(f,ds,nc,ptrarr);
		printf("\n\n");
		

		printf("\nVariable Size Huffman Encoding\n");
		char en[200];
		lookuptablefn(rptr, en, 0, "");
		Encoder();
		printf("\n");
		
		

		char s[1];
		char code[100];

		send(c_socket, ds, sizeof(ds), 0);

		for(int i=0;i<strlen(ds);i++)
		{
			s[0] = LookUpTable[(int)ds[i]].s;
			strcpy(code, LookUpTable[(int)ds[i]].code);

			send(c_socket, s, sizeof(s), 0);
			send(c_socket, code, sizeof(code), 0);
		}
		
		send(c_socket, encodedseq, sizeof(encodedseq), 0);
		printf("Sent.\n");
	}

	close(c_socket);

	printf("\n");	
	return 0;
}
