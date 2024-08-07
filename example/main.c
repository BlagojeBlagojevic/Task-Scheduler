#define WORKER_IMPLEMENTATION 
#include "worker.h"

int32_t task1(int state){

    printf("Task1\n");
    for (size_t i = 0; i < 40; i++)
    {
        printf("----Task 1 ----\n");
    }
    
    //exit(-1);
}

int32_t task2(int state){
    for (int i = 0; i < 20; i++)
    {
        printf("Task2 value %d\n", i);
    }
    
}



int32_t task3(int state){
    printf("---- Task 3 ------\n");
    for (int  i = 0; i < 20; i++)
    {
        printf("%d\n",i);
    }
    

}
int main(){
    Task *task = task_allocation(100); 
    
    task[0].task_pointer = task1;
    task[0].tick_period  = 1000; 
    task[1].task_pointer = task2;
    task[1].tick_period  = 100;
    task[2].task_pointer = task3;
    task[2].tick_period  = 120;

    init_timer_tick();
    loop(task, 3, 10);
    free(task);
    return 0;
}
