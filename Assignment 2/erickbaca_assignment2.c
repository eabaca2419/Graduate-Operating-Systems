#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * printCatalanNumbers(void *param); //subroutine for print 
long double catalanNumber(int n); //catalan number function 

typedef struct{
    int high;
    int low;
    int threadNum;
}Boundary; //data structure to store the data

int main(int argc, char *argv[]){
    if(argc < 3){ 
        printf("./executable nth threads\n");
        return 1;
    }
    int n = atoi(argv[1]); //convert array to integer 
    int numThreads = atoi(argv[2]); //convert array to integer 
    FILE *file = fopen("catalan.dat", "w"); //create a file, open a file as "write"

    if(file == NULL){
       fprintf(stderr, "Error opening the file\n");
       return 1;             
    }
    //set the thread at minimum of 1
    if(numThreads < 1) 
        numThreads = 1; 
    //set the threads at max of 4
    if(numThreads > 4) 
        numThreads = 4;
    
    int load = (int)n/numThreads; //get the increments
    //create an array of threads bounds 
    Boundary threadBound[numThreads];
    //distribute the load among the threads 
    for(int i = 0; i < numThreads; i++){
        threadBound[i].threadNum = i;
        threadBound[i].low = i * load;
        threadBound[i].high = (i + 1) * load;
    }
    //set the last thread.high at the nth number 
    threadBound[numThreads - 1].high = n;
     //create the threads, default attr, printCatalan function, and pass the structure 
    pthread_t thread[4]; //pthread_t array of 4
    pthread_attr_t attr; //pthread default attribute
    pthread_attr_init(&attr);
    //create the threads 
    for(int i = 0; i  < numThreads; i++)
        pthread_create(&thread[i],&attr, printCatalanNumbers, (void * ) &threadBound[i]);
    //wait for all threads to finish
    for(int i =0; i < numThreads; i++)
        pthread_join(thread[i], NULL);
    //combine all files into 1
    for(int i =0; i < numThreads; i++){
        char buffer[15];
        sprintf(buffer,"file%i.dat",i); //write to buffer file name
        FILE *threadFile = fopen(buffer,"r"); //open file name as read file 
        if(threadFile == NULL){
            fprintf(stderr, "Error opening the file\n");
            return 1; 
        }
        char c = fgetc(threadFile);  //get the character of the file 
        while (c != -1) {  //iterate until End Of File 
            fputc(c, file); //write to file 
            c = fgetc(threadFile);  //get new character
        } 
        fclose(threadFile); //close the file 
    }
    fclose(file); //close the main file 
    printf("Catalan numbers stored in catalan.dat\n");
    return 1;
}
void *printCatalanNumbers(void *param){
    Boundary *threadBound = param;//implicit type cast the param to a struct *
    //iterate from the low and high of the sequence
    char buffer[14]; //buffer to set the thread filename
    sprintf(buffer,"file%i.dat",threadBound->threadNum);//set thread file name
    FILE *threadFile = fopen(buffer,"w"); //create a write file for avery different thread 
    for(int i = threadBound->low; i < threadBound->high; i++)
        fprintf(threadFile,"%d: %Lf\n",i + 1,catalanNumber(i)); //print to the file 
    fclose(threadFile);     //close the thread file 
    pthread_exit(NULL);     //exit thread
}

long double catalanNumber(int n){ 
     // Base case
    if (n <= 1)
        return 1;
    else
        return catalanNumber(n - 1) * (4*n + 2)  / (n + 2);
}