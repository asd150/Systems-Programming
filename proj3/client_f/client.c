//works

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "client.h"
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

//#include "mergesort.c"


/**color,
 * director_name,
 * num_critic_for_reviews,
 * duration,
 * director_facebook_likes,
 * actor_3_facebook_likes,
 * actor_2_name,
 * actor_1_facebook_likes,
 * gross,
 * genres,
 * actor_1_name,
 * movie_title,
 * num_voted_users,
 * cast_total_facebook_likes,
 * actor_3_name,
 * facenumber_in_poster,
 * plot_keywords,
 * movie_imdb_link,
 * num_user_for_reviews,
 * language,
 * country,
 * content_rating,
 * budget,
 * title_year,
 * actor_2_facebook_likes,
 * imdb_score,
 * aspect_ratio,
 * movie_facebook_likes
**/

//int final_pidarr[256];
//int final_track = 0;

char out_dir[1000];

//pid_t pid_arr[256];

//int largest_pid_track = 0;
//int final_pidarr[256];

movie_struct * data ;
int curr_arr_size = 5000;
int elements_filled = 0;

volatile int signo_taken;



struct sort_file_param {
	
	char new_path[1000];
	char column_name[1000];
	char final_output_dir[1000];
	
};

struct sort_file_param *files_param;
pthread_t *tray;
int tid_lim = 1000;
int tid_track = 0;

pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;

struct sockaddr_in address;
int sock_num = 0;
int valread = 0;
int port_num = 0;
char *hostName;
struct hostent *server_host;


void sig_handler(int signo)
{
    signo_taken = signo;
}


/**
 * get_outfile_name
 * 
 * get_outfile_name method begins here
 * 
 * 
 * */


char * get_outfile_name(char csv_file[], char column_name[], char output_file[])
{
	int i = 0;
	int j = 0;
	
	int slash_dex = 0;
	int len = strlen(csv_file);
	char out_path[1000];
	
	for(i = 0; i < len-4; i++)
	{
		if(csv_file[i] == '/')
		{
			slash_dex = i;
		}
		
	}
	
	char csv[25];
	
	for(i = slash_dex+1, j = 0; i < len-4; i++, j++)
	{
		csv[j] = csv_file[i];
		
	}
	
	strcpy(out_path, output_file);
	
	strcat(out_path, "/");
	
	strcat(out_path, csv);

	strcat(out_path, "-sorted-");

	strcat(out_path, column_name);
	
	strcat(out_path, ".csv");
	
	return out_path;
	
}


/**
 * sortFile
 * 
 * This method checks the input
 * and correctly submits the required part to 
 * mergesort
 * 
 * 
 * */

int sortFile(char * filePath, char* columnName, char * output_dir)
{
	pthread_mutex_lock(&tlock);
	char input[1024];
	//char eof[3] = "808";
	//char eof_char[3];
	char line_len[3];
	input[0] = '\0';
	
	
	//pthread_mutex_lock(&tlock);
   
   FILE* file;
   file = fopen(filePath, "r");
   
   //fseek(file, 0L, SEEK_END);
   //int sizeoffile = ftell(file);
   
   //fseek(file, 0L, SEEK_SET);*/
   
   //fgets(input, 1024, file);
   
   fgets(input, 1024, file);
   
   //char buff[sizeoffile];
   
	
   while(fgets(input, 1024, file) != NULL)
   {
	   
	   //printf("input len is: %d \n",strlen(input));
	   
	   int len = strlen(input);
	   
	   sprintf(line_len, "%d", len);
	   
	   if((write(sock_num, line_len, strlen(line_len))) < 0)
	   {
		   //printf("input line: %s\n", input);
		   printf("ERROR writing to server1!!!\n");
	   }
	   
	   
	   
	   if((write(sock_num, input, strlen(input))) < 0)
	   {
		   printf("ERROR writing to server2!!!\n");
	   }

       line_len[0] = '\0';
       line_len[1] = '\0';
       line_len[2] = '\0';
       
       int i;
	   for(i = 0; i < 1024; i++)
	   {
		   input[i] = '\0';
	   }
       
       //printf("%s", "String received from the server: ");
       
       
   }
   
       
   
   pthread_mutex_unlock(&tlock);
   
   
   
   return 0;



}


/**
 * Check_csv
 * 
 * checks if a file is a csv file or not
 * 
 * 
 * */

int check_csv(char *file_name)
{
	int len = strlen(file_name);
	
	if(file_name[len-1] == 'v' && file_name[len-2] == 's' && file_name[len-3] == 'c' && file_name[len-4] == '.')
	{
		
		char input[419];
		
		char moviedata_column[1000] = "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes";
		
		FILE * csv_file = fopen(file_name, "r");
		
		if(csv_file == NULL)
		{
			return 1;
		}
		
		fgets(input, 418, csv_file);
		
		
		if(strcmp(input, moviedata_column) == 0)
		{
			
			fclose(csv_file);
			return 0;
		}
		else
		{
			fclose(csv_file);
			return 1;
		}
		
		
		return 0;
		
	}
	else
	{
		return 1;
	}
	
}




void* thread_func(void * ptr)
{
	
    struct sort_file_param * param_struct  = (struct sort_file_param *) ptr;

    sortFile(param_struct->new_path, param_struct->column_name, param_struct->final_output_dir);
    
    //connect to the server here and wait for it to return
    //once it returns that the file has been sorted then continue

    pthread_exit(NULL);
    
}


/**
 * scan_csv_files
 * 
 * This method goes through a directory
 * and checks for csv files 
 * 
 * 
 * */

int scan_csv_files(char *src_dir_name, char *column_name, char *output_dir)
{
	
	DIR* directory = opendir(src_dir_name);
	struct dirent *newFile = NULL;
	
	if(!directory)
	{
		return -1;
	}
	
	while(newFile = readdir(directory))
	{
		if (!strcmp(".", newFile->d_name) || !strcmp("..", newFile->d_name)) 
		{
			continue;
		}
		
		if(newFile->d_type == DT_REG)
		{	
			char * newPath = (char*) malloc(strlen(newFile->d_name) + strlen(src_dir_name) + 2);
			
			
			newPath[0] = '\0';
			strcpy(newPath, src_dir_name);
			strcat(newPath, "/");
			strcat(newPath, newFile->d_name);
			
			int fd = open(newPath, O_RDONLY);
			if(fd < 0)
			{
				return -1;
			}
			
			int len = lseek(fd, 0, SEEK_END);
			close(fd);
			
			if(!check_csv(newPath))
			{
				
				struct sort_file_param param_struct;
				strcpy(param_struct.new_path, newPath);
				strcpy(param_struct.final_output_dir, out_dir);
				strcpy(param_struct.column_name, column_name);
				
				
				if(tid_track == tid_lim)
				{
					
					tid_lim  = tid_lim *2;
					files_param = realloc (files_param, sizeof(struct sort_file_param) * tid_lim);
					tray  = realloc (tray, sizeof(pthread_t) * tid_lim);
				
				}
				
				//printf("it segs in scan\n");
				
				
				
				files_param[tid_track] = param_struct;
				
				
				pthread_create(&tray[tid_track], NULL, thread_func, &files_param[tid_track]);
				
				tid_track += 1;
				
				//printf("maybe after creating the thread\n");
				
				
				
			}
			
			free(newPath);
			
		}
		else if(newFile->d_type == DT_DIR)
		{
			char * newPath = (char*) malloc(strlen(newFile->d_name) + strlen(src_dir_name) + 2);
			
			newPath[0] = '\0';
			strcpy(newPath, src_dir_name);
			strcat(newPath, "/");
			strcat(newPath, newFile->d_name);
			
			scan_csv_files(newPath, column_name, output_dir);
				
			
			free(newPath);
			
		}
		
	}
	
	
	
	closedir(directory);
	
	
	return 1;
		
}


/**
 * Main
 * 
 * main method interacts with the user 
 * and calls the scan_csv recursive method
 * 
 * 
 * */

int main(int argc, char * argv[])
{
	
	
	if(argc < 7)
	{
		printf("ERROR Not Enough Parameters given\n");
		return -1;
	}
	
	char src_dir[1000];
	
	
	if(argc == 7)
	{
		if(strcmp(argv[3], "-h") != 0 && strcmp(argv[5], "-p") != 0)
		{
			printf("ERROR Invalid parameters\n");
			return -1;
		}
		
		getcwd(src_dir, 1000);
		strcpy(out_dir, src_dir);
		
	}
	else if(argc == 9)
	{
		if(strcmp(argv[3], "-h") != 0 && strcmp(argv[5], "-p") != 0)
		{
			printf("ERROR Invalid parameters\n");
			return -1;
		}
		
		if(strcmp(argv[7], "-d") == 0)
		{
			strcpy(src_dir, argv[8]);
			getcwd(out_dir, 1000);
		}
		else if(strcmp(argv[7], "-o") == 0)
		{
			out_dir[0] = '\0';
			getcwd(src_dir, 1000);
			strcpy(out_dir, argv[8]);
		}
		else
		{
			printf("ERROR Invalid parameters\n");
			return -1;
		}
		
	}
	else if(argc == 11)
	{
		if(strcmp(argv[3], "-h") != 0 && strcmp(argv[5], "-p") != 0)
		{
			printf("ERROR Invalid parameters\n");
			return -1;
		}
		
		
		if(strcmp(argv[7], "-d") != 0 && strcmp(argv[9], "-o") != 0)
		{
			printf("ERROR Invalid parameters\n");
			return -1;
		}
		
		out_dir[0] = '\0';
		strcpy(src_dir, argv[8]);
		strcpy(out_dir, argv[10]);
	}
	
	
	//char fileName[] = "Pid.txt";
	
	//FILE *file = fopen(fileName, "w");
	
	
	char *column_name = (char *) malloc(sizeof(char)*20);
	
	
	if(strcmp(argv[2], "color") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "director_name") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "num_critic_for_reviews") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "duration") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "director_facebook_likes") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "actor_3_facebook_likes") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "actor_2_name") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "actor_1_facebook_likes") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "gross") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "genres") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "actor_1_name") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "movie_title") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "num_voted_users") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "cast_total_facebook_likes") == 0)
	{
		column_name = argv[2];
	}
	else if(strcmp(argv[2], "actor_3_name") == 0)
	{
		column_name = argv[2];
	}
    else if(strcmp(argv[2], "facenumber_in_poster") == 0)
    {
	    column_name = argv[2];
	}
    else if(strcmp(argv[2], "plot_keywords") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "movie_imdb_link") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "num_user_for_reviews") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "language") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "country") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "content_rating") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "budget") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "title_year") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "actor_2_facebook_likes") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "imdb_score") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "aspect_ratio") == 0)
    {
	    column_name = argv[2];
    }
    else if(strcmp(argv[2], "movie_facebook_likes") == 0)
    {
	    column_name = argv[2];
    }
    else
    {
	    printf("Input should be inorder of: cat csvFileName | ./sorter -c columnname\n");
	    printf("column_name invalid\n");
        return -1;
	   
    }
    
    //printf("!seg fault before scan!\n");
    
    hostName = argv[4];
    
    //printf("!seg fault before scan!\n");
    
	//printf("%s,\n", hostName);
	
	server_host = gethostbyname(hostName);
	if(server_host == NULL)
	{
		printf("Could not get the Host\n");
		return -1;
	}
    
    
    port_num = atoi(argv[6]);
    
    //printf("!seg fault before scan!\n");
    
    
    memset(&address, 0, sizeof(address));
  
    address.sin_family = AF_INET;
    address.sin_port = htons(port_num);
    
    //printf("%d\n", port_num);
    
    
    
    bcopy((char*)server_host->h_addr,(char*)&address.sin_addr.s_addr, server_host->h_length);
    
    sock_num = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sock_num < 0)
    {
		printf("Socket Creation error!!\n");
		return -1;
	}
	
    
    
    if (connect(sock_num, (struct sockaddr*) &address, sizeof(address)) < 0)
    {
        printf("Could not connect\n");
        return -1;
    }
    
    printf("connected & sending files....\n");
    
    
    
    char send_colmn[256];
    strcpy(send_colmn, column_name);
    int col_len = write(sock_num, send_colmn, sizeof(send_colmn));
    
    memset(send_colmn, 0, sizeof(send_colmn));
	
	
	files_param = realloc (files_param, sizeof(struct sort_file_param) * tid_lim);
	tray  = realloc (tray, sizeof(pthread_t) * tid_lim);
	
	
	//printf("!seg fault before scan!\n");
	scan_csv_files(src_dir, column_name, out_dir);
	
	
	int i = 0;
	
	for(i = 0; i < tid_track; i++)
	{
		pthread_join(tray[i], NULL);
	}
	
	//dump request
	char eof[3] = "808";
	
	if((write(sock_num, eof, strlen(eof))) == 0)
	{
		printf("ERROR writing to server!!!\n");
	}
	
	
	//variables
	//int gotBytes = 0;
	char receiveFileName[BUFSIZ];
	long long file_length;
	  char *file_path;
	  //strcpy(file_path, out_dir);
	    ssize_t read_return;
	   int filefd;
	    char buffer[BUFSIZ];
	
	//receive sorted file from server
	while (recv(sock_num, receiveFileName, sizeof(receiveFileName), 0)) 
	{
		
		
		file_length = strtoll(receiveFileName,&file_path,10);
		
		if (*file_path != ',') {
            fprintf(stderr,"syntax error in request -- '%s'\n",
                receiveFileName);
            exit(EXIT_FAILURE);
        }
        file_path += 1;
        
        
         fprintf(stderr, "is the file name received? ?   =>  %s [%lld bytes]\n",
            file_path,file_length);
		
		strcat(out_dir, "/");
		strcat(out_dir, file_path);
		
		printf("out_dir : %s\n",out_dir);
		
		
		filefd = open(out_dir,
            O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
		
		
		for (;  file_length > 0;  file_length -= read_return) {
            read_return = BUFSIZ;
            if (read_return > file_length)
                read_return = file_length;

            read_return = read(sock_num, buffer, read_return);
            if (read_return == -1) {
                perror("read here2?");
                exit(EXIT_FAILURE);
            }
            if (read_return == 0)
                break;

            if (write(filefd, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
printf("file_path %s\n",file_path);
        fprintf(stderr,"file complete\n");
		
		close(filefd);
		break;
		
	}//while loop
	
	printf("file recieved now closing..!!\n");
	
	close(sock_num);
	return 0;
	
}



