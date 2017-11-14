#include  <stdio.h>
#include  <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#define MAXLINE 80
void  split(char *input, char **args)
{
     while (*input != '\0') {       /* if not the end of line ....... */ 
          while (*input == ' ' || *input == '\t' || *input == '\n')
               *input++ = '\0';     /* replace white spaces with 0    */
          *args++ = input;          /* save the argument position     */
          while (*input != '\0' && *input != ' ' && 
                 *input != '\t' && *input != '\n') 
               input++;             /* skip the argument until ...    */
     }
     *args = '\0';                 /* mark the end of argument list  */
}
     
void  runinput(char **args)
{
     pid_t  pid;
     int    status;
     
     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*args, args) < 0) {     /* execute the command  */
               printf("ERROR: Invalid Command\n");
               exit(1);
          }
     }
     else {                                  /* for the parent:      */
          while (wait(&status) != pid)       /* wait for completion  */
               ;
     }
}

void selectfunc(char **args)
{

DIR *dir;
struct dirent *ent;
int count = 1;
char path[100];
sleep(1);
printf("\n[ NOTE: TYPE '.' FOR CURRENT FILE PATH ]\n\n");
sleep(1);
printf("FILE PATH  --> ");
scanf("%s",&path);
if ((dir = opendir (path)) != NULL) {
  /* print all the files and directories within directory */
  printf("\n Files in the Current directory:\n");
  while ((ent = readdir (dir)) != NULL) {
    printf ("\n%d. %s\n", count, ent->d_name);
    count++;
  }
  closedir (dir);
  runfunc(args);
} else {
  /* could not open directory */
  perror ("");
  printf("\n ERROR: No files found!\n");
}
}

void runfunc(char **args)
{
int val;
printf("\nWhich program you would like to execute? ");
scanf("%d",&val);
if(val == 2)
{
printf("\n you've chose PROJECT1.C to execute\n");
sleep(1);
exec_prog(args);
sleep(1);
}
else if(val == 3)
{
printf("\n you've chose PROJECT2.C to execute\n");
sleep(1);
exec_prog(args);
sleep(1);
}
else if(val == 4)
{ 
printf("\n you've chose PROJECT3.C to execute\n");
sleep(1);
char argm[MAXLINE] = "project3.c";
exec_prog(argm);
sleep(1);
}
else if(val == 5)
{
printf("\n you've chose PROJECT4.C to execute\n");
sleep(1);
exec_prog(args);
sleep(1);
}
else if((val == 0) || (val == 1))
{
sleep(1);
printf("\nEnter a valid choice. TRY AGAIN!\n");
}
else
{
sleep(1);
printf("\n Sorry, Try again!\n");
}

}

int exec_prog(char **argv)
{
    pid_t   my_pid;
    int     status, timeout /* unused ifdef WAIT_FOR_COMPLETION */;

    if (0 == (my_pid = fork())) {
            if (-1 == execve(argv[0], (char **)argv , NULL)) {
                    perror("\nchild process execution failed [%m]");
			printf("\n");
                    return -1;
            }
    }

#ifdef WAIT_FOR_COMPLETION
    timeout = 1000;

    while (0 == waitpid(my_pid , &status , WNOHANG)) {
            if ( --timeout < 0 ) {
                    perror("timeout");
                    return -1;
            }
            sleep(1);
    }

    printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
            argv[0], WEXITSTATUS(status), WIFEXITED(status), status);

    if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
            perror("%s failed, halt system");
            return -1;
    }

#endif
    return 0;
}
     
int  main(void)
{
     char  input[MAXLINE];             /* the input line                 */
     char  *args[MAXLINE];              /* the command line argument      */
     time_t t;
     int should_run=1;

        time(&t);
        sleep(1);
	
	printf("\n\n\n\n");
        printf("\nUBOS Shell code copyright © Abul Hasan | UBID# 1011913.\n");
        sleep(1);
        printf("\nInitializing UBOS Shell...\a\t");
        printf("[100%]\n");
        sleep(1);
        printf("Including the header files...\t");
        printf("[100%]\n");
        sleep(1);
        printf("Loading main() function...\t");
        printf("[100%]\n");
        sleep(1);
        printf("Allocating spaces...\t\t");
        printf("[100%]\n");
        sleep(1);
        printf("Compiling the code...\t\t");
        printf("[100%]\n\n");
        sleep(1);
        printf("Shell successfully loaded at %s\n", ctime(&t));
     
     while (should_run) {                   /* repeat until done ....         */
          printf("UBOS > ");     /*   display a prompt             */
          gets(input);              /*   read in the command line     */
          printf("\n");
          split(input, args);       /*   parse the line               */
          if (strcmp(args[0], "exit") == 0)  /* is it an "exit"?     */
               exit(0);            /*   exit                */
	  else if(strcmp(args[0], "selection") == 0)
	  {
		selectfunc(args);
	  }
          else
		runinput(args);           /* otherwise, execute the command */
     }
return 0;
}

