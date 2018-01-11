//proj2.2_final

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdbool.h>
#include "sorter_thread.h"
#include <pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
typedef struct sdir{
	char dirPath[400];
	
}dirStruct;
//ALL GLOBAL
char* columnName;
int t_index= 0;
//files no need 
int ilimit=204800;

int totalCsv=0;

int total_num_of_movies=0;
int lines=0;
//global struct 
movie* global=NULL;
pthread_t* threads=NULL;
dirStruct* dir=NULL;


int sort(char* path);
int list_dir(char* dName);
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


void * csvFun(void* arg)
{
	dirStruct* incsvfun = (dirStruct*) arg;
	char incsv_path[400];
	strcpy(incsv_path,incsvfun->dirPath);
	//printf("INCSVFUN\n");
	sort(incsv_path);
	pthread_exit(NULL);
}


void* dirFun(void* arg)
{
//printf("I am in dirFun\n");
dirStruct* indirfun = (dirStruct*) arg;
	char indir_path[400];
	strcpy(indir_path,indirfun->dirPath);
	//printf("I am in dirFun. copied %s \n",indir_path);
	list_dir(indir_path);
pthread_exit(NULL);	
}
bool isCsv(char* file)
{
	size_t x=strlen(file);
	return x>4 && strcmp(file+x-4,".csv")==0;
}
int sort(char* path)
{ 
	
	//int line=0;
	int i=0;
	
     int temp_total_num_of_movies=1;
     
		char* str1=(char*)malloc(sizeof(char)*1000);
		 movie *data=(movie*)malloc((10000)*(sizeof(movie)));
		char* str=(char*)malloc(sizeof(char)*10000);
     //int temp_total_num_of_movies=0;
	 
	 
	 char* tok=(char*)malloc(sizeof(char)*100);
	 FILE* fp = fopen(path, "r");
	  if(fp == NULL)
	 {
		 printf("file fail %d\n",errno);
	 }
	 //Header
	 fgets(str1,10000,fp);
	
	while(fgets(str,10000,fp))
	{
		
			tok=strtk(str,",");
			data[i].color=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].color,tok);
			  tok=str+(strlen(tok)+1);
			  
			  
			  //dirName
		
		tok=strtk(tok,",");
			data[i].dirName=(char*)malloc(sizeof(char)*(strlen(tok)+1));
			 strcpy(data[i].dirName,tok);
			  tok=tok+(strlen(tok)+1);
			  
			  
			  
					//Review
	//printf(" cc %s %d \n",tok,i);
		
		tok=strtk(tok,",");
		data[i].review=atoi(tok);
		//	printf("without %d\n",data[i].review);
		//data[i].review==atoi(tok);
	    tok=tok+(strlen(tok)+1);
		//printf("%s %d \n",tok,i);
	
	
	
			//duration
			
	
		tok=strtk(tok,",");
		data[i].duration=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	
	
				//dir_likes
	
	
		tok=strtk(tok,",");
		data[i].dir_likes=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	
	
			//actor3_likes
	
	
		tok=strtk(tok,",");
		data[i].actor3_likes=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	
	
			//actor2_name
			
		
		tok=strtk(tok,",");
			data[i].actor2_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor2_name,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
	
		tok=strtk(tok,",");
		data[i].actor1_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//gross
			
		
		tok=strtk(tok,",");
		data[i].gross=atof(tok);
	    tok=tok+(strlen(tok)+1);
	//	printf("%s %.f \n",tok,i);
	
	
			//genres
		
		tok=strtk(tok,",");
			data[i].genres=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].genres,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
			//actor1_name
	
		tok=strtk(tok,",");
			data[i].actor1_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor1_name,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
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
			
	
		tok=strtk(tok,",");
		data[i].voted_users=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//cast_total_fb_likes
			
		
		tok=strtk(tok,",");
		data[i].cast_total_fb_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//actor3_name
	
	
		tok=strtk(tok,",");
			data[i].actor3_name=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].actor3_name,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	

			//poster_faces
		
		tok=strtk(tok,",");
		data[i].poster_faces=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
		
			//plot
	
	
		tok=strtk(tok,",");
			data[i].plot=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].plot,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
	
			//imdb_link
	
		tok=strtk(tok,",");
			data[i].imdb_link=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].imdb_link,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
	
			//num_user_for_reviews
			
		
		tok=strtk(tok,",");
		data[i].num_user_for_reviews=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//lang
	
		tok=strtk(tok,",");
			data[i].lang=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].lang,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
			//country
		
		tok=strtk(tok,",");
			data[i].country=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].country,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
	
			//content_rating
	
		
		tok=strtk(tok,",");
			data[i].content_rating=(char*)malloc(sizeof(char*)*(strlen(tok)+1));
			 strcpy(data[i].content_rating,tok);
			  tok=tok+(strlen(tok)+1);
			  	//printf("%s %d \n",tok,i);
	
		
			//budget
		
		tok=strtk(tok,",");
		data[i].budget=atof(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//title_year
	
	
		tok=strtk(tok,",");
		data[i].title_year=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//actor2_fb_likes
	
	
		tok=strtk(tok,",");
		data[i].actor2_fb_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
	
		tok=strtk(tok,",");
		data[i].imdb_score=atof(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	

			//aspect_ratio
	
		tok=strtk(tok,",");
		data[i].aspect_ratio=atof(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
	
			//movie_facebook_likes
		
		tok=strtk(tok,",");
		data[i].movie_facebook_likes=atoi(tok);
		//printf("%d %d \n",	data[i].actor1_likes,i);
		  tok=tok+(strlen(tok)+1);
	
			  
			  
			  
			  
			  
			  
			  
			  
	i++;
	temp_total_num_of_movies +=1;
	lines++;
		//fgets(str1,10000,fp);	  
	}
	//printf("temp_total_num_of_movies %d\n",temp_total_num_of_movies);
	
 fclose(fp);
 
	pthread_mutex_lock(&lock);
	
	int p;
	for (p= 0; p < i ; p++){

		global[total_num_of_movies] = data[p];
		total_num_of_movies ++ ;


	}
	//free(str1);
	free(str);
	//free(tok);
	free(data);
	pthread_mutex_unlock(&lock);

    
 
 //printf("i = %d total_num_of_movies %d lines %d\n",i,total_num_of_movies,lines);
 
return 0;
}
void print(char* opendirr)
{

	//FILE* output_file=fopen(opendirr,"w");
	//strcat(opendirr,"/");
	//printf("in printing %s \n",opendirr);
	//printf("in print %s\n",format);
	//strcat(opendirr,"/");
	//printf("in printing %s \n",opendirr);
	//strcat(opendirr,format);
	//printf("in printing %s \n",opendirr);
	//printf("%d",total_num_of_movies);
//DIR* dp = opendir(opendirr);
	FILE* output_file=fopen(opendirr,"w");
	
	
    	fprintf(output_file,"color,");
        fprintf(output_file,"director_name,");
        fprintf(output_file,"num_critic_for_reviews,");
        fprintf(output_file,"duration,");
        fprintf(output_file,"director_facebook_likes,");
        fprintf(output_file,"actor_3_facebook_likes,");
        fprintf(output_file,"actor_2_name,");
        fprintf(output_file,"actor_1_facebook_likes,");
        fprintf(output_file,"gross,");
        fprintf(output_file,"genres,");
        fprintf(output_file,"actor_1_name,");
        fprintf(output_file,"movieTitle,");
        fprintf(output_file,"voted_users,");
        fprintf(output_file,"cast_total_fb_likes,");
        fprintf(output_file,"actor3_name,");      
        fprintf(output_file,"poster_faces,");
         fprintf(output_file,"plot_keywords,");
        fprintf(output_file,"imdb_link,");
        fprintf(output_file,"num_user_for_reviews,");
        fprintf(output_file,"language,");
        fprintf(output_file,"country,");
        fprintf(output_file,"content_rating,");
        fprintf(output_file,"budget,");
        fprintf(output_file,"title_year,");
        fprintf(output_file,"actor2_fb_likes,");
        fprintf(output_file,"imdb_score,");
        fprintf(output_file,"aspect_ratio,");
        fprintf(output_file,"movie_facebook_likes\n");
    
	int i;
	//print out first line of headers that is all
	for ( i = 0; i <total_num_of_movies; i++){
		
		
        fprintf(output_file,"%s,",global[i].color);
        fprintf(output_file,"%s,",global[i].dirName);
        fprintf(output_file,"%d,",global[i].review);
        fprintf(output_file,"%.f,",global[i].duration);
        fprintf(output_file,"%d,",global[i].dir_likes);
        fprintf(output_file,"%d,",global[i].actor3_likes);
        fprintf(output_file,"%s,",global[i].actor2_name);
        fprintf(output_file,"%d,",global[i].actor1_likes);
        fprintf(output_file,"%.f,",global[i].gross);
       fprintf(output_file,"%s,",global[i].genres);
        fprintf(output_file,"%s,",global[i].actor1_name);
int z=0;
for(z=0;z<strlen(global[i].movieTitle);z++){
		if(global[i].movieTitle[z]==','){
		fprintf(output_file,"\"%s\",",global[i].movieTitle);
		break;
		}
	}
	if(z==strlen(global[i].movieTitle)){
        fprintf(output_file,"%s,",global[i].movieTitle);
	}
        fprintf(output_file,"%d,",global[i].voted_users);
        fprintf(output_file,"%d,",global[i].cast_total_fb_likes);
        fprintf(output_file,"%s,",global[i].actor3_name);
        fprintf(output_file,"%d,",global[i].poster_faces);
        fprintf(output_file,"%s,",global[i].plot);
        fprintf(output_file,"%s,",global[i].imdb_link);
        fprintf(output_file,"%d,",global[i].num_user_for_reviews);
        fprintf(output_file,"%s,",global[i].lang);
        fprintf(output_file,"%s,",global[i].country);
        fprintf(output_file,"%s,",global[i].content_rating);
        fprintf(output_file,"%.f,",global[i].budget);
        fprintf(output_file,"%d,",global[i].title_year);
        fprintf(output_file,"%d,",global[i].actor2_fb_likes);
       fprintf(output_file,"%.1f,",global[i].imdb_score);
        fprintf(output_file,"%.1f,",global[i].aspect_ratio);
        fprintf(output_file,"%d\n",global[i].movie_facebook_likes);
    }
    
    fclose(output_file);
    //closedir(dp);
    

}

int list_dir(char* dName)
{
	char path[1048];
	DIR *director;
    director = opendir(dName);
   struct dirent* entry;
   while((entry = readdir(director)) != NULL)
   {
	   if (entry->d_type == DT_DIR && strcmp (entry->d_name, "..") != 0 &&  strcmp (entry->d_name, ".") != 0)
	   {
		    snprintf (path, PATH_MAX, "%s/%s", dName, entry->d_name); 
		  // printf("I am in list_dir : path = %s\n",path);
		   dirStruct dst;
		   strcpy(dst.dirPath,path);
		   //REALLOC IS THE PROBLEM HERE
		   
		   pthread_mutex_lock(&lock);
		   dir[t_index]=dst;
		   pthread_create(&threads[t_index],NULL,dirFun,&dir[t_index]);
		   t_index++;
		   pthread_mutex_unlock(&lock);
	    }
	    else 
	    {
			if(entry->d_type == DT_REG && isCsv(entry->d_name))
			{
				//printf("CSV FILES %s\n",entry->d_name);
				snprintf (path, PATH_MAX, "%s/%s", dName, entry->d_name);
				//printf("CSV FILES %s\n",path);
												//PRINTS CSV PATH AND FILE NAME TILL HERE
				 dirStruct dst;
				 strcpy(dst.dirPath,path);
				 pthread_mutex_lock(&lock);
		   dir[t_index]=dst;
		   pthread_create(&threads[t_index],NULL,csvFun,&dir[t_index]);
		   t_index++;
		   totalCsv++;
		   pthread_mutex_unlock(&lock);
				 
			}
		}
   }
   closedir(director);
    return 1;
}

int main(int argc,char** argv)
{
	char* thisDir=malloc(sizeof(char)*1048);
	char thatDir[1048];
	if(argc!=7&&argc!=5&&argc!=3){
	printf("error incorrect parameters\n");
	exit(0);
	}
	if (argc>=7){



        if(strcasecmp(argv[3], "-d") ==0 ){

        strcpy(thisDir, argv[4]);
        }
        else if(strcasecmp(argv[1], "-d") ==0 ){

        strcpy(thisDir, argv[2]);
        }else if(strcasecmp(argv[5], "-d") ==0 ){

        strcpy(thisDir, argv[6]);
        }
        else{

            printf("WRONG PARAMETERS\n");
            exit(0);
        }




        if(strcasecmp(argv[5], "-o") ==0 ){

            strcpy(thatDir,argv[6]);
        }else if(strcasecmp(argv[1], "-o") ==0 ){

            strcpy(thatDir,argv[2]);
        }else if(strcasecmp(argv[3], "-o") ==0 ){

            strcpy(thatDir,argv[4]);
        }
	else{

            printf("WRONG PARAMETERS\n");
            exit(0);
        }


	}
	else if (argc>=5){



        if(strcasecmp(argv[3], "-d") ==0 ){

        strcpy(thisDir, argv[4]);
        strcpy(thatDir, "NONE");
        }
        else if(strcasecmp(argv[1], "-d") ==0 ){

        strcpy(thisDir, argv[2]);
        strcpy(thatDir, "NONE");
        }



        else if(strcasecmp(argv[3], "-o") ==0 ){

            strcpy(thatDir, argv[4]);
            getcwd(thisDir,1048);
        }else if(strcasecmp(argv[1], "-o") ==0 ){

            strcpy(thatDir, argv[2]);
            getcwd(thisDir,1048);
        }

        else{

            printf("WRONG PARAMETERS\n");
            exit(0);
        }


	}

	else{

        getcwd(thisDir,1048);
        strcpy(thatDir, "NONE");

	}

	if(strcmp(argv[1],"-h")==0)
	{
		printf(" ./sorter -c <columnName>\n");
		
	}
	/*if(strcmp(argv[1],"-c")!=0)
	{
		printf(" -c is missing\n");
		printf("Invalid Input. Type './sorter -h' for help'\n");
		exit(0);
		
	}*/
	DIR* dp = opendir(thatDir);
	if (!dp && strcmp(thatDir,"NONE")!=0){

		printf("OUTPUT FILE IS NOT CORRECT\n");
		exit(0);

	}
	int d=0;
	char* columnName =(char*)malloc(sizeof(columnName)*10);
	if(strcasecmp(argv[1], "-c") ==0 ){
		strcpy(columnName,argv[2]);
	d=2;
	}else if(strcasecmp(argv[3], "-c") ==0 ){
		strcpy(columnName,argv[4]);
	d=4;
	}else if(strcasecmp(argv[5], "-c") ==0 ){
		strcpy(columnName,argv[6]);
	d=6;
	}else{
		printf(" -c is missing\n");
		printf("Invalid Input. Type './sorter -h' for help'\n");
		exit(0);
	}
	
	if(strcmp("color", argv[d]) == 0 || strcmp("director_name", argv[d]) == 0  || strcmp("num_critic_for_reviews", argv[d])==0 || strcmp("duration", argv[d]) == 0  
	|| strcmp("director_facebook_likes", argv[d]) == 0 || strcmp("actor_1_facebook_likes", argv[d]) == 0 || strcmp("actor_3_facebook_likes", argv[d]) == 0 
	|| strcmp("gross", argv[d]) == 0 || strcmp("num_voted_users", argv[d]) == 0 || strcmp("cast_total_facebook_likes", argv[d]) == 0 || strcmp("facenumber_in_poster", argv[d]) == 0 
	|| strcmp("num_user_for_reviews", argv[d]) == 0 ||  strcmp("budget", argv[d]) == 0 ||  strcmp("title_year", argv[d]) == 0 
	|| strcmp("actor_2_facebook_likes", argv[d]) == 0 || strcmp("imdb_score", argv[d]) == 0 || strcmp("aspect_ratio", argv[d]) == 0 || strcmp("movie_facebook_likes", argv[d]) == 0
	|| strcmp("actor_2_name", argv[d]) == 0 || strcmp("genres", argv[d]) == 0 || strcmp("actor_1_name", argv[d]) == 0 || strcmp("movie_title", argv[d]) == 0 
	|| strcmp("actor_3_name", argv[d]) == 0  || strcmp("plot_keywords", argv[d]) == 0 || strcmp("movie_imdb_link", argv[d]) == 0  ||  strcmp("language", argv[d]) == 0
	|| strcmp("country", argv[d]) == 0 || strcmp("content_rating", argv[d]) == 0){
	
	global=(movie*)malloc(sizeof(movie)*(1224*7000));
	threads = (pthread_t *)malloc(sizeof(pthread_t)*ilimit);
	dir = (dirStruct* ) malloc (sizeof(dirStruct)*ilimit);
	
	list_dir(thisDir);
	int tjoin;
	
	printf("Initial PID: %d\n",(int)getpid());
	printf("TIDS of all child threads:");
	for(tjoin = 0; tjoin<t_index; tjoin++)
	{
		printf("%u,",(int)threads[tjoin]);
		pthread_join(threads[tjoin],NULL);
	}
	//test
	//printf("global %s\n",global[71].movieTitle);
	
	//FORMAT OF OUTPUT FILE

   char* format=(char*)malloc(sizeof(char)*100);
    format[0] = '\0';
    int count= 0 ;
char* name = "AllFile.csv";
int name_length = strlen(name);
    int start_index=0;   
		for(count=0;count<name_length-4;count++){
        format[count]  = name[start_index];
        start_index++;       
    }
    format[count] = '\0';    
 strcat(format,"-sorted-");  
 strcat(format,columnName); 
 strcat(format,".csv"); 
 //printf("%s\n",format);
 
 
 /*COLUMN TO BE SORTED */
 int cases;

	if((strcmp(argv[d],"color")==0)){
	cases=1;MergeSort(global,0,lines-1,cases);
	
	}
		else if(strcmp(argv[d],"director_name")==0){cases=2;MergeSort(global,0,lines-1,cases);}
		
	else if(strcmp(argv[d],"actor_2_name")==0){cases=4;MergeSort(global,0,lines-1,cases);}	 
	else if(strcmp(argv[d],"genres")==0){cases=5;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"actor_1_name")==0){cases=6;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"movie_title")==0){cases=7;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"actor_3_name")==0){cases=8;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"plot_keywords")==0){cases=9;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"movie_imdb_link")==0){cases=10;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"language")==0){cases=11;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"country")==0){cases=12;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"content_rating")==0){cases=13;MergeSort(global,0,lines-1,cases);}
	
	
	else if(strcmp(argv[d],"num_critic_for_reviews")==0){cases=14;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"duration")==0){cases=15;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"director_facebook_likes")==0){cases=16;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"actor_3_facebook_likes")==0){cases=17;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"actor_1_facebook_likes")==0){cases=18;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"gross")==0){cases=19;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"num_voted_users")==0){cases=20;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"cast_total_facebook_likes")==0){cases=21;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"facenumber_in_poster")==0){cases=22;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"num_user_for_reviews")==0){cases=23;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"budget")==0){cases=24;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"title_year")==0){cases=25;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"actor_2_facebook_likes")==0){cases=26;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"imdb_score")==0){cases=27;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"aspect_ratio")==0){cases=28;MergeSort(global,0,lines-1,cases);}
	else if(strcmp(argv[d],"movie_facebook_likes")==0){cases=29;MergeSort(global,0,lines-1,cases);}
	else
	{
		//printf("Use the same fields from .csv file\n");
		//printf("Invalid Field\n Run the program again with correct field \n");
		//abort();
	}
	
	
	if(strcmp(thatDir,"NONE") != 0)
	{
		strcat(thatDir,"/");
	//printf("in printing %s \n",thatDir);
	strcat(thatDir,format);
	
	//this is important
	print(thatDir);
	}
	else 
	{
		print(format);
	}
	
	
	printf("\nTotal number of threads: %d",t_index+1);
	printf("\n");
	free(thisDir);
	free(format);
	free(global);
}
else
{
	printf("Column name is invalid\n type '<-h> for help'\n");
	exit(0);
}
	return 0;
}
