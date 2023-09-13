#include "includes/minitalk.h"

/**
 * g_waiting is a global variable used to indicate whether the program is currently
 * waiting for a signal. It is set to 0 initially and modified by the signal handlers.
 */
int	g_waiting;

/**
 * The handler function is a signal handler that sets the global variable g_waiting to 0.
 * It is registered to handle the SIGUSR1 signal.
 * @param signum The signal number of the received signal (expected to be SIGUSR1)
 */
void	handler(int signum)
{
	g_waiting = 0;
}

/**
 * The ft_encode function takes a character and a process ID (pid) and sends the binary
 * representation of the character to the process identified by the pid, one bit at a time.
 * It sends SIGUSR1 for a '1' bit and SIGUSR2 for a '0' bit.
 * @param c The character to be encoded and sent
 * @param pid The process ID of the receiving process
 * @return Returns 0 if the character was successfully sent, and 1 otherwise
 */
int	ft_encode(unsigned char c, pid_t pid)
{
	int		i;
	int		value;

	i = 0;
	while (i < 8)
	{
		value = (c >> (7 - i)) & 1;
		if (value == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (1);
		}
		i++;
		g_waiting = 1;
		while (g_waiting == 1)
			;
	}
	return (0);
}

/**
 * The ft_ack function is a signal handler that is called when a SIGUSR2 signal is received.
 * It prints a message confirming the reception of the message by the server.
 * @param signum The signal number of the received signal (expected to be SIGUSR2)
 */
void	ft_ack(int signum)
{
	(void) signum;
	ft_printf("Server confirmed reception of the message.\n");
}

/**
 * The main function initializes the signal handlers, validates the command line arguments,
 * and then iterates over the message string, sending each character to the server using
 * the ft_encode function. It ends by sending a null character ('\0') to indicate the end
 * of the message.
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @return Returns 0 if the message was successfully sent, and a non-zero value otherwise
 */
int	main(int argc, char **argv)
{
	char	*str;
	pid_t	pid;
	int		i;

	signal(SIGUSR1, handler);
	signal(SIGUSR2, ft_ack);
	g_waiting = 0;
	if (argc < 3)
		return (ft_printf("ERROR : missing 'SERVER PID' or 'MESSAGE'\n"));
	pid = ft_atoi(argv[1]);
	str = argv[2];
	i = 0;
	while (str[i])
	{
		if (ft_encode((unsigned char) str[i], pid) == 1)
			return (ft_printf("Error sending character.\n"));
		i++;
	}
	if (ft_encode('\0', pid) == 1)
		return (ft_printf("Error sending character.\n"));
	return (0);
}
