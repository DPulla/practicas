#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>

#define ITER 100000

static RT_TASK tarea1;
static RT_TASK tarea2;
static RT_SEM sem;

int global = 0;

void tareaUno(void *arg){
    for(int i=0; i < ITER; i++){
        rt_sem_v(&sem);
        printf("Tarea 1 la variable global es ----- %d \n", ++global);
        rt_sem_p_until(&sem, TM_INFINITE);
    }
}

void tareaDos(void *arg){
    for(int i=0; i < ITER; i++){
        rt_sem_v(&sem);
        printf("Tarea 2 la variable global es ----- %d \n", --global);
        rt_sem_p_until(&sem, TM_INFINITE);
    }
}

int main(int argc, char* argv[]){
    rt_sem_create(&sem, "sem", 0, S_PULSE);
    rt_task_create(&tarea1, "tarea 1", 0 , 1, 0);
    rt_task_create(&tarea2, "tarea 2", 0 , 1, 0);
    rt_task_start(&tarea1, &tareaUno,0);
    rt_task_start(&tarea2, &tareaDos,0);
    printf("\nValor variable GLOBAL ---- %d\n", global);
    return 0;
}