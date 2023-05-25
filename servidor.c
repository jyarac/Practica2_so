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
#include <time.h>
#include <arpa/inet.h>
// Definición de la estructura de datos para almacenar la información de tiempos de viaje

//create a function called ingresar origen that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
#define PORT 3535
#define BUFFER_SIZE 200


void guardarRegistro(char *registro, char *nombreArchivo) {
    FILE *archivo;

    // Abrir el archivo en modo adjunto (append)
    if ((archivo = fopen(nombreArchivo, "a")) != NULL) {
        // Escribir el registro en el archivo
        fprintf(archivo, "%s\n", registro);

        // Cerrar el archivo
        fclose(archivo);
        printf("Consulta satisfactoria.\n");
    } else {
        printf("No se pudo abrir el archivo para guardar el registro.\n");
    }
}


int main() {
    

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


    // Accept an incoming connection
    int clientSocket;
    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    //stay accepting connections

    while (1==1){
    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t *)&clientAddressSize)) < 0) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }
    // Receive data from client
    char buffer[BUFFER_SIZE];
    //obtaining client ip
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), clientIP, INET_ADDRSTRLEN);


    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead < 0) {
        perror("Receiving data failed");
        exit(EXIT_FAILURE);
    }

        //formatting the log
    char registro[100];
    char nombreArchivo[] = "log.txt";
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    strftime(registro, sizeof(registro), "[%Y%m%dT%H%M%S]", now);
    strcat(registro, "Cliente [");
    strcat(registro, clientIP);
    strcat(registro, "] [");
    strcat(registro, buffer);
    strcat(registro, "]");

    int numbers[3];
    char *token = strtok(buffer, " ");
    int i = 0;
    while (token != NULL && i < 3) {
        numbers[i] = atoi(token);
        i++;
        token = strtok(NULL, " ");
    }
    //print numbers
    double travel_time = search(numbers[0], numbers[1], numbers[2]);
    //send data to client
    char response[BUFFER_SIZE];
    sprintf(response, "%f", travel_time);
    send(clientSocket, response, strlen(response), 0);
    
    //search for the data in the hash table
    //saving log history
        FILE *file;
    char *file_name = "log.txt";

    // Abrir el archivo

    // Obtener la fecha y hora actual

    // Formatear la fecha y hora actual

    // Guardar el registro en el archivo
    guardarRegistro(registro, nombreArchivo);


      }  
    close(clientSocket);
    close(serverSocket);

    return 0;
}



 

