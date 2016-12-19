#include "pipe_networking.h"

int server_handshake(int* from_client){

  printf("[SERVER] Initiating handshake...\n");
  mkfifo("WKP", 0644);
  
  printf("[SERVER] Connecting to WKP...\n");
  *from_client = open("WKP", O_RDONLY);

  printf("[SERVER] Waiting for private fifo name...\n");
  char c_fifo_name[MESSAGE_BUFFER_SIZE];
  read(*from_client, c_fifo_name, MESSAGE_BUFFER_SIZE);
  
  int rem = remove("WKP");
  printf("[SERVER] Removed WKP\n");
  
  int to_client = open(c_fifo_name, O_WRONLY);
  
  char *msg = "[SERVER]>>[CLIENT] Initial message\n";
  
  write(to_client, msg, sizeof(msg));
  
  return to_client; //to_client 
}

int client_handshake(int* to_server){
  char c_fifo_name[MESSAGE_BUFFER_SIZE];
  sprintf(c_fifo_name, "%d", getpid());
  
  printf("[CLIENT] Creating private pipe...\n");
  mkfifo(c_fifo_name, 0644); //private FIFO 
  
  
  printf("[CLIENT] Connecting to WKP...\n");
  *to_server = open("WKP", O_WRONLY);
  
  printf("[CLIENT] Sending private FIFO name to server...\n");
  write(*to_server, c_fifo_name, sizeof(c_fifo_name));
  
  printf("[CLIENT] Connecting to private FIFO...\n");
  int from_server = open(c_fifo_name, O_RDONLY);

  printf("[CLIENT] Connection established!\n");

  char s_msg[MESSAGE_BUFFER_SIZE];
  read(from_server, s_msg, MESSAGE_BUFFER_SIZE);
  
  int rem = remove(c_fifo_name);
  printf("gotcha! %s\n", s_msg);
  
  return from_server;
}
  
     
