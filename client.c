/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:43:51 by kdvarako          #+#    #+#             */
/*   Updated: 2024/05/20 11:33:36 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sendbinary(char *s, pid_t pid)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (s[i] == '1')
			kill(pid, SIGUSR2);
		else if (s[i] == '0')
			kill(pid, SIGUSR1);
		i++;
		usleep(200);
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
			bin[j] = '1';
		else
			bin[j] = '0';
		j--;
		val = val / 2;
	}
	while (j >= 0)
	{
		bin[j] = '0';
		j--;
	}
	sendbinary(bin, pid);
}

int	error_pid(char *arg)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(arg))
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
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
	if (error_pid(argv[1]) == -1)
	{
		ft_putstr_fd("Entered pid is not a number\n", 1);
		return (-1);
	}
	i = 0;
	pid = ft_atoi(argv[1]);
	while (i < ft_strlen(argv[2]))
	{
		chartobinary(argv[2][i], pid);
		i++;
	}
	chartobinary('\0', pid);
	return (0);
}
