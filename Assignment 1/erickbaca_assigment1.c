/* Author: Erick A. Baca
 * Date:September 14, 2021
 * EE 5370 Operating Systems
 * Assigment #1
 */
#include <sys/wait.h>
#include <sys/types.h>  
#include <unistd.h>     
#include <stdlib.h>
#include <stdio.h>


static char *commands[4][3] = {{"cat", "/proc/meminfo", NULL},     //3D array for the commands
                                {"uname", "-a", NULL},
                                {"ls", "-l", NULL},
                                {"echo", "4th process", NULL}};

int main(int argc, char *argv[]){
    pid_t child[4];             //create 4 pid_t for each child of the parent
    for(int i =0; i < 3; i++){  //iterate over the first 3 childs 
        child[i] = fork();      //fork a child
        if(child[i] < 0){       //if the child is negative, exit program
            fprintf(stderr,"Error forking a process\n"); 
            return -1; 
        }
        else if(child[i] == 0)  //if the child is 0, then execute program 
            execlp(commands[i][0], commands[i][0], commands[i][1], commands[i][2]);
        else 
            waitpid(child[i] ,NULL, 0); //as the parent wait for the childs to end
    }
    /*When child 3 finishes, it will start a process echo and it will say good 
    bye without waiting for the previous process */

    child[3] = fork();          //fork the fourth child 
    if(child[3] < 0){           //if the child is negative, exit program
        fprintf(stderr,"Error forking a process\n");
        return -1;              
    }
    else if( child[3] == 0)     //if the last child pid is 0, then execute program
        execlp(commands[3][0], commands[3][0], commands[3][1], commands[3][2]);
    else 
        printf("Goodbye!\n");  //dont wait for the last process to end
    return 0;
}