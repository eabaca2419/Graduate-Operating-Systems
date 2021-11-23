#include <stdlib.h> 
#include <stdio.h>
#include <pthread.h>

void *catalanThread(void *); //thread subroutine 

typedef struct {
    int threadNum;
    int numOfThreads;
    int cNumber;
}Data_t; //data structure for the threads 

long double *array = NULL; //create a global array 
long double catalanNumber(int n); //catalan number sequence function 

int main(int argc, char **argv){ 
     if(argc < 3){  //check if it received 3 arguments 
        printf("Usage: ./executable number threads\n");
        return EXIT_FAILURE;
    }

    int num = atoi(argv[1]);    //Safe the number for the catalan number
    int numThreads = atoi(argv[2]); //Safe the second argument which is the number of threads
    num++;
    
    if(num < 0)  //If the number is less than 0
        num = 0;    
    if(numThreads < 0)  //If the thread is 0 or lower set the number of threads to 1
        numThreads = 1;

    pthread_t tasks[numThreads];   
    array = (long double *)malloc(sizeof(long double)*num); //Allocate the num size of array for the catalan numbers 
    Data_t threadsData[numThreads]; //Allocate the data structure for the threads

    /*load the data structure with the correct value*/
    for(int i = 0; i < numThreads; i++){
        threadsData[i].threadNum = i; //Set thread num 
        threadsData[i].cNumber = num; //Set the catalan number 
        threadsData[i].numOfThreads = numThreads; //Set the total threads 
        pthread_create(&tasks[i], NULL, catalanThread,(void*)&threadsData[i]);  //create the thread
    }
    /*Wait for all threads to finish*/
    for(int i =0; i < numThreads; i++)
        pthread_join(tasks[i], NULL);

   FILE *file = fopen("catalan.dat", "w");  //Create a file name "catalan.dat" as a write file

   /*Iterate over the array*/ 
    for(int i = 0; i < num; i++)
        fprintf(file,"%d: %Lf\n", i, array[i]); //Print to the file 

    fclose(file);  //Close the file object 
    printf("Catalan sequence locate at catalan.dat\n");

    /*Free the heap memory*/ 
    free(array);
    return 0;
}
/*Threads*/ 
void *catalanThread(void *param){
   Data_t thread = *(Data_t *)param; //Dereferance the data structure 
   /*Iterate over the thread num, i < cNumber, and step of the total threads*/
   for(int i = thread.threadNum; i < thread.cNumber; i += thread.numOfThreads)
       array[i] = catalanNumber(i); //Save to the array 
    pthread_exit(0); //exit the thread
}

long double catalanNumber(int n){ 
    /*Base Case*/
    if (n <= 1) 
        return 1;
   /*catalanNumber(n) is sum of catalanNumber(i)*catalanNumber(n-i-1)*/
   unsigned long int res = 0;
    for (int i=0; i<n; i++)
        res += catalanNumber(i)*catalanNumber(n-i-1);
    return res;
}
