#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<iostream>


FILE *e;
FILE *s;
	

void exclui_tags();

int main(){
	setlocale(LC_ALL,"Portuguese");
	
	int erro=0;//status
	
	e = fopen("arq.html","r");
	
	if((e=fopen("arq.html","r"))==NULL){
		printf("Não foi possível abrir o arquivo!");
		erro=1;
	}
	
	s = fopen("arq.html","w");
	
	if((fopen("arq.html","w"))==NULL){
		printf("Não foi possível abrir o arquivo!");
		erro=2;
	}
	
	exclui_tags();
	
	fclose(e);
	fclose(s); 
	return 0;
}

void exclui_tags(){
 	char string;
  	string StripTagsRegex (string text){
    return Regex.Replace(text, "<(.|\n)*?>", string.Empty);
	}
}

