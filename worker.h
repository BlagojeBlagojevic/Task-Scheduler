#ifndef WORKER_H
#define WORKER_H
#include<stdio.h>
#include<signal.h>
#include<stdint.h>
#include<unistd.h>
#include<time.h>
#include<string.h>

#define ERROR_BREAK(...) fprintf(stdout, __VA_ARGS__); exit(-1)
#define TRUE  1  
#define FALSE 0

#ifndef TASK_ALLOCATOR

    #include<stdlib.h>
    #define TASK_ALLOCATOR malloc

#endif

#ifndef MAX_NUM_OF_TASKS 
    #define MAX_NUM_OF_TASKS 200
#endif

//GLOBAL VARS 
static volatile sig_atomic_t is_timer_ticked = FALSE;
static struct   sigaction sa;  


typedef struct task{
    
    uint8_t is_runing;
    int32_t state;
    uint64_t tick_period;
    uint64_t elapsed_time;
    //uint8_t  priority;
    int32_t (*task_pointer)(int);  //FUNCION POINTER WITCH WILL    
}Task;

Task* task_allocation(int num_of_task);
void init_timer_tick(void);
static inline void loop(Task* task, int num_of_tasks, uint32_t timer_interval_tick);


static void signal_handler(int signo);

#ifdef WORKER_IMPLEMENTATION 

Task* task_allocation(int num_of_task){
    if(num_of_task > MAX_NUM_OF_TASKS){
        ERROR_BREAK("You try to allocate a more task then is posible.\nMax num of tasks is %d.\n", MAX_NUM_OF_TASKS);
    }
    Task* _task;
    _task = TASK_ALLOCATOR(num_of_task * sizeof(Task));
    for (int i = 0; i < num_of_task; i++){
       
       _task[i].is_runing = FALSE;
       _task[i].state = 0;
       _task[i].tick_period = 0;
       _task[i].elapsed_time = 0;
      // _task[i].priority = 0;
       _task[i].task_pointer = NULL;  //FUNCION POINTER WITCH WILL
    }
    
    return _task;
}
void init_timer_tick(void){
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &signal_handler;
    sigaction(SIGALRM, &sa, NULL);   

}
static inline void loop(Task* task, int num_of_tasks, uint32_t timer_interval_tick_ms){
    ualarm(1, timer_interval_tick_ms);
    
    uint16_t runing_task      = 0;   
    while(1){
        if(is_timer_ticked){
            ualarm(1, timer_interval_tick_ms);
            is_timer_ticked = FALSE;
            //task[runing_task].task_pointer(0);
            for (uint16_t i = 0; i < num_of_tasks; i++){
                task[i].elapsed_time += timer_interval_tick_ms;
            }
            
            
            //printf("Elapsed time is %lu\n", task[runing_task].elapsed_time);
            for (uint16_t i = 0; i < num_of_tasks; i++){
                if (task[i].elapsed_time > task[i].tick_period){
                 
                  task[i].elapsed_time = 1;
                  runing_task  = i;
                  break;
                
                }
                   
            }
            //EXECUTE A TASK
            task[runing_task].task_pointer(0);
            sleep(timer_interval_tick_ms * 2);
        }
        
    }
}


static void signal_handler(int signo){
        is_timer_ticked = TRUE;
        //printf("Timer is ticked\n");
}
#endif

#endif