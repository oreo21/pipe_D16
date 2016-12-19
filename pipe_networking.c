#include "pipe_networking.h"

int server_handshake(int* from_client){

  printf("[SERVER] Initiating handshake...\n");
  mkfifo("WKP", 0644);
  
  printf("[SERVER] Connecting to WKP...\n");
  int wkp = open("WKP", O_WRONLY);

  printf("[SERVER] Waiting for private fifo name...\n");
  char c_fifo_name[MESSAGE_BUFFER_SIZE + 1];
  read(wkp, c_fifo_name, sizeof(c_fifo_name));
  c_fifo_name[MESSAGE_BUFFER_SIZE] = 0;
  
  int rem = remove("WKP");
  if (rem) {
    printf("[SERVER] Remove error\n");
    exit(rem);
  }
  printf("[SERVER] Removed WKP\n");
  
  int c_fifo = open(c_fifo_name, O_WRONLY);
  char *msg = "[SERVER]>>[CLIENT] Initial message\n";
  write(c_fifo, msg, sizeof(msg));
  
  printf("[SERVER] Waiting for [CLIENT] acknowledgment message...\n");
  char c_msg[MESSAGE_BUFFER_SIZE];
  read(c_fifo, c_msg, sizeof(c_msg));
  printf("[SERVER] Received message from [CLIENT]:%s\n", c_msg);
  
  *from_client = c_fifo_name;  
  return c_fifo; //to_client 
}

int client_handshake(int* to_server){
  
  char c_fifo_name[MESSAGE_BUFFER_SIZE];
  sprintf(c_fifo_name, "%d", getpid());
  
  printf("[CLIENT] Creating private pipe...\n");
  mkfifo(c_fifo_name, 0644); //private FIFO 
  
  
  printf("[CLIENT] Connecting to WKP...\n");
  int wkp = open("WKP", O_WRONLY);
  
  printf("[CLIENT] Sending private FIFO name to server...\n");
  write(wkp, c_fifo_name, sizeof(c_fifo_name));
  
  printf("[CLIENT] Connecting to private FIFO...\n");
  int c_fifo = open(c_fifo_name, O_RDONLY);

  char s_msg[MESSAGE_BUFFER_SIZE];
  read(c_fifo, s_msg, sizeof(s_msg));
  printf("[CLIENT] Received initial message from [SERVER]: %s\n", s_msg);
  
  int rem = remove(c_fifo_name);
  if (rem) {
    printf("[CLIENT] Remove error\n");
    exit(rem);
  }
  
  printf("[CLIENT] Removed private FIFO\n");

  char ack_message[] = "[CLIENT] >> [SERVER] this is a message of acknowledgment!\n";
  write(c_fifo, ack_message, sizeof(ack_message));
  
  *to_server = c_fifo_name;
  return c_fifo;
}
  
     
