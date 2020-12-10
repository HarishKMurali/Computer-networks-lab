#include <bits/stdc++.h> 
using namespace std; 
#define TOTAL_CHARS 128
void decToBinary(int n,int len,FILE *ptr) 
{ 
    // array to store binary number 
    int binaryNum[32]; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
		while(i<len)
		{binaryNum[i]=0;
		++i;}
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
       { cout << binaryNum[j];fprintf(ptr,"%d",binaryNum[j]);} 
}  
int main() 
{ 
  
  	FILE *fptr=fopen("input.txt","r");
		FILE *ptr=fopen("lookup.txt","w");
		int _char[TOTAL_CHARS],freq[TOTAL_CHARS];
		char arr[TOTAL_CHARS];
    for(int i=0; i < TOTAL_CHARS; ++i) {
        _char[i] = 0;
    }
		char c;
    
    while((c=fgetc(fptr)) != EOF) {
        _char[c] = _char[c] + 1;
    }
		int size=0;
		for(int i=0;i<TOTAL_CHARS;++i)
		{
			if(_char[i]>0)
			{
				arr[size]=i;
				freq[size]=_char[i];
				size++;
			}
		}
		int len=ceil(log(size)/log(2));
		for(int i=0;i<size;++i)
		{
			cout<<"\n"<<arr[i]<<" ";
			fprintf(ptr,"%c",arr[i]);
			fputc(' ',ptr);
			decToBinary(i,len,ptr);
			fputc('\n',ptr);
		}
		
}
