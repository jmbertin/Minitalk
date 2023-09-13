#include <stdlib.h>
#include <stdint.h>
#include "includes/minitalk.h"

/**
 * This static function is a helper function used internally in the ft_atoi function.
 * It checks and skips the spaces and handles signs (+/-) present at the start of the input string.
 * It returns 9 if it encounters more than one sign characters sequentially,
 * which is considered an error state.
 * @param ptr_i - A pointer to an integer to store the index up to which spaces and signs are present.
 * @param str - The input string which needs to be parsed to an integer.
 * @param ptr_minus - A pointer to an integer to store the count of minus signs encountered.
 * @return - Returns 0 for a valid string and 9 for an invalid string with consecutive signs.
 */
static int	check_sp_signs(int *ptr_i, const char *str, int *ptr_minus)
{
	int	minus;
	int	i;

	i = 0;
	minus = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if ((str[i] == 43 || str[i] == 45)
		&& (str[i + 1] == 43 || str[i + 1] == 45))
		return (9);
	while (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
		{
			minus++;
			i++;
		}
		else
			i++;
	}
	*ptr_i = i;
	*ptr_minus = minus;
	return (0);
}

/**
 * This function converts the initial portion of the input string pointed
 * to by 'str' to an integer value according to the ANSI C standard.
 * @param str - The input string which needs to be parsed to an integer.
 * @return - Returns the converted integer value of the input string.
 *           If the input string has consecutive signs, it returns 0.
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	minus;

	i = 0;
	nb = 0;
	minus = 0;
	if (check_sp_signs(&i, str, &minus) == 9)
		return (0);
	while (str[i] && (str[i] > 47 && str[i] < 58))
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (minus % 2 == 1)
		nb = -nb;
	return (nb);
}

/**
 * This function allocates memory for an array of 'elementCount' elements,
 * each of 'elementSize' bytes, and returns a pointer to the allocated memory.
 * The allocated memory is initialized to zero.
 * @param elementCount - Number of elements to be allocated.
 * @param elementSize - Size of each element in bytes.
 * @return - Returns a pointer to the allocated memory, or NULL if allocation fails or
 *           if 'elementCount' or 'elementSize' is SIZE_MAX.
 */
void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*dest;

	dest = (void *)malloc(elementCount * elementSize);
	if (dest == 0 || elementCount == SIZE_MAX || elementSize == SIZE_MAX)
		return (NULL);
	ft_bzero(dest, elementCount * elementSize);
	return (dest);
}

/**
 * This function sets the first 'n' bytes of the memory area pointed to by 's' to zero.
 * @param s - A pointer to the memory area to be set to zero.
 * @param n - The number of bytes to set to zero.
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		*str++ = '\0';
	}
}
