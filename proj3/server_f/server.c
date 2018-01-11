//final server#include <stdio.h>#include <arpa/inet.h>#include <stdlib.h>#include <fcntl.h>#include <unistd.h>#include <string.h>#include <sys/socket.h>#include <netinet/in.h>#include <pthread.h>#include "server.h"#include <assert.h>#include <sys/stat.h>#include <sys/sendfile.h>#define MAX_NUM_THREAD 10#define PORT 9000int status = 1; // for server running statusint num_of_thread = 0; // currently created num of threadsint server_sock, client_sock;pthread_mutex_t lockA = PTHREAD_MUTEX_INITIALIZER;//movie_struct * data ;//int curr_arr_size = 5000;//int elements_filled = 0;void mergeColumn (int cases);typedef struct tid_type{	pthread_t tid;	int isFree;	int socketfd;	char columnName[256];}tid_type;void gotoxy(int x,int y){ //printf("%c[%d;%df",0x1B,y,x);}/* Global thread id pool */tid_type tid_pool[MAX_NUM_THREAD];void Merge(movie_struct *arr, int low, int mid, int high,int cases,int lines);void MergeSort(movie_struct *arr, int low, int high,int Scases);void MergeSort(movie_struct *arr, int low, int high,int Scases){    if (low < high)    {        int mid = (low + high) / 2;        //printf("-->> %s: lo = %d, md = %d, hi = %d\n", __func__, low, mid, high);        MergeSort(arr, low, mid,Scases);        MergeSort(arr, mid + 1, high,Scases);        Merge(arr, low, mid, high,Scases,high);        //printf("<<-- %s: lo = %d, md = %d, hi = %d\n", __func__, low, mid, high);    }}void Merge(movie_struct *arr, int low, int mid, int high,int cases,int lines){    int mergedSize = high - low + 1;    movie_struct *temp = (movie_struct *)malloc(mergedSize * sizeof(movie_struct));    int mergePos = 0;    int leftPos = low;    int rightPos = mid + 1;    if(cases==1){while (leftPos <= mid && rightPos <= high){        if(strcasecmp (arr[leftPos].color,arr[rightPos].color)<0){            temp[mergePos++] = arr[leftPos++];}else{            temp[mergePos++] = arr[rightPos++];}}//else            }//While    if(cases==2){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].director_name,arr[rightPos].director_name)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While       if(cases==4){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].actor_2_name,arr[rightPos].actor_2_name)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While       if(cases==5){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].genres,arr[rightPos].genres)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While        if(cases==6){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].actor_1_name,arr[rightPos].actor_1_name)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While         if(cases==7){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].movie_title,arr[rightPos].movie_title)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While         if(cases==8){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].actor_3_name,arr[rightPos].actor_3_name)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While         if(cases==9){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].plot_keywords,arr[rightPos].plot_keywords)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While         if(cases==10){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].movie_imdb_link,arr[rightPos].movie_imdb_link)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While         if(cases==11){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].language,arr[rightPos].language)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While     if(cases==12){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].country,arr[rightPos].country)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While     if(cases==13){    while (leftPos <= mid && rightPos <= high)         {        if(strcasecmp (arr[leftPos].content_rating,arr[rightPos].content_rating)<0)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While     if(cases==14){    while (leftPos <= mid && rightPos <= high)         {        if(arr[leftPos].num_user_for_reviews < arr[rightPos].num_user_for_reviews)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While     }     if(cases==15){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].duration<arr[rightPos].duration)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While     }     if(cases==16){    while (leftPos <= mid && rightPos <= high)         {      if(arr[leftPos].director_facebook_likes<arr[rightPos].director_facebook_likes)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While     }     if(cases==17){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].actor_3_facebook_likes<arr[rightPos].actor_3_facebook_likes)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While     }     if(cases==18){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].actor_1_facebook_likes<arr[rightPos].actor_1_facebook_likes)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While     }     if(cases==19){    while (leftPos <= mid && rightPos <= high)         {       if(arr[leftPos].gross<arr[rightPos].gross)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While     }    if(cases==20){    while (leftPos <= mid && rightPos <= high)         {        if(arr[leftPos].num_voted_users<arr[rightPos].num_voted_users)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==21){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].cast_total_facebook_likes<arr[rightPos].cast_total_facebook_likes)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==22){    while (leftPos <= mid && rightPos <= high)         {        if(arr[leftPos].facenumber_in_poster<arr[rightPos].facenumber_in_poster)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==23){    while (leftPos <= mid && rightPos <= high)         {       if(arr[leftPos].num_user_for_reviews<arr[rightPos].num_user_for_reviews)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==24){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].budget<arr[rightPos].budget)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==25){    while (leftPos <= mid && rightPos <= high)         {       if(arr[leftPos].title_year<arr[rightPos].title_year)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++];} }//else    }//While        if(cases==26){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].actor_2_facebook_likes<arr[rightPos].actor_2_facebook_likes)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==27){    while (leftPos <= mid && rightPos <= high)         {        if(arr[leftPos].imdb_score<arr[rightPos].imdb_score)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==28){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].aspect_ratio<arr[rightPos].aspect_ratio)        { temp[mergePos++] = arr[leftPos++];}        else{temp[mergePos++] = arr[rightPos++]; }//else    }//While    }    if(cases==29){    while (leftPos <= mid && rightPos <= high)         {         if(arr[leftPos].movie_facebook_likes<arr[rightPos].movie_facebook_likes)        { temp[mergePos++] = arr[leftPos++];        }        else        {            temp[mergePos++] = arr[rightPos++];            }        //else    }    }//While    while (leftPos <= mid){        temp[mergePos++] = arr[leftPos++];}    while (rightPos <= high){        temp[mergePos++] = arr[rightPos++];}    assert(mergePos == mergedSize);    //Print("merged", mergedSize, temp);    for (mergePos = 0; mergePos < mergedSize; ++mergePos)        arr[low + mergePos] = temp[mergePos];    free(temp);            } void print(char* opendirr,int elements_filled,movie_struct* data){	//FILE* output_file=fopen(opendirr,"w");	//strcat(opendirr,"/");	//printf("in printing %s \n",opendirr);	//printf("in print %s\n",format);	//strcat(opendirr,"/");	//printf("in printing %s \n",opendirr);	//strcat(opendirr,format);	//printf("in printing %s \n",opendirr);	//printf("%d",total_num_of_movies);//DIR* dp = opendir(opendirr);	FILE* output_file=fopen("sorted.csv","w");		    	fprintf(output_file,"color,");        fprintf(output_file,"director_name,");        fprintf(output_file,"num_critic_for_reviews,");        fprintf(output_file,"duration,");        fprintf(output_file,"director_facebook_likes,");        fprintf(output_file,"actor_3_facebook_likes,");        fprintf(output_file,"actor_2_name,");        fprintf(output_file,"actor_1_facebook_likes,");        fprintf(output_file,"gross,");        fprintf(output_file,"genres,");        fprintf(output_file,"actor_1_name,");        fprintf(output_file,"movieTitle,");        fprintf(output_file,"voted_users,");        fprintf(output_file,"cast_total_fb_likes,");        fprintf(output_file,"actor3_name,");              fprintf(output_file,"poster_faces,");         fprintf(output_file,"plot_keywords,");        fprintf(output_file,"imdb_link,");        fprintf(output_file,"num_user_for_reviews,");        fprintf(output_file,"language,");        fprintf(output_file,"country,");        fprintf(output_file,"content_rating,");        fprintf(output_file,"budget,");        fprintf(output_file,"title_year,");        fprintf(output_file,"actor2_fb_likes,");        fprintf(output_file,"imdb_score,");        fprintf(output_file,"aspect_ratio,");        fprintf(output_file,"movie_facebook_likes\n");    	int i;	//print out first line of headers that is all	for ( i = 0; i <elements_filled; i++){				        fprintf(output_file,"%s,",data[i].color);        fprintf(output_file,"%s,",data[i].director_name);        fprintf(output_file,"%d,",data[i].num_critic_for_reviews);        fprintf(output_file,"%d,",data[i].duration);        fprintf(output_file,"%d,",data[i].director_facebook_likes);        fprintf(output_file,"%d,",data[i].actor_3_facebook_likes);        fprintf(output_file,"%s,",data[i].actor_2_name);        fprintf(output_file,"%d,",data[i].actor_1_facebook_likes);        fprintf(output_file,"%d,",data[i].gross);       fprintf(output_file,"%s,",data[i].genres);        fprintf(output_file,"%s,",data[i].actor_1_name);int z=0;for(z=0;z<strlen(data[i].movie_title);z++){		if(data[i].movie_title[z]==','){		fprintf(output_file,"\"%s\",",data[i].movie_title);		break;		}	}	if(z==strlen(data[i].movie_title)){        fprintf(output_file,"%s,",data[i].movie_title);	}        fprintf(output_file,"%d,",data[i].num_voted_users);        fprintf(output_file,"%d,",data[i].cast_total_facebook_likes);        fprintf(output_file,"%s,",data[i].actor_3_name);        fprintf(output_file,"%d,",data[i].facenumber_in_poster);        fprintf(output_file,"%s,",data[i].plot_keywords);        fprintf(output_file,"%s,",data[i].movie_imdb_link);        fprintf(output_file,"%d,",data[i].num_user_for_reviews);        fprintf(output_file,"%s,",data[i].language);        fprintf(output_file,"%s,",data[i].country);        fprintf(output_file,"%s,",data[i].content_rating);        fprintf(output_file,"%d,",data[i].budget);        fprintf(output_file,"%d,",data[i].title_year);        fprintf(output_file,"%d,",data[i].actor_2_facebook_likes);       fprintf(output_file,"%.1f,",data[i].imdb_score);        fprintf(output_file,"%.1f,",data[i].aspect_ratio);        fprintf(output_file,"%d\n",data[i].movie_facebook_likes);    }        fclose(output_file);    //closedir(dp);    }void init_tid_pool(){	int i;	for(i = 0; i < MAX_NUM_THREAD; i++)	{		tid_pool[i].isFree = 1;		tid_pool[i].socketfd = -1;	}}/** * check_enum *  * This below method checks for the correct enum entered by the user *  *  * */ /** * self_tokenizer *  * Tokenizer method begins here *  *  * */int self_tokenizer(char line[], char token[], int index){		int i = 0;		if(line[index] == '"')	{		index++;				while(line[index] != '"' && line[index] != '\0' && line[index] != '\n')		{			token[i] = line[index];			i++;			index++;		}				token[i] = '\0';				index = index + 2;			}	else	{		while(line[index] != ',' && line[index] != '\0' && line[index] != '\n')		{			token[i] = line[index];			index++;			i++;		}				token[i] = '\0';				index++;			}		return index;		}/* return the index of available tid in pool */int get_tid(){	int i;	for (i = 0; i < MAX_NUM_THREAD; i++)	{		if (tid_pool[i].isFree == 1)		{			return i;		}	}	return -1;}void release_tid(int index){	tid_pool[index].isFree = 1;}void * service(void *args){	pthread_mutex_lock(&lockA);		int curr_arr_size = 5000;    int elements_filled = 0;	movie_struct *data = (movie_struct*)malloc(sizeof(movie_struct) * curr_arr_size);			int index = (int)(intptr_t)args;	//int intbyte = 500;	int client_socket = tid_pool[index].socketfd;	int bytesReceived = 0;							char column_name[256];	strcpy(column_name,tid_pool[index].columnName);	//printf("we got volumn name in the worker thread %s", column_name);	struct stat st;	char token[500];	token[0] = '\0';	int file_index;	file_index = 0;	int linesFilled;	linesFilled = 0;	movie_struct temp_movie;	//FILE *fp;	//char fname[256];	//char columnname[500];	 char recvBuff[1024];	 char recvnum[3];			     memset(recvBuff, 0, sizeof(recvBuff));    memset(recvnum, 0, sizeof(recvnum));	//read(client_socket, fname, 1024);	//strcat(fname,"AK");	//printf("File Name: %s\n",fname);	//printf("Receiving file...\n");		//recv(client_socket, column_num, 1, 0);	//recv(client_socket, column_num_len, atoi(column_num), 0);			//recv(client_socket, column_name, atoi(column_num), 0);			int i = 0;	/*for(i = 0; i < 3; i++)	   {		   recvnum[i] = '\0';	   }*/   	    int z =0;        while(1)    { 		//z++;		//eofTerm = strstr(recvBuff, "QTRSG");				//printf("recvnum: %d\n", atoi(recvnum));		//int temp_num = atoi(recvnum);		//temp_num = temp_num - 1;				bytesReceived = recv(client_socket, recvnum, 3, 0);				if(strcmp("808", recvnum) == 0)		{			//send all sorted files to client			//call dump request detected			//dump();						break;		}				recv(client_socket, recvBuff, atoi(recvnum), 0);				//printf("buffer: %s\n", recvBuff);				//z++;						/**	    * This will resize once the array is 	    * over a certain limit.	    * */	   if(elements_filled == curr_arr_size)	   {		   curr_arr_size = curr_arr_size*2;		   data = realloc(data, sizeof(movie_struct)*(curr_arr_size));		   	   }						if(atoi(recvnum) != 0)		{			if(elements_filled == curr_arr_size)			{				curr_arr_size = curr_arr_size*2;				data = realloc(data, sizeof(movie_struct)*(curr_arr_size));			}			z++;			file_index = self_tokenizer(recvBuff, token, file_index);			temp_movie.color[0] = '\0';			strcpy(temp_movie.color, token);									file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.director_name[0] = '\0';	        strcpy(temp_movie.director_name, token);	       // printf("temp_movie.director_name: %s \n", temp_movie.director_name);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.num_critic_for_reviews = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.duration = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.director_facebook_likes = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.actor_3_facebook_likes = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.actor_2_name[0] = '\0';	        strcpy(temp_movie.actor_2_name, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.actor_1_facebook_likes = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.gross = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.genres[0] = '\0';	        strcpy(temp_movie.genres, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.actor_1_name[0] = '\0';	        strcpy(temp_movie.actor_1_name, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.movie_title[0] = '\0';	        strcpy(temp_movie.movie_title, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.num_voted_users = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.cast_total_facebook_likes = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.actor_3_name[0] = '\0';	        strcpy(temp_movie.actor_3_name, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.facenumber_in_poster = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.plot_keywords[0] = '\0';	        strcpy(temp_movie.plot_keywords, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.movie_imdb_link[0] = '\0';	        strcpy(temp_movie.movie_imdb_link, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.num_user_for_reviews = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.language[0] = '\0';	        strcpy(temp_movie.language, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.country[0] = '\0';	        strcpy(temp_movie.country, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.content_rating[0] = '\0';	        strcpy(temp_movie.content_rating, token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.budget = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.title_year = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.actor_2_facebook_likes = atoi(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.imdb_score = atof(token);	        	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.aspect_ratio = atof(token);	   	        file_index = self_tokenizer(recvBuff, token, file_index);	        temp_movie.movie_facebook_likes = atoi(token);	   	   	        file_index = 0;	       // int i;	        /*for(i = 0; i < 1000; i++)	        {		        recvBuff[i] = '\0';	        }*/						//file_index = 0;			data[elements_filled] = temp_movie;	   	    elements_filled++;	    linesFilled++;					}		//file_index = 0;		        //printf("recvBuff: %s\n", recvBuff);                /*if(strcmp(recvBuff, "QTR") == 0 || strcmp(recvnum, "QTR") == 0)        {			break;		}*/                        //printf("recvBuff: %s\n", recvBuff);      //      printf("recvBuff  bytes: %d\n", bytesReceived);               //int i;	   for(i = 0; i < 1024; i++)	   {		   recvBuff[i] = '\0';	   }	   for(i = 0; i < 3; i++)	   {		   recvnum[i] = '\0';	   }            }                //printf(" z %d \n", z);        //printf("\n print : %s \n", recvnum);                    int cases;	if((strcmp(column_name,"color")==0)){cases=1;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"director_name")==0){cases=2;MergeSort(data,0,elements_filled-1,cases);}		else if(strcmp(column_name,"actor_2_name")==0){cases=4;MergeSort(data,0,elements_filled-1,cases);}	 	else if(strcmp(column_name,"genres")==0){cases=5;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"actor_1_name")==0){cases=6;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"movie_title")==0){cases=7;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"actor_3_name")==0){cases=8;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"plot_keywords")==0){cases=9;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"movie_imdb_link")==0){cases=10;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"language")==0){cases=11;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"country")==0){cases=12;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"content_rating")==0){cases=13;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"num_critic_for_reviews")==0){cases=14;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"duration")==0){cases=15;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"director_facebook_likes")==0){cases=16;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"actor_3_facebook_likes")==0){cases=17;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"actor_1_facebook_likes")==0){cases=18;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"gross")==0){cases=19;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"num_voted_users")==0){cases=20;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"cast_total_facebook_likes")==0){cases=21;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"facenumber_in_poster")==0){cases=22;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"num_user_for_reviews")==0){cases=23;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"budget")==0){cases=24;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"title_year")==0){cases=25;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"actor_2_facebook_likes")==0){cases=26;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"imdb_score")==0){cases=27;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"aspect_ratio")==0){cases=28;MergeSort(data,0,elements_filled-1,cases);}	else if(strcmp(column_name,"movie_facebook_likes")==0){cases=29;MergeSort(data,0,elements_filled-1,cases);}	else	{		printf("Use the same fields from .csv file\n");		printf("Invalid Field\n Run the program again with correct field \n");		//abort();	}                 print("sorted",elements_filled,data);        	//	 printf("\nFile sent....Completed\n");	 	 	 //send the file name [DONE]  Allsorted-columnName.csv	 char fileName[256] = "Allsorted-";	 strcat(fileName,column_name);	 strcat(fileName,".csv");	// printf("new file name %s\n",fileName);		//send file to clinet : 1. variables	int filefd;	char remote_file[BUFSIZ];	  ssize_t read_return;	  char buffer[BUFSIZ];	  	//open file	filefd = open("sorted.csv",O_RDONLY);	if (filefd == -1) {                    perror("open send file");                    // exit(EXIT_FAILURE);                                    }                       //fstat for size       if (fstat(filefd,&st) < 0) {                    perror("stat send file");                    // exit(EXIT_FAILURE);                    close(filefd);                                 }	memset(remote_file, 0, sizeof(remote_file));		sprintf(remote_file, "%lld,%s",                    (long long) st.st_size,fileName);                           //size works****   //      printf("size of file from server to client %s\n", remote_file);         //this send is for file size    	send(client_socket, remote_file, sizeof(remote_file), 0);				//send the actual data	while (1) {                    read_return = read(filefd, buffer, BUFSIZ);                    if (read_return == 0)                        break;                    if (read_return == -1) {                        perror("read here?");                        // exit(EXIT_FAILURE);                        break;                    }                    if (write(client_socket, buffer, read_return) == -1) {                        perror("write");                        // exit(EXIT_FAILURE);                        break;                    }                }		close(filefd);			remove("sorted.csv");		free(data);		close(client_socket);		release_tid(index);		num_of_thread--;	pthread_mutex_unlock(&lockA);	pthread_exit(0);}int main(int argc, char **argv){	if(argc != 3)	{		printf("usage: ./server -p <port>\n");		exit(-1);	}	if(strcmp(argv[1],"-p") != 0)	{		printf("usage: ./server -p <port>\n");		exit(-1);	}	struct sockaddr_in address;	size_t clen=0;	if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) <= 0)	{		perror("socket");		exit(EXIT_FAILURE);	}		address.sin_family = AF_INET;    address.sin_addr.s_addr = INADDR_ANY;	address.sin_port = htons(atoi(argv[2]));		if (bind(server_sock, (struct sockaddr*)&address, sizeof(address)) < 0)	{		perror("bind");		close(server_sock);		exit(EXIT_FAILURE);	}	if (listen(server_sock, 0) < 0)	{		perror("listen");		close(server_sock);		exit(EXIT_FAILURE);	}	//printf("Waiting for connections...\n");	init_tid_pool();	printf("Recieved connections From: ");	fflush(stdout);		while (status)	{		clen = sizeof(address);		client_sock = accept(server_sock, (struct sockaddr*)&address, (socklen_t*)&clen);	//printf("%s,",inet_ntoa(address));	 //printf("IP Address is: %s\n", inet_ntoa(address));			if (client_sock < 0)		{			perror("accept");			close(server_sock);			exit(EXIT_FAILURE);		}		char str[INET_ADDRSTRLEN];inet_ntop( AF_INET, &address.sin_addr.s_addr, str, INET_ADDRSTRLEN );	      printf("%s",str);		printf(",");		fflush(stdout);		//printf("[+] Connect to client %d\n", server_sock); 		char getColumn[256];		int getcol_len = recv(client_sock, getColumn, sizeof(getColumn), 0);		if(getcol_len < 0){			printf("error writing column name\n");		}		//printf(getCoulmn);		//printf("getColumn %s\n",getColumn);		if (num_of_thread < MAX_NUM_THREAD)		{			int i = get_tid();			tid_pool[i].socketfd = client_sock;			strcpy(tid_pool[i].columnName, getColumn);			memset(getColumn, 0, sizeof(getColumn));			pthread_create(&tid_pool[i].tid, NULL, service, (void *)(intptr_t)i);			num_of_thread++;			pthread_detach(tid_pool[i].tid);		}		else		{			while (num_of_thread >= MAX_NUM_THREAD)			{				sleep(1);			}		}	}			close(server_sock);	//free(data);	return 0;}