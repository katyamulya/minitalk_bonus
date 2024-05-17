/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:23 by kdvarako          #+#    #+#             */
/*   Updated: 2024/05/17 15:43:29 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sendbinary(char *s, pid_t pid)
{
	int	i;
	int	result;

	i = 0;
	while (i < 9)
	{
		if (s[i] == '1')
			result = kill(pid, SIGUSR2);
		else if (s[i] == '0')
			result = kill(pid, SIGUSR1);
		i++;
		usleep(100);
	}
}

void	chartobinary(unsigned char ch, pid_t pid)
{
	int		j;
	int		val;
	char	bin[9];

	val = ch;
	j = 7;
	while (val > 0)
	{
		if (val % 2 == 1)
		{
			bin[j] = '1';
			j--;
		}
		else
		{
			bin[j] = '0';
			j--;
		}
		val = val / 2;
	}
	while (j >= 0)
	{
		bin[j] = '0';
		j--;
	}
	sendbinary(bin, pid);
}

void	handler(int signum)
{
	if (signum == SIGUSR1)
		ft_putstr_fd("All characters were printed on server.\n", 1);
}

int	main(int argc, char **argv)
{
	pid_t			pid;
	unsigned int	i;

	if (argc < 3)
	{
		ft_putstr_fd("Not all parameters were given!\n", 1);
		return (-1);
	}
	i = 0;
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, handler);
	while (i < ft_strlen(argv[2]))
	{
		chartobinary(argv[2][i], pid);
		i++;
	}
	chartobinary('\0', pid);
	return (0);
}
