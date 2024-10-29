#include "os.h"

#define DELAY 1000

void user_task0(void *param)
{
    uart_puts("Task 0: Created!\n");
    int i = 0;
	while (1) {
        i++;
        printf("Task 0: i = %d\n", i);
        uart_puts("Task 0: Running...\n");
        if (i == 5) {
            printf("Task 0: exit\n");
            task_exit();
            return;
		}
		task_delay(DELAY);
		task_yield();
	}
}

void user_task1(void *param)
{
	uart_puts("Task 1: Created!\n");
	int i = 0;
    while (1) {
        i++;
        printf("Task 1: i = %d\n", i);
        uart_puts("Task 1: Running...\n");
        if (i == 3) {
            printf("Task 1: exit\n");
            task_exit();
            return;
		}
		task_delay(DELAY);
        task_yield();
	}
}

void user_task3(void *param) {
	uart_puts("Task 3: Created!\n");
	int i = 0;
	while (1) {
		i++;
		printf("Task 3: i = %d\n", i);
		uart_puts("Task 3: Running...\n");
		if (i == 3) {
			printf("Task 3: exit\n");
			task_exit();
			return;
		}
		task_delay(DELAY);
		task_yield();
	}
}

void user_task2(void *param) {
    uart_puts("Task 2: Created!\n");
    int i = 0;
    while (1) {
        i++;
		printf("Task 2: i = %d\n", i);
		uart_puts("Task 2: Running...\n");
        if (i == 3) {
            printf("create task 3\n");
            task_create(user_task3, NULL, 0);
		}
        task_delay(DELAY);
		task_yield();
	}
}



/* NOTICE: DON'T LOOP INFINITELY IN main() */
void os_main(void)
{
    // task_create(user_task0);
    // task_create(user_task1);
    task_create(user_task0, NULL, 2);
    task_create(user_task1, NULL, 0);
    task_create(user_task2, NULL, 3);
}

