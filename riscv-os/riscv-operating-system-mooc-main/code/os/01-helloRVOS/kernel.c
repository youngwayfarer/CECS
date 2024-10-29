extern void uart_init(void);
// extern void uart_putc(char c);
extern void uart_puts(char *s);
extern char uart_getc(void);
extern void uart_echo(void);

void start_kernel(void)
{
	uart_init();
    uart_puts("Hello, RVOS!\n");

    uart_echo();

	while (1) {}; // stop here!
}

