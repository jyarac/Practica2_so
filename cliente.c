#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 3535
#define BUFFER_SIZE 200
void peticion_servidor( int sourceid, int dstid, int hod) {
    // Set up server address
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    // Convert IP address from string to binary form
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        perror("Dirección inválida/No compatible");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error al conectar");
        exit(EXIT_FAILURE);
    }

    printf("Conectado al servidor\n");

    // Send dstid, sourceid and hod to server
    char message[BUFFER_SIZE];
    sprintf(message, "%d %d %d",sourceid, dstid, hod);

    ssize_t bytesSent = send(clientSocket, message, strlen(message), 0);
    if (bytesSent < 0) {
        perror("Error al enviar los datos");
        exit(EXIT_FAILURE);
    }

    // Close the socket
    close(clientSocket);
}
void ingresar_origen(int* sourceid) {

    int input;
    printf("Ingrese ID del origen:");
    scanf("%d", &input);
    if (input >= 1 && input <= 1160) {
        *sourceid = input; // save input #include <unistd.h>

    } else {
        printf("Error: el valor ingresado no está entre 1 y 1160.\n");
    }
}
//create a function called ingresar destino that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message
void ingresar_destino(int* dstid) {
    int input;
    printf("Ingrese ID del destino:");
    scanf("%d", &input);
    if (input >= 1 && input <= 1160) {
        *dstid = input; // save input to the integer pointed by ptr
    } else {
        printf("Error: el valor ingresado no está entre 1 y 1160.\n");
    }
}
//create a function called ingresar hora that receives a pointer to a integer and wait for input,verifies if the input is between 0 and 23, the input is saved on the integer else it prints an error message
void ingresar_hora(int* hod) {
    int input;
    printf("Ingrese hora del dia:");
    scanf("%d", &input);
    if (input >= 0 && input <= 23) {
        *hod = input; // save input to the integer pointed by ptr
    } else {
        printf("Error: el valor ingresado no está entre 0 y 23.\n");
    }
}
int main() {
    int option;
    int sourceid;
    int dstid;
    int hod;
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Llamar a la función para establecer la conexión con el servidor


    while (option != 5) {
        printf("Bienvenido\n");
        printf("1. Ingresar origen\n");
        printf("2. Ingresar destino\n");
        printf("3. Ingresar hora\n");
        printf("4. Buscar tiempo de viaje medio\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &option);
    switch (option) {
            case 1:
             ingresar_origen(&sourceid);
                break;
            case 2:

                ingresar_destino(&dstid);
                break;
            case 3:

                ingresar_hora(&hod);
                break;
            case 4:
                peticion_servidor(sourceid, dstid, hod);
                break;
            case 5:

                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
                break;
        }
    }
}
