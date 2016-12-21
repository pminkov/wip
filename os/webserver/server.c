/*

Based on this:
http://pages.cs.wisc.edu/~dusseau/Classes/CS537-F07/Projects/P2/p2.html

*/
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>

#include "threads.h"

void error(char *message) {
  perror(message);
  exit(1);
}

void writeln_to_sock(int sockfd, char *message) {
  write(sockfd, message, strlen(message));
  write(sockfd, "\r\n", 2);
}

char *concat(char *s1, char *s2) {
  char *res = malloc(strlen(s1) + strlen(s2) + 1);
  strcpy(res, s1);
  strcat(res, s2);
  return res;
}

void http_get_reply(int sockfd) {
  char *content = "<html><body><h1>PetkoWS</h1></body></html>\r\n";

  char length_str[100];
  sprintf(length_str, "%d", (int)strlen(content));

  char *content_length_str = concat("Content-Length: ", length_str);

  writeln_to_sock(sockfd, "HTTP/1.1 200 OK");
  writeln_to_sock(sockfd, "Server: PetkoWS/1.0 (MacOS)");
  writeln_to_sock(sockfd, "Content-Type: text/html");
  writeln_to_sock(sockfd, content_length_str);
  writeln_to_sock(sockfd, "");
  writeln_to_sock(sockfd, content);

  free(content_length_str);

  //printf("Sleeping...\n");
  //sleep(3);
}

char *read_text_from_socket(int sockfd) {
  char *buffer = malloc(1024);

  int n = read(sockfd, buffer, 1023);
  if (n < 0) error("Error reading from socket");
  buffer[n] = '\0';

  printf("From socket: %s\n\n", buffer);

  return buffer;
}


void *handle_socket_thread(void* sockfd_arg) {
  int sockfd = *((int *)sockfd_arg);

  printf("Handling socket: %d\n", sockfd);
  
  char *text = read_text_from_socket(sockfd);
  free(text);

  http_get_reply(sockfd);

  close(sockfd);
  return NULL;
}


void handle_socket(int sockfd) {
  pthread_t thread;

  Pthread_create(&thread, NULL, handle_socket_thread, &sockfd);
}


int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }

  struct sockaddr_in serv_addr;

  int port = 8000;

  while (1) {
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      port++;
    } else {
      break;
    }
  }

  printf("Running on port: %d\n", port);

  if (listen(sockfd, 5) < 0) error("Couldn't listen");

  struct sockaddr_in client_addr;
  int cli_len = sizeof(client_addr);

  while (1) {
    int newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &cli_len);
    if (newsockfd < 0) error("Error on accept");
    printf("New socket: %d\n", newsockfd);
    handle_socket(newsockfd);

  }

  close(sockfd);

  return 0;
}
