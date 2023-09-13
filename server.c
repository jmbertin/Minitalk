#include "includes/minitalk.h"
#include "includes/ft_printf.h"

/**
 * A global variable to store the current state of the signal being processed.
 * It holds the sender's PID, the current character being built from the signal
 * data, and a counter of how many bits have been received so far.
 */
t_signal	*g_signal_server;

/**
 * A signal handler function that is called when SIGUSR1 or SIGUSR2 signals are
 * received. It uses global variable g_signal_server to build up a character bit
 * by bit from the signals received, printing the character when 8 bits have been
 * received, and acknowledging the receipt of a message back to the sender when a
 * null character ('\0') is received.
 * @param signum - The signal number of the received signal.
 * @param info - A pointer to a siginfo_t structure which contains information
 *               about the signal (including the sender's PID).
 * @param context - A pointer to a ucontext_t structure (not used in this function).
 */
void	ft_signal_handler(int signum, siginfo_t *info, void *context)
{
	if (info->si_pid != 0)
		g_signal_server->pid_sender = info->si_pid;
	g_signal_server->c <<= 1;
	if (signum == SIGUSR1)
	{
		g_signal_server->c++;
	}
	g_signal_server->i++;
	if (g_signal_server->i == 8)
	{
		g_signal_server->i = 0;
		ft_printf("%c", g_signal_server->c);
		if (g_signal_server->c == '\0')
		{
			usleep(40);
			kill(g_signal_server->pid_sender, SIGUSR2);
		}
	}
	usleep(40);
	kill(g_signal_server->pid_sender, SIGUSR1);
}

/**
 * The main function initializes a t_signal structure to hold the signal state,
 * sets up signal handlers to handle SIGUSR1 and SIGUSR2 signals using the
 * sigaction system call, and then enters an infinite loop where it pauses
 * waiting for signals to be received.
 * @return - This function does not return as it enters an infinite loop.
 */
int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	g_signal_server = malloc(sizeof(t_signal) * 1);
	g_signal_server->c = 0b00000000;
	g_signal_server->i = 0;
	g_signal_server->pid_sender = 0;
	pid = getpid();
	ft_printf("PID SERVER : %d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
