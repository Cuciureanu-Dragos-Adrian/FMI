#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>



/*
	Steps for creating a daemon:

1.	fork off the parent process & let it terminate if forking was successful. -> Because the parent process has terminated, the child process now runs in the background.

2.	setsid - Create a new session. The calling process becomes the leader of the new session and the process group leader of the new process group. The process is now detached from its controlling terminal.

3.	catch signals - Ignore and/or handle signals.

4.	fork again & let the parent process terminate to ensure that you get rid of the session leading process. 

5.	chdir - Change the working directory of the daemon.

6.	umask - Change the file mode mask according to the needs of the daemon.

7.	close - Close all open file descriptors that may be inherited from the parent process.
*/


static void create_daemon()
{
    pid_t pid;

    // fork off the parent process
    pid = fork();

    // error check
    if (pid < 0)
        exit(EXIT_FAILURE);

    // success: Let the parent terminate
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // on success: The child process becomes session leader
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    // catch, ignore and handle signals
    //TODO: Implement a working signal handler
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // fork off for the second time
    pid = fork();

    // an error occurred
    if (pid < 0)
        exit(EXIT_FAILURE);

    // success: Let the parent terminate
    if (pid > 0)
        exit(EXIT_SUCCESS);

    // set new file permissions
    umask(0);

    // change the working directory to the root directory
    // chdir("/");

    // close all open file descriptors
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
    {
        close (x);
    }
    
    FILE* fp = fopen("./test.txt", "w");

	fprintf(fp, "%d", getpid());

	fclose(fp);
}


int main()
{
    create_daemon();

    while (1)
    {
    	sleep(30);
    	
        break;
    }

    return EXIT_SUCCESS;
}

