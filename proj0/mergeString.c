//Florian Malaj
//Arthkumar Desai
//cs214 proj0

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sorter.h"
void MergeSort(movie *arr, int low, int high,int Scases)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        //printf("-->> %s: lo = %d, md = %d, hi = %d\n", __func__, low, mid, high);

        MergeSort(arr, low, mid,Scases);
        MergeSort(arr, mid + 1, high,Scases);

        Merge(arr, low, mid, high,Scases,high);
        //printf("<<-- %s: lo = %d, md = %d, hi = %d\n", __func__, low, mid, high);
    }
}
void Merge(movie *arr, int low, int mid, int high,int cases,int lines)
{
    int mergedSize = high - low + 1;
    movie *temp = (movie *)malloc(mergedSize * sizeof(movie));
    int mergePos = 0;
    int leftPos = low;
    int rightPos = mid + 1;

    if(cases==1){while (leftPos <= mid && rightPos <= high){
        if(strcasecmp (arr[leftPos].color,arr[rightPos].color)<0){
            temp[mergePos++] = arr[leftPos++];}else{
            temp[mergePos++] = arr[rightPos++];}}//else
            }//While

    if(cases==2){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].dirName,arr[rightPos].dirName)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
   
    if(cases==4){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].actor2_name,arr[rightPos].actor2_name)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
   
    if(cases==5){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].genres,arr[rightPos].genres)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
    if(cases==6){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].actor1_name,arr[rightPos].actor1_name)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
     if(cases==7){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].movieTitle,arr[rightPos].movieTitle)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
     if(cases==8){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].actor3_name,arr[rightPos].actor3_name)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
     if(cases==9){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].plot,arr[rightPos].plot)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
     if(cases==10){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].imdb_link,arr[rightPos].imdb_link)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
     if(cases==11){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].lang,arr[rightPos].lang)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While

     if(cases==12){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].country,arr[rightPos].country)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While

     if(cases==13){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(strcasecmp (arr[leftPos].content_rating,arr[rightPos].content_rating)<0)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While

     if(cases==14){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(arr[leftPos].review < arr[rightPos].review)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
     }
     if(cases==15){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].duration<arr[rightPos].duration)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
     }
     if(cases==16){
    while (leftPos <= mid && rightPos <= high)     
    {
      if(arr[leftPos].dir_likes<arr[rightPos].dir_likes)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
     }
     if(cases==17){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].actor3_likes<arr[rightPos].actor3_likes)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
     }
     if(cases==18){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].actor1_likes<arr[rightPos].actor1_likes)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
     }
     if(cases==19){
    while (leftPos <= mid && rightPos <= high)     
    {
       if(arr[leftPos].gross<arr[rightPos].gross)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
     }
    if(cases==20){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(arr[leftPos].voted_users<arr[rightPos].voted_users)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==21){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].cast_total_fb_likes<arr[rightPos].cast_total_fb_likes)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==22){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(arr[leftPos].poster_faces<arr[rightPos].poster_faces)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==23){
    while (leftPos <= mid && rightPos <= high)     
    {
       if(arr[leftPos].num_user_for_reviews<arr[rightPos].num_user_for_reviews)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==24){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].budget<arr[rightPos].budget)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==25){
    while (leftPos <= mid && rightPos <= high)     
    {
       if(arr[leftPos].title_year<arr[rightPos].title_year)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++];} }//else
    }//While
    
    if(cases==26){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].actor2_fb_likes<arr[rightPos].actor2_fb_likes)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==27){
    while (leftPos <= mid && rightPos <= high)     
    {
        if(arr[leftPos].imdb_score<arr[rightPos].imdb_score)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==28){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].aspect_ratio<arr[rightPos].aspect_ratio)
        { temp[mergePos++] = arr[leftPos++];}
        else{temp[mergePos++] = arr[rightPos++]; }//else
    }//While
    }
    if(cases==29){
    while (leftPos <= mid && rightPos <= high)     
    {
         if(arr[leftPos].movie_facebook_likes<arr[rightPos].movie_facebook_likes)
        { temp[mergePos++] = arr[leftPos++];
        }
        else
        {
            temp[mergePos++] = arr[rightPos++];
            }
        //else
    }
    }//While
    while (leftPos <= mid){
        temp[mergePos++] = arr[leftPos++];}
    while (rightPos <= high){
        temp[mergePos++] = arr[rightPos++];}

    assert(mergePos == mergedSize);

    Print("merged", mergedSize, temp);

    for (mergePos = 0; mergePos < mergedSize; ++mergePos)
        arr[low + mergePos] = temp[mergePos];

    free(temp);         
   
}

 void Print(const char *tag, int n, movie *array)
{
    int i;
    printf("%s:\n", tag);
    printf("color\t");
        printf("dirName\t");
        printf("review\t ");
        printf("duration\t ");
        printf("dir_likes\t ");
        printf("actor3_likes\t ");
        printf("actor2_name\t ");
        printf("actor1_likes\t ");
        printf("gross\t ");
        printf("genres\t ");
        printf("actor1_name\t ");
        printf("movieTitle\t ");
        printf("voted_users\t ");
        printf("cast_total_fb_likes\t ");
        printf("actor3_name\t ");      
        printf("poster_faces\t ");
        printf("imdb_link\t ");
        printf("num_user_for_reviews\t ");
        printf("language\t ");
        printf("country\t ");
        printf("content_rating\t ");
        printf("budget\t ");
        printf("title_year\t ");
        printf("actor2_fb_likes\t ");
        printf("imdb_score\t ");
        printf("aspect_ratio\t ");
        printf("movie_facebook_likes\n ");
    
    for ( i = 0; i < n; i++){
        printf(" %s\t ",array[i].color);
        printf(" %s\t",array[i].dirName);
        printf(" %d\t ",array[i].review);
        printf(" %.f\t ",array[i].duration);
        printf(" %d\t ",array[i].dir_likes);
        printf(" %d\t ",array[i].actor3_likes);
        printf(" %s\t ",array[i].actor2_name);
        printf(" %d\t ",array[i].actor1_likes);
        printf(" %.f\t ",array[i].gross);
        printf(" %s\t ",array[i].genres);
        printf(" %s\t ",array[i].actor1_name);
        printf(" %s\t ",array[i].movieTitle);
        printf(" %d\t ",array[i].voted_users);
        printf(" %d\t ",array[i].cast_total_fb_likes);
        printf(" %s\t ",array[i].actor3_name);
        printf(" %d\t ",array[i].poster_faces);
        printf(" %s\t ",array[i].plot);
        printf(" %s\t ",array[i].imdb_link);
        printf(" %d\t ",array[i].num_user_for_reviews);
        printf(" %s\t ",array[i].lang);
        printf(" %s\t ",array[i].country);
        printf(" %s\t ",array[i].content_rating);
        printf(" %.f\t ",array[i].budget);
        printf(" %d\t ",array[i].title_year);
        printf(" %d\t ",array[i].actor2_fb_likes);
        printf(" %.1f\t ",array[i].imdb_score);
        printf(" %.1f\t ",array[i].aspect_ratio);
        printf(" %d\n ",array[i].movie_facebook_likes);
    }
                     
    
}







