#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

typedef struct node
{
    int weird_number;
    char *text;
    struct node *next_node;
} node_t;

pthread_t *consumers;
pthread_t producer;

sem_t semaphore;
pthread_mutex_t lock_insert, lock_stdout;

node_t *head = NULL;
node_t *tail = NULL;

int prod_alive = 0;
long int N = 0;
int in_list = 0;

void push_to_list(int number, char *text);
void *loop_push_to_list();
void *producer_work(void *arg);
void *consumer_work(void *arg);
int init(int argc, char **argv);

int main(int argc, char **argv)
{
    void *ret, *ret1;
    int return_val = 0;
    int sem_val;

    if (init(argc, argv) != 0)
    {
        fprintf(stderr, "Error occurred during initialization.\n");
        free(consumers);
        exit(1);
    }

    // create a producer thread
    pthread_create(&producer, NULL, producer_work, NULL);

    long num_of_consumer = 1;
    // create N consumer threads
    for (int i = 0; i < N; i++)
    {
        pthread_create(&consumers[i], NULL, consumer_work, (void *)num_of_consumer);
        num_of_consumer++;
    }

    // check if there wasn't an error in the producer's starting routine function
    pthread_join(producer, &ret);
    if (ret != 0)
    {
        fprintf(stderr, "Producer ended with error, setting return_val = 1\n");
        return_val = 1;
    }

    // wait for the consumers to proccess all the work and print
    // after that increase semaphore value to end them
    sem_getvalue(&semaphore, &sem_val);
    while (sem_val != 0)
    {
        sem_getvalue(&semaphore, &sem_val);
    }

    for (int i = 0; i < N; i++)
    {
        sem_post(&semaphore);
    }

    sem_getvalue(&semaphore, &sem_val);

    for (int i = 0; i < N; i++)
    {
        pthread_join(consumers[i], &ret1);
        if (ret1 != 0)
        {
            fprintf(stderr, "Consumer with index %d ended with an error.\n", i);
            return_val = 1;
        }
    }

    free(consumers);
    return return_val;
}

void push_to_list(int number, char *text)
{
    pthread_mutex_lock(&lock_insert);

    node_t *temp;
    temp = (node_t *)malloc(sizeof(node_t));
    temp->text = text;
    temp->weird_number = number;

    if (head == NULL)
    {
        head = temp;
        head->next_node = NULL;
        tail = head;
    }
    else
    {
        tail->next_node = temp;
        tail = temp;
        tail->next_node = NULL;
    }

    in_list++;

    pthread_mutex_unlock(&lock_insert);

    sem_post(&semaphore);
}

void *producer_work(void *arg)
{
    prod_alive = 1;

    int number, ret, ret_feof;
    char *text;

    while (!(ret_feof = feof(stdin)) && (ret = scanf("%d %ms", &number, &text)) == 2)
    {
        if (number < 0)
        {
            free(text);
            prod_alive = 0;
            pthread_exit((void *)1);
        }

        push_to_list(number, text);
    }
    // EOF didn't occur, yet scanf detected wrong input
    if (!ret_feof && ret != -1)
    {
        prod_alive = 0;
        pthread_exit((void *)1);
    }

    prod_alive = 0;
    return NULL;
}

void *consumer_work(void *arg)
{
    sem_wait(&semaphore);

    while (in_list > 0 || prod_alive == 1)
    {
        in_list--;

        // take from the linked list
        pthread_mutex_lock(&lock_insert);

        if (head == NULL)
        {
            pthread_mutex_unlock(&lock_insert);
            return NULL;
        }

        node_t *ret = head;
        head = head->next_node;

        pthread_mutex_unlock(&lock_insert);

        // print
        pthread_mutex_lock(&lock_stdout);

        printf("Thread %ld:", (long)arg);
        for (int i = 0; i < ret->weird_number; i++)
        {
            printf(" %s", ret->text);
        }
        printf("\n");

        pthread_mutex_unlock(&lock_stdout);

        free(ret->text);
        free(ret);

        sem_wait(&semaphore);
    }

    return NULL;
}

int init(int argc, char **argv)
{
    if (argc < 2)
    {
        N = 1;
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Wrong number of arguments!\n");
        return 1;
    }
    else
    {
        N = atoi(argv[1]);
    }

    long numOfCPU = sysconf(_SC_NPROCESSORS_ONLN);

    if (N < 1 || N > numOfCPU)
    {
        return 1;
    }

    consumers = (pthread_t *)malloc(sizeof(pthread_t) * N);

    sem_init(&semaphore, 0, 0);
    pthread_mutex_init(&lock_insert, NULL);
    pthread_mutex_init(&lock_stdout, NULL);

    return 0;
}