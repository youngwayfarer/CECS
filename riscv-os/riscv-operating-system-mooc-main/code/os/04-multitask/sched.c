#include "os.h"

/* defined in entry.S */
extern void switch_to(struct context *next);

#define MAX_TASKS 10
#define STACK_SIZE 1024
/*
 * In the standard RISC-V calling convention, the stack pointer sp
 * is always 16-byte aligned.
 */
uint8_t __attribute__((aligned(16))) task_stack[MAX_TASKS][STACK_SIZE];
// struct context ctx_tasks[MAX_TASKS];

// todo: new struct for task priority
struct task_info {
    uint8_t priority;
    void* param;
    struct context ctx;
};
struct task_info task_infos[MAX_TASKS];
static uint8_t task_existing[MAX_TASKS];

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

/*
 * _top is used to mark the max available position of ctx_tasks
 * _current is used to point to the context of current task
 */
static int _top = 0;
static int _current = -1;

static void w_mscratch(reg_t x)
{
	asm volatile("csrw mscratch, %0" : : "r" (x));
}

void sched_init()
{
    w_mscratch(0);

    for (int i = 0; i < MAX_TASKS; i++) {
		task_existing[i] = 0;
	}
}

/*
 * implment a simple cycle FIFO schedular
 */
// void schedule()
// {
// 	if (_top <= 0) {
// 		panic("Num of task should be greater than zero!");
// 		return;
// 	}

// 	_current = (_current + 1) % _top;
// 	struct context *next = &(ctx_tasks[_current]);
// 	switch_to(next);
// }

// todo: schedule
void schedule() {
	if (_top <= 0) {
		panic("Num of task should be greater than zero!");
		return;
	}

    // _current need a initial value
    if (_current == -1) {
		_current = 0;
	}

    // printf("------------------------------------------------------------------\n");
	// for (int i = 0; i < _top; i++) {
	// 	printf("task param: %p, priority: %d\n", task_infos[i].param, task_infos[i].priority);
	// 	printf("task: %d\n", task_infos[i].ctx.ra);
	// }

	// find the highest priority task
    int highest_priority_task = -1;
    int highest_priority = 256;
	for (int i = 0; i < _top; i++) {
        if (!task_existing[i]) {
            continue;
		}

        if (task_infos[i].priority < highest_priority) {
			highest_priority = task_infos[i].priority;
			highest_priority_task = i;
		}
    }

    if (highest_priority_task == -1) {
        panic("No task to run!");
        return;
    }

    _current = highest_priority_task;
    // printf("current: %d\n", _current);
    // printf("current param: %p\n", task_infos[_current].param);
    // printf("current priority: %d\n", task_infos[_current].priority);
    struct context *next = &(task_infos[_current].ctx);

    // printf("next ra: %d\n", next->ra);
    // printf("------------------------------------------------------------------\n");

	switch_to(next);
}

/*
 * DESCRIPTION
 * 	Create a task.
 * 	- start_routin: task routine entry
 * RETURN VALUE
 * 	0: success
 * 	-1: if error occured
 */
// int task_create(void (*start_routin)(void))
// {
// 	if (_top < MAX_TASKS) {
// 		ctx_tasks[_top].sp = (reg_t) &task_stack[_top][STACK_SIZE];
// 		ctx_tasks[_top].ra = (reg_t) start_routin;
// 		_top++;
// 		return 0;
// 	} else {
// 		return -1;
// 	}
// }


// todo: task_create
// just create a task, not run it
int task_create(void (*task)(void *param), void *param, uint8_t priority) {
	if (_top < MAX_TASKS) {
        if (priority < 0 || priority > 255) {
            return -1;
		}

        for (int i = 0; i < _top; i++) {
            if (!task_existing[i]) {
                task_infos[i].priority = priority;
                task_infos[i].param = param;
                task_infos[i].ctx.sp = (reg_t)&task_stack[i][STACK_SIZE];
                task_infos[i].ctx.ra = (reg_t)task;
                task_existing[i] = 1;
                // printf("task param: %p\n", param);
				// printf("task %d\n", task_infos[_top - 1].ctx.ra);
                return 0;
			}
		}
        task_infos[_top].priority = priority;
        task_infos[_top].param = param;
        task_infos[_top].ctx.sp = (reg_t)&task_stack[_top][STACK_SIZE];
        task_infos[_top].ctx.ra = (reg_t)task;
        task_existing[_top] = 1;
        _top++;
        // printf("task param: %p\n", param);
        // printf("task %d\n", task_infos[_top - 1].ctx.ra);
        return 0;
    } else {
        return -1;
    }
}

/*
 * DESCRIPTION
 * 	task_yield()  causes the calling task to relinquish the CPU and a new 
 * 	task gets to run.
 */
void task_yield()
{
	schedule();
}

/*
 * a very rough implementaion, just to consume the cpu
 */
void task_delay(volatile int count)
{
	count *= 50000;
	while (count--);
}


// todo:

void task_exit() {
    task_existing[_current] = 0;
    schedule();
}