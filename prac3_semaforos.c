#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>

#define ITER 100000

sem_t sem1;

static RT_TASK tarea1;
static RT_TASK tarea2;

int global = 0;

void tareaUno(void *arg){
    for(int i=0; i < ITER; i++){
        sem__wait(&sem1);
        printf("Tarea 1 la variable global es %d -----\n", ++global);
        sem__post(&sem1);
    }
}

void tareaDos(void *arg){
    for(int i=0; i < ITER; i++){
        sem__wait(&sem1);
        printf("Tarea 2 la variable global es %d -----\n", --global);
        sem__post(&sem1);
    }
}

int main(int argc, char* argv[]){
    sem__init(&sem1, 0, 1);
    rt_task_create(&tarea1, "tarea 1", 0 , 1, 0);
    rt_task_create(&tarea2, "tarea 2", 0 , 1, 0);
    rt_task_start(&tarea1, &tareaUno,0);
    rt_task_start(&tarea2, &tareaDos,0);
    return 0;
}