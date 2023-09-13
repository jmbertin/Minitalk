#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *input, ...);
int		ft_print_str(char *s, int fd);
void	ft_printnbr(int nb, int fd, int *len);
size_t	ft_strlen(const char *str);
int		ft_print_base(unsigned long long nb, char *base, int len);

#endif
