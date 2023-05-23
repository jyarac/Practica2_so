# Client and server communitacion
the server hashes a uber dataset with travel times between many destinations, at various hours of the day.
the server starts a socket that receives every time travel request

the client starts a socket, the receive the origin, destination and hour of the day, then launch a petition for the server
the server receives the petition with the parameters and searches in the hash table the correspondent mean travel time for that parameters
