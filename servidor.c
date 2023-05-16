#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>

// Definición de la estructura de datos para almacenar la información de tiempos de viaje

//create a function called ingresar origen that receives a pointer to a integer and wait for input,verifies if the input is between 1 and 1160, the input is saved on the integer else it prints an error message




int main() {
    
    //create a if statement that verifies if the file hash.bin exist if it does, it calls hashDocument function with parameters datos.csv, hash.bin and 1160, else it calls hashDocument function with parameters datos.csv, hash.bin and 1160
    hashDocument();
    //print document hashed
    printf("Document hashed\n");
    //start server 

}

 

