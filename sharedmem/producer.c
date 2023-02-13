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
    const int cmd = IPC_STAT;
    struct shmid_ds ds;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0 ) {
        perror("producer: shmget");
        shmctl(shmid,cmd,&ds);
        return -1;
    }
    
    m = (struct data *)shmat(shmid,NULL,0);

    if (m < 0) {
        perror("producer: shmat");
        return -1;
    }

    for (int i = 0; i < 10; i++)
    {
        m->data0 = i;
        m->data1 = i*10;
        m->data2 = i*20;
        sleep(1);
    }
    return 0;
}
