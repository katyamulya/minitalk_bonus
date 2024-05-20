/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:43:54 by kdvarako          #+#    #+#             */
/*   Updated: 2024/05/20 11:28:38 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	getdecimal(int signum, int i, int num)
{
	int	bin;
	int	binn[9];

	binn[0] = 128;
	binn[1] = 64;
	binn[2] = 32;
	binn[3] = 16;
	binn[4] = 8;
	binn[5] = 4;
	binn[6] = 2;
	binn[7] = 1;
	if (signum == SIGUSR1)
		bin = 0;
	if (signum == SIGUSR2)
		bin = 1;
	num = num + bin * binn[i];
	return (num);
}

char	*charjoin(char *s, char ch)
{
	char	*ptr;
	int		len;
	int		i;

	len = ft_strlen(s) + 1;
	i = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (free(s), s = NULL, NULL);
	if (s)
	{
		while (s[i] != '\0')
		{
			ptr[i] = s[i];
			i++;
		}
	}
	ptr[i] = ch;
	i++;
	ptr[i] = '\0';
	return (free(s), s = NULL, ptr);
}

void	signalhandler(int signum)
{
	static int	i;
	static int	j;
	static int	number;
	static char	*s;

	if (!s)
		s = ft_calloc(1, 1);
	if (i == 0)
		number = 0;
	number = getdecimal(signum, i, number);
	i++;
	if (i == 8)
	{
		s = charjoin (s, ((char) number));
		if (((char) number) == '\0')
		{
			ft_putstr_fd(s, 1);
			write(1, "\n", 1);
			free(s);
			s = NULL;
			j = -1;
		}
		j++;
		i = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("PID = ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
	{
		signal(SIGUSR1, signalhandler);
		signal(SIGUSR2, signalhandler);
		pause();
	}
	return (0);
}
