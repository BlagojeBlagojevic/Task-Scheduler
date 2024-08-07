# Task Scheduler

## Overview

This project is a simple task scheduler written in C. It provides a basic framework to schedule and execute tasks at specified intervals using signal handling and timers.

## Features

- **Task Allocation**: Dynamically allocate memory for a specified number of tasks.
- **Timer-Based Execution**: Execute tasks periodically based on a timer.
- **Signal Handling**: Use Unix signals to manage timer ticks.

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/BlagojeBlagojevic/Task-Scheduler.git
    cd taskscheduler
    ```

2. Compile the code:

    ```bash
    gcc -o scheduler main.c
    ```

    Ensure that `main.c` contains the entry point and includes the `worker.h` file.

## Usage

1. **Include the Header**

    In your C file, include the `worker.h` header:

    ```c
    #define WORKER_IMPLEMENTATION
    #include "worker.h"
    ```

2. **Define Your Tasks**

    Create your task functions. These should match the signature `int32_t function_name(int)`:

    ```c
    int32_t task1(int state){
    printf("task1\n");
    }

    int32_t task2(int state){
    printf("task2\n");
    }

    int32_t task3(int state){
    printf("task3\n");
    }

    ```

3. **Initialize the Scheduler**

    Allocate tasks and set up the scheduler:

    ```c
    int main(){
    Task *task = task_allocation(100); 
    
    task[0].task_pointer = task1;
    task[0].tick_period  = 1000; 
    task[1].task_pointer = task2;
    task[1].tick_period  = 100;
    task[2].task_pointer = task3;
    task[2].tick_period  = 120;
    //task[0].task_pointer(NULL);
    init_timer_tick();
    
    //ualarm(1000, 1);   
    loop(task, 3, 10);
    free(task);
    return 0;
    }
    ```

4. **Run the Scheduler**

    Execute the compiled program:

    ```bash
    ./scheduler
    ```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

If you have suggestions for improvements or find any issues, feel free to open an issue or submit a pull request.


