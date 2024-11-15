#include "os.h"

/* interval ~= 1s */
#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint32_t _tick = 0;

/* load timer interval(in ticks) for next timer interrupt.*/
void timer_load(int interval)
{
	/* each CPU has a separate source of timer interrupts. */
	int id = r_mhartid();
	
	*(uint64_t*)CLINT_MTIMECMP(id) = *(uint64_t*)CLINT_MTIME + interval;
}

void timer_init()
{
	/*
	 * On reset, mtime is cleared to zero, but the mtimecmp registers 
	 * are not reset. So we have to init the mtimecmp manually.
	 */
	timer_load(TIMER_INTERVAL);

	/* enable machine-mode timer interrupts. */
	w_mie(r_mie() | MIE_MTIE);

	/* enable machine-mode global interrupts. */
	w_mstatus(r_mstatus() | MSTATUS_MIE);
}

void timer_handler() 
{
	_tick++;
    // printf("tick: %d\n", _tick);

    uint32_t seconds = _tick;

    uint32_t hours = seconds / 3600;
    seconds = seconds % 3600;

    uint32_t minutes = seconds / 60;
    seconds = seconds % 60;

    // printf("%02d:%02d:%02d\n", hours, minutes, seconds);

    if (hours < 10) {
		uart_putc('0');
    }
    printf("%d", hours);

    printf(":");

    if (minutes < 10) {
		uart_putc('0');
	}
	printf("%d", minutes);

	printf(":");

	if (seconds < 10) {
		uart_putc('0');
	}
	printf("%d", seconds);

	uart_putc('\n');

	timer_load(TIMER_INTERVAL);
}
