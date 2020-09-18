/*
2 threads one producer one consumer
with global array producer will write
consumer will read it and print
*/

#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

char buffer[2] = "\0"; //string that the producer will write and consumer will read
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
char var;
int flag = 0;

void *producer()
{
    char str[100] = "doing this for lab\n";
    int j = 0;
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        //printf("%ld\n", strlen(str));
        for (j = 0; j <= i; j++)
        {
            buffer[j] = str[i];

            while (var != '\0')
            {
                sleep(1);
            }

            pthread_mutex_lock(&mtx); //only one thread at the time
            var = buffer[j];
            pthread_mutex_unlock(&mtx); //once consumer read than Unlock mutex and procee
        }
    }
    flag = 1;
}

void *consumer()
{
    while (flag == 0)
    {
        pthread_mutex_lock(&mtx); //only one thread at the time
        printf("%c", var);        //prints what was read
        var = '\0';
        *buffer = '\0';
        fflush(stdout);

        pthread_mutex_unlock(&mtx); //Unlock mutex
    }
}

int main(int argc, char *argv)
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, producer, NULL); //creating the threads
    pthread_create(&thread2, NULL, consumer, NULL);

    pthread_join(thread1, NULL); //Wait for threads to finish
    pthread_join(thread2, NULL);
}
