#include <pthread.h>
#include <unistd.h>
#include <cstdio>

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

int r = 0;

void* provider(void* param)
{
    while (true) {
        pthread_mutex_lock(&mute);
        if (r == 1) {
            pthread_mutex_unlock(&mute);
            continue;
        }
        r = 1;
        printf("provide\n");
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mute);
        sleep(1);
    }
}

void *consumer(void *param)
{
    while (true) {
        pthread_mutex_lock(&mute);
        while (r == 0) {
            pthread_cond_wait(&condition, &mute);
        }
        r = 0;
        printf("consume \n");
        pthread_mutex_unlock(&mute);
    }
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, nullptr, consumer, nullptr);
    pthread_create(&t2, nullptr, provider, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    pthread_mutex_destroy(&mute);
    pthread_cond_destroy(&condition);

    return 0;
}

