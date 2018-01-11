//Florian Malaj
//Arthkumar Desai
//cs214 proj0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorter.h"


  

char* my_strtok(char*str,const char*delim,char** store)
	{
		char*p,*wk;
		if(str!=NULL)
		{
			*store=str;
		}
		if(*store==NULL) return NULL;
		if(**store =='\0') return NULL;
		p=strpbrk(wk=*store,delim);
		if(p!=NULL)
		{
			*p='\0';
			*store=p+1;
		}
		else 
		{
			*store =NULL;
		}
		return wk;
	}
	
char* strtk(char*str,const char*delim)
{
	char* p;
	return my_strtok(str,delim,&p);
}
int main(int argc,char**argv)
{ 
	
	if(argc!=3)
	{
		printf("Not Enough Arguments\n");
		EXIT_FAILURE;
	}
	if(strcmp(argv[1],"-c")!=0)
	{
		printf("-c is missing\n");
		EXIT_FAILURE;
	}
	int line=0;
	int i=1;
	int freeCounter;
	FILE* fp;
	fp=stdin;
	char* tok;
	char* str1=(char*)malloc(sizeof(char)*100000);
	

	
	 movie *data=(movie*)malloc((17999)*(sizeof(movie)));
	 	char* str=(char*)malloc(sizeof(char)*100000);
	
	
	

	

fgets(str1,10000,fp);
	
	while(fgets(str,10000,fp))
	{
				//color
		if(str[0]=='"')
		{
			tok=strtok(str,"\"");
			data[i].color=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].color,tok);
			 tok=str+2+(strlen(tok)+1);
			 	//printf("coloe %s %d \n",tok,i);
			//printf("with quotatoin mark %s %d\n",data[i].color,i);
		}
		else
		{
			tok=strtk(str,",");
			data[i].color=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].color,tok);
			  tok=str+(strlen(tok)+1);
		//	printf("%s %d \n",data[i].color,i);
		}
			//printf("%s %d \n",tok,i);
		//tok=strtk(tok,",");
					
					//dirName
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].dirName=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].dirName,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].dirName=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].dirName,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
					//Review
	//printf(" cc %s %d \n",tok,i);
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].review=atoi(tok);
			//printf("with %d\n",data[i].review);
		tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	}
	else
	{
		tok=strtk(tok,",");
		data[i].review=atoi(tok);
		//	printf("without %d\n",data[i].review);
		//data[i].review==atoi(tok);
	    tok=tok+(strlen(tok)+1);
		//printf("%s %d \n",tok,i);
	}
	
	
			//duration
			
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].duration=atof(tok);
		tok=tok+1+(strlen(tok)+1);
		printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].duration=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	}
	
				//dir_likes
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].dir_likes=atof(tok);
		tok=tok+1+(strlen(tok)+1);
		printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].dir_likes=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	}
	
			//actor3_likes
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].actor3_likes=atof(tok);
		tok=tok+1+(strlen(tok)+1);
		printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].actor3_likes=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	}
	
			//actor2_name
			
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].actor2_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor2_name,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].actor2_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor2_name,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//actor1_likes
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].actor1_likes=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].actor1_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//gross
			
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].gross=atof(tok);
		tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].gross=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	}
	
			//genres
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].genres=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].genres,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].genres=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].genres,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//actor1_name
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].actor1_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor1_name,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].actor1_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor1_name,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//movieTitle
		
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].movieTitle=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].movieTitle,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].movieTitle=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].movieTitle,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//voted_user
			
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].voted_users=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].voted_users=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//cast_total_fb_likes
			
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].cast_total_fb_likes=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].cast_total_fb_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//actor3_name
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].actor3_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor3_name,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].actor3_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor3_name,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//poster_faces
			
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].poster_faces=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].poster_faces=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
		
			//plot
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].plot=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].plot,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].plot=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].plot,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
	
			//imdb_link
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].imdb_link=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].imdb_link,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].imdb_link=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].imdb_link,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
	
			//num_user_for_reviews
			
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].num_user_for_reviews=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].num_user_for_reviews=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//lang
			
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].lang=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].lang,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].lang=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].lang,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//country
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].country=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].country,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].country=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].country,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
	
			//content_rating
	
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
			data[i].content_rating=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].content_rating,tok);
			 tok=tok+1+(strlen(tok)+1);
		//printf("wi th  quotes = %s %d \n",tok,i);
	
	}
	else
	{
		tok=strtk(tok,",");
			data[i].content_rating=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].content_rating,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	}
		
			//budget
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].budget=atof(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].budget=atof(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//title_year
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].title_year=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].title_year=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//actor2_fb_likes
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].actor2_fb_likes=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].actor2_fb_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//imdb_score
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].imdb_score=atof(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].imdb_score=atof(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//aspect_ratio
	
	if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].aspect_ratio=atof(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].aspect_ratio=atof(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	
			//movie_facebook_likes
		if(tok[0]=='"'){
		tok=strtok(tok,"\"");
		data[i].movie_facebook_likes=atoi(tok);
		//printf("wi th  quotes = %s %d \n",tok,i);
		  tok=tok+(strlen(tok)+1);
	
	}
	else
	{
		tok=strtk(tok,",");
		data[i].movie_facebook_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	}
	//printf("%d %d \n",	data[i].actor1_likes,i);
		i++;
}

int cases;

	if((strcmp(argv[2],"color")==0)){
	cases=1;MergeSort(data,1,i-1,cases);
	
	}
		else if(strcmp(argv[2],"director_name")==0){cases=2;MergeSort(data,1,i-1,cases);}
		
	else if(strcmp(argv[2],"actor_2_name")==0){cases=4;MergeSort(data,1,i-1,cases);}	 
	else if(strcmp(argv[2],"genres")==0){cases=5;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"actor_1_name")==0){cases=6;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"movie_title")==0){cases=7;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"actor_3_name")==0){cases=8;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"plot_keywords")==0){cases=9;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"movie_imdb_link")==0){cases=10;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"language")==0){cases=11;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"country")==0){cases=12;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"content_rating")==0){cases=13;MergeSort(data,1,i-1,cases);}
	
	
	else if(strcmp(argv[2],"num_critic_for_reviews")==0){cases=14;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"duration")==0){cases=15;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"director_facebook_likes")==0){cases=16;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"actor_3_facebook_likes")==0){cases=17;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"actor_1_facebook_likes")==0){cases=18;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"gross")==0){cases=19;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"num_voted_users")==0){cases=20;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"cast_total_facebook_likes")==0){cases=21;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"facenumber_in_poster")==0){cases=22;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"num_user_for_reviews")==0){cases=23;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"budget")==0){cases=24;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"title_year")==0){cases=25;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"actor_2_facebook_likes")==0){cases=26;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"imdb_score")==0){cases=27;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"aspect_ratio")==0){cases=28;MergeSort(data,1,i-1,cases);}
	else if(strcmp(argv[2],"movie_facebook_likes")==0){cases=29;MergeSort(data,1,i-1,cases);}
	else
	{
		printf("Use the same fields from .csv file\n");
		printf("Invalid Field\n");
		EXIT_FAILURE;
	}
	
	




	//Free Function
for(freeCounter=0;freeCounter<=line;freeCounter++)
{	
	free(data[freeCounter].color);
	free(data[freeCounter].dirName);    
	  free(data[freeCounter].actor2_name); 
	          free(data[freeCounter].genres);
	           free(data[freeCounter].actor1_name);
	            free(data[freeCounter].movieTitle);	          
	               free(data[freeCounter].actor3_name);	               
	                 free(data[freeCounter].plot);
	                  free(data[freeCounter].imdb_link);	               
	                   free(data[freeCounter].lang);
	                   free(data[freeCounter].country);
	                  free(data[freeCounter].content_rating);
				  }           

free(data);
free(str);


return 0;
}
	
	
	
