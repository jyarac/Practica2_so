#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// Definición de la estructura de datos para almacenar la información de tiempos de viaje

//create a function called ingresar origen that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
#define PORT 3535
#define BUFFER_SIZE 200


int main() {
    
    //create a if statement that verifies if the file hash.bin exist if it does, it calls hashDocument function with parameters datos.csv, hash.bin and 1160, else it calls hashDocument function with parameters datos.csv, hash.bin and 1160
    hashDocument();
    //print document hashed
    printf("Document hashed\n");
    //creating a socket and initializing it|
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept an incoming connection
    int clientSocket;
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    while (1==1){
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressSize)) < 0) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }


    // Receive data from client
    char buffer[BUFFER_SIZE];
    //print buffer
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead < 0) {
        perror("Receiving data failed");
        exit(EXIT_FAILURE);
    }

    printf("Received data from client: %s\n", buffer);
    int numbers[3];
    char *token = strtok(buffer, " ");
    int i = 0;
    while (token != NULL && i < 3) {
        numbers[i] = atoi(token);
        i++;
        token = strtok(NULL, " ");
    }
    //print numbers
    search(numbers[0], numbers[1], numbers[2]);
    //search for the data in the hash table
    //if the data is found send the data to the client
    //else send a message to the client that the data was not found
    //send data to client

      }  
    close(clientSocket);
    close(serverSocket);

    return 0;
}



 

