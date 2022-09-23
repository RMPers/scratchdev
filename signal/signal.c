/* Program to illustrate the use of POSIX signals on UNIX
   The program runs a eternal loop.

   A time alarm signal is used to periodically print work time
   An interrupt signal is used for work time on demand or terminate
   A quit signal is masked together with int and alarm during execution
   of signal handlers */

#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void do_task();
void sighandler_time(int);
void sighandler_demand(int);
int time = 0;

int main() {

    sigset_t mask;
    struct sigaction action;

    /* Status Routine will handle timer and INTR */

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGALRM); // if this would not be masked the alarm would trigger
                               // sighandler_time even if sighandler_demand was running.
    sigaddset(&mask, SIGQUIT);
    action.sa_flags=0;
    action.sa_mask=mask;

    action.sa_handler=sighandler_time;
    sigaction(SIGALRM,&action,NULL);


    action.sa_handler=sighandler_demand;
    sigaction(SIGINT,&action,NULL);

    /* start alarm clock */
    alarm(7);

    do_task();
}

void do_task()
{
    while (1) {
        sleep(5);
        time+=5;
        printf("total work time %d sec\n", time);
    }
}

void sighandler_time(int signum)
{

    alarm(0); /* shutoff alarm */

    if (signum == SIGINT) printf("Interrupt ");
    if (signum == SIGALRM) printf("Timer ");

    printf("signhandler: processing time %d\n",time);

    alarm(7);	/*restart alarm*/
}

void sighandler_demand(int signum)
{
    printf("Interrupt signal %d\n", signum);
    printf("Press 0 to kill appliction. Any other key to continue...\n");
    int sel;
    scanf("%d", &sel);
    if (sel == 0)
        exit(0);

    signal(signum, SIG_DFL); // changes disposition of signal to SIG_DFL. Next time this signal will be handled
                             // by default signal handler
}

__attribute__((constructor))
static void set_init_values()
{
    time=30;
}
