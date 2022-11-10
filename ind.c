#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
 void int_handler(int sig);

 if(signal(SIGINT, int_handler) == SIG_ERR)
 {
  perror("signal SIGINT");
  exit(1);
 }
 while(1)
 {
  int pipefds[2];
  char mes[100];

  pipe(pipefds);

  pid_t id = fork();

  if(id == 0)
  {
   close(pipefds[0]);
   write(pipefds[1], mes, sizeof(mes));
   printf("\nThe message from parent : %s\n", mes);
   exit(EXIT_SUCCESS);
  }
  if(id > 0)
  {
   wait(NULL);
   close(pipefds[1]);
   read(pipefds[0], mes, sizeof(mes));
   close(pipefds[0]);
   printf("\nEnter a message : ");
   scanf("%s", mes);
  }
 }
return EXIT_SUCCESS;
}

void int_handler(int sig)
{
 printf("Process immediately terminated\n");
}
