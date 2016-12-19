#include "pipe_networking.h"

int server_handshake(int* from_client){

  printf("[SERVER] Initiating handshake (WKP created)...\n");
  mkfifo("WKP", 0644);
  
  printf("[SERVER] Connecting to WKP...\n");
  int wkp = open("WKP", O_WRONLY);

  printf("[SERVER] Waiting for private fifo name...\n")
  char c_fifo_name[512];
  read(wkp, c_fifo_name, sizeof(c_fifo_name));
  
  int rem = remove("WKP");
  if (rem) 
    printf("[SERVER] Remove error\n");
  
  int c_fifo = open(c_fifo_name, O_WRONLY);
  char *msg = "[SERVER]>>[CLIENT] Initial message\n";
  write(c_fifo, msg, sizeof(msg));
  
  printf("[SERVER] Waiting for [CLIENT] acknowledgment message\n");
  char c_msg[512];
  read(c_fifo, c_msg, sizeof(c_msg));
  printf("[SERVER] Received message from [CLIENT]:%s\n", c_msg);
 
  *from_client = c_fifo_name;  
  return c_fifo; //to_client 
}

int client_handshake(int* toServer){
  
  printf("[CLIENT] Creating private pipe...\n");
  mkfifo("PRI", 0644); //private FIFO 
  
  printf("[CLIENT] Connecting to WKP...\n");
  int fd = open("WKP", O_WRONLY);
  
  write(fd, "PRI", sizeof("PRI") + 1);
  
  char readin[256];
  read("PRI", readin, sizeof(readin));
  printf("received: %s\n", readin);
  
  //sending message to server
  
  
  
}
  
     
