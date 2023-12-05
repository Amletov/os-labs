#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>


#define SHMSZ     27    

int main() {

    char c;
    int shmid;
    key_t key = 234156;
    char *shm, *s;
    

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(-1);
    }

    struct shmid_ds shminfo;
    if (shmctl(shmid, IPC_STAT, &shminfo) == -1) {
        perror("shmctl");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }



    // Выводим PID последнего присоединившегося процесса
    printf("[%d]Последний присоединившийся процесс: %d\n", getpid(), shminfo.shm_lpid);

    

    return 0;
}

