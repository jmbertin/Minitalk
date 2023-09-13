#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "ft_printf.h"

typedef struct s_signal
{
	unsigned char	c;
	int				i;
	int				pid_sender;
}	t_signal;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t elementCount, size_t elementSize);
void	ft_bzero(void *s, size_t n);

#endif
