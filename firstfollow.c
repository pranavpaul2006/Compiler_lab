#include<stdio.h>
#include<string.h>
#include<ctype.h>

char p[10][10];
int n;
char infirst[128];
char infollow[128];

void first(char c , char s[]){
	int i,j,k;
	if(!isupper((unsigned char)c)){
		if(!strchr(s,c)){
			strncat(s,&c,1);
		}
		return;
	}
	
	if(infirst[(int)c])
		return;
	infirst[(int)c] =1;
	
	for(i = 0 ; i < n;i++){
		if(p[i][0] != c)
			continue;
		if(p[i][3] == '#'){
			if(!strchr(s,'#'))
				strcat(s,"#");
		}
		else{
			for(j=3;p[i][j];j++){
				char t[20] ="";
				first(p[i][j] , t);
				
				for(k = 0 ; t[k];k++){
					if(t[k] != '#' && !strchr(s,t[k]))
						strncat(s,&t[k] , 1);
				}
				if(!strchr(t , '#'))
					break;
			}
			if(!p[i][j] && !strchr(s,'#'))
				strcat(s,"#");
		}
		
	}
	infirst[(int)c] = 0;
}


void follow(char c , char s[]){
	int i,j,k,m;
	if(infollow[(int) c])
		return;
	infollow[(int)c] = 1;
	
	if(c == p[0][0] && !strchr(s,'$'))
		strcat(s,"$");
	
	for(i = 0;i<n;i++){
		for(j=3; p[i][j] ; j++){
			if(p[i][j] != c)
				continue;
				
			int nullable = 1;
			for(m = j+1;p[i][m];m++){
				char t[20] = "";
				first(p[i][m] , t);
				
				for(k = 0 ; t[k];k++){
					if(t[k] !='#' && !strchr(s,t[k]))
						strncat(s,&t[k] , 1);
				}
				if(!strchr(t , '#')){
					nullable = 0;
					break;
				}
			}
			
			if(nullable && p[i][0] !=c){
				char u[20] = "";
				follow(p[i][0],u);
				for(k = 0 ; u[k];k++){
					if(!strchr(s,u[k]))
						strncat(s,&u[k],1);
				}
			}
			
		}
		
		
	}
	infollow[(int)c] = 0;
}

void print_set(char s[]){
	printf("{");
	for(int i=0;s[i] ; i++){
		if(i>0){
			printf(", ");
		}
		printf("%c",s[i]);
	}
	printf("}\n");
}

int main(){
	int i ;
	char nt[10] = "";
	
	printf("enter the no of productions");
	scanf("%d",&n);
	
	printf("enter productions :\n");
	for(i = 0;i<n;i++){
		scanf("%s",p[i]);
	}
	
	for(i = 0 ; i < n; i++){
		if(!strchr(nt,p[i][0]))
			strncat(nt,&p[i][0],1);
	}
	
	printf("\nfirst set:\n");
	for(i=0 ; nt[i];i++)
	{
		char s[20]="";
		first(nt[i] , s);
		printf("first(%c) = " , nt[i]);
		print_set(s);
		
	}
	for(i=0 ; nt[i];i++)
	{
		char s[20] ="";
		follow(nt[i] , s);
		printf("follow(%c) = " , nt[i]);
		print_set(s);
		
	}
}


Output


enter the no of productions5
enter productions :
S->ABC
A->a
B->b
B->#
C->c

first set:
first(S) = {a}
first(A) = {a}
first(B) = {b, #}
first(C) = {c}
follow(S) = {$}
follow(A) = {b, c}
follow(B) = {c}
follow(C) = {$}
