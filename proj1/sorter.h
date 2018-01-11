//Florian Malaj
//Arthkumar Desai
//cs214 proj0

typedef struct records {
	char*color;
	char* dirName;
	int review;
	double duration;
	int dir_likes;
	int actor3_likes;
	char* actor2_name;
	int actor1_likes;
	double gross;
	char* genres;
	char* actor1_name;
	char* movieTitle;
	int voted_users;
	int cast_total_fb_likes;
	char* actor3_name;
	int poster_faces;
	char* plot;
	char* imdb_link;
	int num_user_for_reviews;
	char* lang;
	char* country;
	char* content_rating;
	double budget;
	int title_year;
	int actor2_fb_likes;
	double imdb_score;
	double aspect_ratio;
	int movie_facebook_likes;
	
}movie;



char* my_strtok(char*str,const char*delim,char** store);
char* strtk(char*str,const char*delim);
void Merge(movie *arr, int low, int mid, int high,int cases,int lines,char*);
void MergeSort(movie *arr, int low, int high,int Scases,char*);
void Print(const char *tag, int n, movie *array,char*);
//int sort(char* fileName,char* path,char* columnName);
