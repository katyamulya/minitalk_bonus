/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:40:23 by kdvarako          #+#    #+#             */
/*   Updated: 2024/05/20 11:32:45 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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

void	printnsignal(char *s, pid_t pid)
{
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	kill(pid, SIGUSR1);
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

void	signalhandler(int signum, siginfo_t *info, void *context)
{
	static int	i;
	static int	j;
	static int	number;
	static char	*s;

	(void)context;
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
			printnsignal(s, info->si_pid);
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
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_putstr_fd("PID = ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sa.sa_handler = (void *)signalhandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		printf("Error SIGUSR1!\n");
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		printf("Error SIGUSR2!\n");
	}
	while (1)
	{
		pause();
	}
	return (0);
}
