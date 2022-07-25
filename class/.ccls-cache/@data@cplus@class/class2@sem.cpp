#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct
{
    sem_t *lock;
    int num;
} STRUCT;

void *test(void *obj)
{
    STRUCT *point = (STRUCT *)obj;
    sem_t *semlock = point->lock;
    sem_wait(semlock);
    FILE *f = fopen("test.txt", "a");
    if (f == NULL)
        printf("fopen is wrong\n");
    printf("sem_wait %d\n", point->num);
    int j = 0;
    for (j = 0; j < 30; j++)
        fprintf(f, "%c111111111111\n", 'a' + point->num);
    fclose(f);
    sem_post(semlock);

    return nullptr;
}

int main()
{
    pthread_t pid[20]; //  pthread_t pid;
    int ret, i = 0;
    STRUCT obj[13];
    sem_t semlock;
    if (sem_init(&semlock, 0, 1) != 0) // 此处初始信号量设为1. 第二个参数为0表示不应用于其他进程。
        printf("sem_init is wrong\n");
    for (i = 0; i < 10; i++)
    {
        obj[i].num = i;
        obj[i].lock = &semlock;
        ret = pthread_create(&pid[i], NULL, test, &obj[i]);

        if (ret != 0)
        {
            printf("create thread wrong %d!!\n", i);
            return 0;
        }
    }
    for (i = 0; i < 10; i++)
    {
        printf("here is main thread\n");
        pthread_join(pid[i], NULL); // 等待其他线程结束，如果没有这里，主线程先结束，会释放pid[]及obj[]，则出现BUG。
    }
    // pthread_detach(pid[i]);
    return 0;
}