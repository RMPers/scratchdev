#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

#define KEYID 5679
#define SHMSZ (sizeof(struct data))

struct data {
        int data0;
        int data1;
        int data2;
};

int main (void)
{
    struct data* m;
    int shmid;
    key_t key = KEYID;
    struct shmid_ds ds;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0 ) {
        perror("shmget");
        shmctl(shmid, IPC_RMID, &ds);
        return -1;
    }
    else
    {
        printf("shared mem succeesfull id=%d\n", shmid);
    }

    if (shmctl(shmid, IPC_STAT, &ds) < 0)
    {
        perror("shmctl");
        return -1;
    }

    m = (struct data *)shmat(shmid,NULL,0);

    for (;;)
    {
        printf("data=%d,%d,%d\n", m->data0, m->data1, m->data2);
        sleep(2);
    }
    return 0;
}
