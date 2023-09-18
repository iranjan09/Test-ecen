#  Network Programming Assignment 1 - TCP Echo Server and Client

## Introduction

This project implements a simple TCP echo service consisting of a server and a client. The server listens for incoming connections and echoes back whatever it receives from clients. Clients can send text to the server and receive the echoed text.

## Team Members

### Aneesh Dixit
- **UIN:** 530006593 
- **Contributions:**  
  - Implemented the server logic and readline function
  - Created and executed test cases.
  - Developed the report
      
### Ishan Ranjan
- **UIN:** 833002748
- **Contributions:**
  - Implemented the client logic and written function
  - Developed the Makefile and Readme.md
  - Generated the chatGPT code 

## Files

### Server (server.c)

- The server is started using the command: `echos <Port>`, where `Port` is the port number on which the server listens.
- The server supports multiple simultaneous connections.
- When a client connects, the server echoes back any text received from the client.
- When a client closes its socket (e.g., after receiving an EOF), the server child process gracefully exits.

### Client (client.c)

- The client is started using the command: `echo <IP Address> <Port>`, where `IP Address` is the IPv4 address of the server, and `Port` is the server's port number.
- The client reads a line of text from its standard input and sends it to the server.
- The client then receives the echoed line from the server and prints it to its standard output.
- The client continues this loop until it reads an EOF from its standard input (e.g., Control-D), at which point it closes the socket and exits gracefully.

### `common.c`

- Contains common functions used by both the server and client.
- Includes functions for reading and writing data on sockets.

### `common.h`

- Header file with function declarations and constants used across the codebase.

## Directory Structure

- `bin`: Contains the binary executables.
- `include`: Contains the `common.h` file.
- `obj`: Contains the object files.
- `src`: Contains the source code files.

## Building and Running

1. Navigate to the project directory.

2. Clean the project (optional): make clean

3. Compile the code and generate binaries: make -f Makefile

4. To run the server, use the following command (replace Port with the desired port number): 
   `/echos <Port>`

5. To run the client, use the following command (replace IP Address and Port with the server's IP address and port number):
   `./echo <IP Address> <Port>`
