# Minitalk Project

Minitalk is a unique communication system built on UNIX signals. This lightweight server-client application allows for a simple and direct means of interprocess communication through customized handling of SIGUSR1 and SIGUSR2 signals.

----
## Features

- Lightweight server-client communication
- Character encoding and decoding through signal handling
- Support for handling simultaneous client connections
- Real-time communication through UNIX signals
- Error handling for unexpected input scenarios

----
## Compilation

To compile the project, run the following command in your terminal:

````
git clone https://github.com/jmbertin/Minitalk
cd Minitalk
make all
````

This command builds both the server and client executables.

You can build server and client separetly :
````
make server
make client
````

----

## Usage

To start the server, run:

````
./server
````

You will be presented with the server's PID, which is necessary for the client to send messages to the server.

To send a message from the client to the server, run:

````
./client [SERVER_PID] [MESSAGE]
````
Replace **[SERVER_PID]** with the server's PID displayed upon startup, and **[MESSAGE]** with the actual message you wish to send.

For example:

````
./client 12345 "Hello, world!"
````

----

## Understanding the Code

**Server**
The server is designed to continually listen for signals and assemble them into characters, displaying each character as it is completed and recognizing the end of a message when it encounters a null character ('\0').

**Client**
The client translates each character of the input message into a series of signals that represent the binary value of each character. It sends these signals to the server and waits for acknowledgment between each character to ensure synchronization.

**Debugging and Testing**
A set of debugging and testing scripts are included to help you verify that the server and client are functioning correctly. Run the test scripts using:

````
chmod +x tests.sh
./tests.sh
````

----

## Contribution
Feel free to fork the project and submit your contributions through pull requests. We appreciate any contributions to improve the project!
