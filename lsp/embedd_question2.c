#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define WORK_SIZE 64
#define MAX_CHAR 50
#define MAX_USER_INPUT 100
#define DEBUG 0 // DEBUG is 0 to disable, and 1 to enable

char work_area[WORK_SIZE];
char buff[MAX_CHAR];

char *file = "/tmp/file.txt";
unsigned char flag_end;

sem_t flag_append, flag_remove;

void rand_str(char *, size_t);
void *thread_append(void *arg);
void *thread_remove(void *arg);

void rand_str(char *dest, size_t length)
{
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0)
    {
        size_t index = (double)rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

int main()
{
    int res;
    pthread_t a_thread, r_thread;
    void *thread_result;
    char user_input[MAX_USER_INPUT];

    res = sem_init(&flag_append, 0, 0);
    if (res != 0)
    {
        perror("Semaphore flag_append initialization failed");
        exit(EXIT_FAILURE);
    }
    res = sem_init(&flag_remove, 0, 0);
    if (res != 0)
    {
        perror("Semaphore flag_remove initialization failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&a_thread, NULL, thread_append, NULL);
    if (res != 0)
    {
        perror("thread_append creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&r_thread, NULL, thread_remove, NULL);
    if (res != 0)
    {
        perror("thread_remove creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Input some text. Enter 'end' to finish\n");
    while (strncmp("end", user_input, 3) != 0)
    {
#if (DEBUG)
        printf("%d:thread_main\n", __LINE__);
#endif
        fgets(user_input, MAX_USER_INPUT, stdin);
        usleep(1000000);
    }
    pthread_cancel(a_thread);
    pthread_cancel(r_thread);
#if (DEBUG)
    printf("\nWaiting for a_thread to finish...\n");
#endif
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("a_thread join failed");
        exit(EXIT_FAILURE);
    }
#if (DEBUG)
    printf("a_thread joined\n");
    printf("\nWaiting for r_thread to finish...\n");
#endif
    res = pthread_join(r_thread, &thread_result);
    if (res != 0)
    {
        perror("r_thread join failed");
        exit(EXIT_FAILURE);
    }
#if (DEBUG)
    printf("r_thread joined\n");
#endif
    exit(EXIT_SUCCESS);
}

void *thread_append(void *arg)
{
    unsigned char appended = 1;
    sem_post(&flag_append);
    while (1)
    {
#if (DEBUG)
        printf("%d:thread_append\n", __LINE__);
#endif
        sem_wait(&flag_append);
        if (appended == 1)
        {
            rand_str(buff, rand() % MAX_CHAR);
        }
#if (DEBUG)
        printf("%d:buff=%s,buff_len=%d\n", __LINE__, buff, strlen(buff));
        printf("%d:work_area=%s,work_area_len=%d\n", __LINE__, work_area, strlen(work_area));
#endif
        if ((strlen(work_area) + strlen(buff)) < sizeof(work_area))
        {
            strcat(work_area, buff);
            appended = 1;
            sem_post(&flag_append);
        }
        else
        {
            usleep(100000);
            appended = 0;
            sem_post(&flag_remove);
        }
#if (DEBUG)
        printf("%d:work_area=%s,len=%ld\n", __LINE__, work_area, strlen(work_area));
        printf("\n");
#endif
        usleep(100000);
    }
    // pthread_exit(NULL);
}

void *thread_remove(void *arg)
{
    int fd;
    fd = creat(file, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd < 0)
    {
        printf("error in creating or writing a file\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        sem_wait(&flag_remove);
#if (DEBUG)
        printf("%d:thread_remove,work_area_len=%d\n", __LINE__, strlen(work_area));
#endif
        write(fd, work_area, strlen(work_area));
        write(fd, "\n", 1);
        strcpy(work_area, "");
        usleep(100000);
        sem_post(&flag_append);
    }
}