#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "banking.h"

int main(int argc, char *argv[]){
    /*Check if the all the arguments where placed*/
    if(argc < 6){  
        printf("./bankClient servIPAddr servPortNum transaction acctnum value\n");
        return 1;
    }
    sBANK_PROTOCOL inProg;  //Store the arguments in the structure
    int portNum = atoi(argv[2]);    //Convert the second argument (which is the port number) into an argument

    /*Check the character in the third argument to see what the user want to do*/
    switch(argv[3][0]){
        case 'B':   //Bank inquiry
            inProg.trans = BANK_TRANS_INQUIRY;
            break;
        case 'D':   //Deposit 
            inProg.trans = BANK_TRANS_DEPOSIT;
            break;
        case 'W':   //Withdraw
            inProg.trans = BANK_TRANS_WITHDRAW;
            break;
        default:    //If the character is not as the 3 expected an error will occur which quits the code
            printf("Invalid transaction key");
            exit(0);
    }

    inProg.acctnum = atoi(argv[4]); //Convert the fourth argument (which is the accounr number) into and interger
    inProg.value = atoi(argv[5]);   //Convert the fifth argument (which is the value) into and interger
    struct sockaddr_in socketAddr;  //Socketr address

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); //Create socket
    /*Check if there was an error while creating the socket*/
    if(clientSocket < 0){
        printf("Error creating the socket");
        exit(0);    //Exit code if their was an error while creating the socket
    }

    socketAddr.sin_family = AF_INET;    //type of address family
    socketAddr.sin_port = htons(portNum);   //Port number gather from the arguments
    socketAddr.sin_addr.s_addr = inet_addr(argv[1]);    //IP Address gather from the arguments
    
    int connection = connect(clientSocket, (struct sockaddr *)&socketAddr, sizeof(socketAddr) );     //Establish connection
    
    /*Check if the conection is establish between the client and the server*/
    if(connection < 0 ){   
        printf("Failed to connect socket\n");
        exit(0);    //Exit the code if the socket fail to connect
    }
    else if(!(connection < 0)){     
        printf("Your server and your client are conected\n");
        send(clientSocket, (void*)&inProg, sizeof(inProg),0);   //Send the structure
    }
    
    sBANK_PROTOCOL serverReturn;    //Create another structure for the returned values
    recv(clientSocket, (void *)&serverReturn, sizeof(serverReturn),0);  //Receiving the result from the server
    /*For security measures, check if the account number sent is the one received*/
    if(inProg.acctnum == serverReturn.acctnum){
        printf("Account Number: %d\n", serverReturn.acctnum);
    }
    else{
        printf("Acount number Error\n");
        exit(0);    //If the account numbers don't match exit code
    } 
    /*Depending on the transaction print the received data correctly*/
    switch(serverReturn.trans){
        case 0:
            printf("Type of Transaction: Deposit\n");
            printf("Amount Deposited: %d\n", serverReturn.value);
            break;
        case 1:
            printf("Type of Transaction: Withdraw\n");
            printf("Amount Withdrew: %d\n", serverReturn.value);
            break;
        case 2:
            printf("Type of Transaction: Bank Inquiry\n");
            printf("Balance Inquiry: %d\n", serverReturn.value);
            break;
        default:
            printf("Error Ocurred when getting the transation value\n");
            break;
    }
return 0;   
}