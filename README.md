# Hashing, client and server communication
this project is an example of server configuration and petition management.
uses a uber dataset with travel times between many destinations, at various hours of the day
Hash the dataset in order to make faster petitions.

the project has 3 important files
hash.h
server.c
client.c

hash.h is the library, has all the code related to the creation and consulting to the hashmap.

server.c initially hashes the uber dataset
this hash will store every possible petition.
the server starts a socket that receives every time travel request

client.c starts a socket, the receive the origin, destination and hour of the day, then launch a petition for the server
the server receives the petition with the parameters and searches in the hash table the correspondent mean travel time for that parameters
