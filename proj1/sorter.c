//Arthkumar Desai
//Benjamin weiss


#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>
#include "sorter.h"


#define MAX_PIDS 257
volatile pid_t *pids;
//volatile pid_t *c;
int x;
int checkHeader(char* rootDirPath) ;

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
int sort(char* fileName,char* path,char*columnName)
{ 
	
	//printf("path sorter.c %s\n",path);
	//printf("fileName sorter.c %s\n",fileName);
	
	
	
	int name_length = strlen(fileName);

    /**it CANNOT have .csv file**/
    if (name_length < 4){

        return -1;

    }
    char* format=(char*)malloc(sizeof(char)*100);
    format[0] = '\0';
    int count= 0 ;


    int start_index=0;   
		for(count=0;count<name_length-4;count++){
        format[count]  = fileName[start_index];
        start_index++;       
    }
    format[count] = '\0';    
 strcat(format,"-sorted-");  
 strcat(format,columnName); 
 strcat(format,".csv"); 
 
 
	
	
    
   // char* createFile=NULL;
   
	//FILE* output_File= fopen(format,"w");
	
	//printf("printing format %s\n",format);
	
	int line=0;
	int i=1;
	int freeCounter;
	//FILE* fp=fopen(in,"r");
	
	char* tok=(char*)malloc(sizeof(char)*10000);
	char* str1=(char*)malloc(sizeof(char)*100000);
	
	
	
	 movie *data=(movie*)malloc((17999)*(sizeof(movie)));
	 	char* str=(char*)malloc(sizeof(char)*100000);
	
	
//char header[] = "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes";
/********************************HEADER CHECKED*******************************************/
	FILE* fp=fopen(path,"r");
	if(fp==NULL)
	{
		printf("error opening file\n");
		exit(0);
	}

	fgets(str1,10000,fp);
	
	//if(strcmp(str1,header)!=0)
	//if(strstr(str1, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes") != NULL) 

	//{
		
	//	printf("Header is different\n");
		//fclose(fp);
		//exit(0);
	//}

	
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

	if((strcmp(columnName,"color")==0)){
	cases=1;MergeSort(data,1,i-1,cases,format);
	
	}
		else if(strcmp(columnName,"director_name")==0){cases=2;MergeSort(data,1,i-1,cases,format);}
		
	else if(strcmp(columnName,"actor_2_name")==0){cases=4;MergeSort(data,1,i-1,cases,format);}	 
	else if(strcmp(columnName,"genres")==0){cases=5;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"actor_1_name")==0){cases=6;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"movie_title")==0){cases=7;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"actor_3_name")==0){cases=8;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"plot_keywords")==0){cases=9;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"movie_imdb_link")==0){cases=10;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"language")==0){cases=11;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"country")==0){cases=12;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"content_rating")==0){cases=13;MergeSort(data,1,i-1,cases,format);}
	
	
	else if(strcmp(columnName,"num_critic_for_reviews")==0){cases=14;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"duration")==0){cases=15;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"director_facebook_likes")==0){cases=16;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"actor_3_facebook_likes")==0){cases=17;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"actor_1_facebook_likes")==0){cases=18;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"gross")==0){cases=19;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"num_voted_users")==0){cases=20;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"cast_total_facebook_likes")==0){cases=21;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"facenumber_in_poster")==0){cases=22;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"num_user_for_reviews")==0){cases=23;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"budget")==0){cases=24;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"title_year")==0){cases=25;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"actor_2_facebook_likes")==0){cases=26;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"imdb_score")==0){cases=27;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"aspect_ratio")==0){cases=28;MergeSort(data,1,i-1,cases,format);}
	else if(strcmp(columnName,"movie_facebook_likes")==0){cases=29;MergeSort(data,1,i-1,cases,format);}
	else
	{
		printf("Use the same fields from .csv file\n");
		printf("Invalid Field\n Run the program again with correct field \n");
		abort();
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
free(format);

return 0;
}





/**********************************************************************************************************************************/
bool isCsv(char* file)
{
	size_t x=strlen(file);
	return x>4 && strcmp(file+x-4,".csv")==0;
}







static void list_dir (const char * dir_name,char* column)
{
	//pid_t id;
//int z;
    DIR * d;
    d = opendir (dir_name);
  char* sortBy=(char*)malloc(sizeof(char)*100);
  strcpy(sortBy,column);
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
  
    while (1) {
        struct dirent * entry;
        const char * d_name;
        //Check rest files in same dir
        entry = readdir (d);
        if (! entry) {            
            break;}
            
        d_name = entry->d_name;
        /* Print the name of the file and directory. */
        
        

		 char path[PATH_MAX]; 

        if (entry->d_type == DT_DIR && strcmp (d_name, "..") != 0 &&  strcmp (d_name, ".") != 0) {
	//	printf("PARENT IN DIR \n");
           
		fflush(stdout);
		pid_t x=fork();
		if(x>0){
		
			pids[MAX_PIDS-2]++;
	
		 continue; 
		}else if(x<0){
		 exit (EXIT_FAILURE);		
		}	
		
		printf("%d,",(int)getpid());
                int path_length;
               
                path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);              
                
                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                
                	//printf("PATH : %s\n",path);
                list_dir (path,sortBy);
               exit(0);
            	
	}
	else
	{ 
	if(entry->d_type == DT_REG && isCsv(entry->d_name) && strstr(entry->d_name, "-sorted-")  == NULL )
	{
		//printf("path %s\n",path);
		//if(checkHeader(path,entry->d_name) == -1){
			//printf("not match\n");
			//}
			//else{
		fflush(stdout);
		pid_t x=fork();
		if(x>0){			
		
			pids[MAX_PIDS-2]++;
	
		 continue; 
		}else if(x<0){
		 exit (EXIT_FAILURE);		
		}	
		//printf("PARENT IN REG \n");
		printf("%d,",(int)getpid());
		 int path_length;
               
                path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);              
                
                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                //printf("CHILD ++ CSV_FILE: %s\nThe Path is: %s\n\n", entry->d_name,path);
			
			//printf("I am child\n");
			//printf("path of csv file %s = %s \n",entry->d_name,path);
			if(checkHeader(path) == -1){
				printf("\nPID OF INVALID CSV FILE HEADER: \n");
				 exit(0);
				 
				 }else{
			sort(entry->d_name,path,sortBy);
			exit(0);
			  
		  }
		}
	
	
	//}
}
    }//While
    int count=0;
pid_t track=0;
x=(((int)getpid())-(int)pids[MAX_PIDS-1]);
pids[x]=getpid();
   do{

	track=wait(&count);
}while(track>0); 
   
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
//x=(((int)getpid())-(int)pids[MAX_PIDS-1]);
	if(getpid()!=pids[MAX_PIDS-1]){
		exit(0);
	}
	//return z;
}
int checkHeader(char* path) {
    int result = -1;
   
    char *fileLines = (char*)malloc(strlen(path)+1500); 
    if( fileLines == NULL){
      printf("Allocate Not memory.");
      abort();
    }
  
    FILE* fp = fopen(path, "r+");
    int skip = 0;
     if(fp) {
      while (fgets(fileLines, 1500, fp) != NULL) {
        if(skip == 0){
            if(strstr(fileLines, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes") != NULL) {
              result = 0;
              skip = 1;
              break;
            } else {
              result = -1;
              skip = 1;
              break;
            }
        }
      } 
    } else {
      result =  -1;
    }
    fclose(fp);
    return result;
}

int main (int argc, char**argv){
	//MAX_PIDS is 256 as the pid in the array is for variable that is used to track size.
		if(argc>3||argc<3){
		printf("INCORRECT INPUT\n");
		exit (EXIT_FAILURE);
		} 
		char* tempS = argv[2];
		
	if(strcmp("color", tempS) == 0 || strcmp("director_name", tempS) == 0  || strcmp("num_critic_for_reviews", tempS)==0 || strcmp("duration", argv[2]) == 0  
	|| strcmp("director_facebook_likes", argv[2]) == 0 || strcmp("actor_1_facebook_likes", argv[2]) == 0 || strcmp("actor_3_facebook_likes", argv[2]) == 0 
	|| strcmp("gross", argv[2]) == 0 || strcmp("num_voted_users", argv[2]) == 0 || strcmp("cast_total_facebook_likes", argv[2]) == 0 || strcmp("facenumber_in_poster", argv[2]) == 0 
	|| strcmp("num_user_for_reviews", argv[2]) == 0 ||  strcmp("budget", argv[2]) == 0 ||  strcmp("title_year", argv[2]) == 0 
	|| strcmp("actor_2_facebook_likes", argv[2]) == 0 || strcmp("imdb_score", argv[2]) == 0 || strcmp("aspect_ratio", argv[2]) == 0 || strcmp("movie_facebook_likes", argv[2]) == 0
	|| strcmp("actor_2_name", argv[2]) == 0 || strcmp("genres", argv[2]) == 0 || strcmp("actor_1_name", argv[2]) == 0 || strcmp("movie_title", argv[2]) == 0 
	|| strcmp("actor_3_name", argv[2]) == 0  || strcmp("plot_keywords", argv[2]) == 0 || strcmp("movie_imdb_link", argv[2]) == 0  ||  strcmp("language", argv[2]) == 0
	|| strcmp("country", argv[2]) == 0 || strcmp("content_rating", argv[2]) == 0){
			
			pids=mmap(0,MAX_PIDS*sizeof(pid_t),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
		if(!pids){
			exit (EXIT_FAILURE);
		}	
		memset((void*)pids,0,MAX_PIDS*sizeof(pid_t));
		pids[MAX_PIDS-1]=getpid();
		printf("Initial PID: %d\nPIDS of all child processes: ",(int)pids[MAX_PIDS-1]);
//printf("\nChildren: ");
//printf("%s","");
		pids[MAX_PIDS-2]++;
		x=(int)getpid();
		//pids[(pids[MAX_PIDS-1]-getpid())]=getpid();
		
	char* columnName=(char*)malloc(sizeof(char)*120);;
	strcpy(columnName,argv[2]);
	//printf("column name %s\n",columnName);
 list_dir (".",columnName);


printf("\nTotal number of processes: %d\n",(int)pids[MAX_PIDS-2]);
free(columnName);
  }
  else{
	  printf("Use the Same columnName from CSV file\n");
	  abort();
  }    
   	   
    return 0;
}
