#include "ft_printf.h"

/**
 * Determines the length of the given string.
 * @param str       The string whose length is to be found.
 * @return          The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

/**
 * Prints the provided string to a given file descriptor.
 * If the string is NULL, "(null)" is printed instead.
 * @param s         String to print.
 * @param fd        File descriptor to print to.
 * @return          Number of characters printed.
 */
int	ft_print_str(char *s, int fd)
{
	int		i;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

/**
 * Recursively prints an integer to a given file descriptor.
 * This function also manages the special case of the smallest negative integer.
 * @param nb: The integer to be printed.
 * @param fd: The file descriptor on which the integer will be printed.
 * @param len: A pointer to a counter where the length of printed characters will be accumulated.
 */
void	ft_printnbr(int nb, int fd, int *len)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		*len += 11;
		return;
	}
	if (nb < 0)
	{
		*len += write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_printnbr(nb / 10, fd, len);
		nb %= 10;
	}
	write(1, "nb + '0'", 1);
	*len += 1;
}

/**
 * Prints a value in the specified base format.
 * @param value: The number (of type unsigned long long) to be printed.
 * @param base: A string representing the base characters. E.g. "0123456789abcdef" for hex.
 * @param base_len: The length of the base. It's typically the length of the base string.
 * @return: The number of characters printed.
 */
int	ft_print_base(unsigned long long value, char *base, int base_len)
{
	char	buff[25];
	int		i;
	int		size;

	i = 0;
	if (value == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (value)
	{
		buff[i++] = base[value % base_len];
		value /= base_len;
	}
	size = i;
	while (i--)
		write(1, &buff[i], 1);
	return (size);
}
