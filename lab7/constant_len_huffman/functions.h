#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int c_socket;

int ClientCreate(int port, int anyip, char IPADDR[])		// Return 1 for error
{
	c_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(port);
	if(anyip == 0) client.sin_addr.s_addr = inet_addr(IPADDR);
	else client.sin_addr.s_addr = INADDR_ANY;
	if(connect(c_socket, (struct sockaddr *)&client, sizeof(client)) == -1)
	{
		printf("Connection Issue.\n");
		return 1;
	}
	else return 0;
}


struct node *rptr=NULL;

struct node{
	struct node *lcptr;
	char sym;
	int freq;
	struct node *rcptr;
};

struct lookup{
	char s;
	char code[200];
};



char s[200];
char ds[200];
int f[200];
int n;
int nc;
struct lookup LookUpTable[200];
int lookup_size;

char encodedseq[200] = "";


void ISort(){
	for(int i=1;i<nc;i++){
		for(int j=i;j>0;j--){
			if(f[j-1]>f[j]){
				int temp=f[j];
				f[j]=f[j-1];
				f[j-1]=temp;
				
				char temp2=ds[j];
				ds[j]=ds[j-1];
				ds[j-1]=temp2;
			}
			else break;
		}
	}
}


void Read(){
	printf("Enter the string: ");
	scanf(" %[^\n]", s);
	n = strlen(s);
	lookup_size = 0;
}

void count(){
	nc=0;
	for(int i=0;i<n;i++){
		int flag=0;
		//ds[0]=0;
		for(int j=0;j<nc;j++){
			if(s[i]==ds[j]){
				flag=1;
				break;
			}
		}
		if(flag==0 ){
			ds[nc]=s[i];
			nc++;
		}
	}
	for(int i=0;i<nc;i++){
		int cou=0;
		for(int j=0;j<n;j++){
			if(ds[i]==s[j]){
				cou++;
			}
		}
		f[i]=cou;
	}
	
	ISort();

}

void lookuptablefn(struct node *ptr, char en[], int ensize, char chars[]){
	
		int maxnoofbits = 10;

		int noofchars = strlen(chars);

		int noofbits = 1;
		int twopow = 2;
		for(int i=0;i<maxnoofbits;i++)		///////////////////	// MAX NO OF BITS ALLOWED = 10 // ////////////////////////
		{
			if(noofchars <= twopow)
			{
				i = maxnoofbits;
			}
			else
			{
				twopow *= 2;
				noofbits++;
			}
		}

		char code[noofbits];
		for(int i=0;i<noofbits;i++) code[i] = '0';

		for(int i=0;i<noofchars;i++)
		{
			for(int j=0;j<noofbits;j++)
			{
				if(code[j] == '1') code[j] = '0';
				else if(code[j] == '0')
				{
					code[j] = '1';
					j = noofbits;
				}
			}
			LookUpTable[(int)chars[i]].s = chars[i];
			strcpy(LookUpTable[(int)chars[i]].code, code);
			printf("Code: %c - %s\n", chars[i], LookUpTable[(int)chars[i]].code);
		}
	
	
}

void Encoder(){
	printf("Encoded Sequence: ");
	char temp[400];

	for(int i=0;i<n;i++){
		int index = (int)(s[i]);

		printf("%s", LookUpTable[index].code);
		strcat(encodedseq, LookUpTable[index].code);
	}
	printf("\n");
}

void print(struct node *ptr){
	if(ptr!=NULL){
		print(ptr->lcptr);
		printf("\n");
		printf("%c - %d", ptr->sym, ptr->freq);
		printf("\n");
		print(ptr->rcptr);
	}
}