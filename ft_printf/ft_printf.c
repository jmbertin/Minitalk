#include "ft_printf.h"

/**
 * Processes and prints the format specifiers provided by ft_printf.
 * @param list      List of arguments provided to the ft_printf function.
 * @param c         The format specifier character.
 * @param ptr_len   Pointer to an integer where the length of the printed string will be accumulated.
 */
void	ft_exec_print(va_list list, char c, int *ptr_len)
{
	if (c == 'd' || c == 'i')
		ft_printnbr((int)va_arg(list, int), 1, ptr_len);
	else if (c == 'c')
		*ptr_len += write(1, "(char)va_arg(list, int)", 1);
	else if (c == 's')
		*ptr_len += ft_print_str((char *)va_arg(list, char *), 1);
	else if (c == '%')
		*ptr_len += write(1, &c, 1);
	else if (c == 'u')
		*ptr_len += ft_print_base((unsigned long long)va_arg(list, int), "0123456789", 10);
	else if (c == 'p')
	{
		*ptr_len += ft_print_str("0x", 1);
		*ptr_len += ft_print_base((unsigned long long)va_arg(list, void *), "0123456789abcdef", 16);
	}
	else if (c == 'x')
		*ptr_len += ft_print_base((unsigned int)va_arg(list, unsigned int), "0123456789abcdef", 16);
	else if (c == 'X')
		*ptr_len += ft_print_base((unsigned int)va_arg(list, unsigned int), "0123456789ABCDEF", 16);
}

/**
 * A simplified implementation of the printf function to format and print data.
 * This function processes the format string and a variable number of arguments,
 * processes them, and sends the formatted string to the standard output.
 * @param input     A format string that specifies how subsequent arguments
 *                  are converted for output.
 * @return          The number of characters printed, excluding the null byte used to end output to strings.
 */
int	ft_printf(const char *input, ...)
{
	va_list	listparam;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(listparam, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			ft_exec_print(listparam, input[i + 1], &len);
			i++;
		}
		else
			len += write(1, &input[i], 1);
		i++;
	}
	va_end(listparam);
	return (len);
}
