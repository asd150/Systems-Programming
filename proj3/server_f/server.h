#ifndef SORTER_H
#define SORTER_H

//this is the .h file

//struct Definitions
typedef struct
{
	char color[50];
	char director_name[100];
	int num_critic_for_reviews;
	int duration;
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char actor_2_name[100];
	int actor_1_facebook_likes;
	int gross;
	char genres[200];
	char actor_1_name[100];
	char movie_title[200];
	int num_voted_users;
	int cast_total_facebook_likes;
	char actor_3_name[100];
	int facenumber_in_poster;
	char plot_keywords[200];
	char movie_imdb_link[300];
	int num_user_for_reviews;
	char language[100];
	char country[100];
	char content_rating[50];
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	float imdb_score;
	float aspect_ratio;
	int movie_facebook_likes;
	
} movie_struct;

enum columns{COLOR, DIRECTORNAME, NUM_CRITIC_FOR_REVIEWS, DURATION, DIRECTOR_FACEBOOK_LIKES, ACTOR_3_FACEBOOK_LIKES, ACTOR_2_NAME, ACTOR_1_FACEBOOK_LIKES, GROSS, GENRES, ACTOR_1_NAME, MOVIE_TITLE, NUM_VOTED_USERS, CAST_TOTAL_FACEBOOK_LIKES, ACTOR_3_NAME, FACENUMBER_IN_POSTER, PLOT_KEYWORDS, MOVIE_IMDB_LINK, NUM_USER_FOR_REVIEWS, LANGUAGE, COUNTRY, CONTENT_RATING, BUDGET, TITLE_YEAR, ACTOR_2_FACEBOOK_LIKES, IMDB_SCORE, ASPECT_RATIO, MOVIE_FACEBOOK_LIKES };

int self_tokenizer(char line[], char token[], int index);

//void mergeSort(struct movie_struct ** movie_structs, int l, int r, enum columns columns);

//void merge(struct movie_struct ** movie_structs, int l, int m, int r, enum columns columns);

#endif
