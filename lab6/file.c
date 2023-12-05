#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 27

int main() {
    char c;
    int shmid;
    
    // Уникальный ключ для создания разделяемой области памяти
    key_t key = 234156;

    // Указатель на разделяемую память
    char *shm;

    // Создаем или получаем идентификатор разделяемой области памяти
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(-1);
    }

    // Структура для хранения информации о разделяемой области памяти
    struct shmid_ds shminfo;

    // Получаем информацию о разделяемой области памяти
    if (shmctl(shmid, IPC_STAT, &shminfo) == -1) {
        perror("shmctl");
        exit(1);
    }

    // Присоединяем разделяемую область памяти к адресному пространству процесса
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Выводим PID текущего процесса и PID последнего присоединившегося процесса
    printf("[%d] Последний присоединившийся процесс: %d\n", getpid(), shminfo.shm_lpid);

    return 0;
}
