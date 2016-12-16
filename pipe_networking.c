#include "pipe_networking.h"

int server_handshake(int* fromClient){
  mkfifo("mario", 0644); //WKP
  printf("server_handshake called\n");
}

int client_handshake(int* toServer){
  printf("client_handshake called\n");
  
  char priName[6] = "luigi";
  mkfifo(priName, 0644); //private FIFO  

  int fd = open("mario", O_WRONLY);
  write(fd, priName, sizeof(priName));
  
}
  
     
