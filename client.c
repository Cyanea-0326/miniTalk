/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:01:58 by shonakam          #+#    #+#             */
/*   Updated: 2024/02/15 18:42:30 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "ft_printf/srcs/ft_printf.h"

// avoid magic number
#define BIT_PATTERN_LENGTH 8

void	send_signals(unsigned char c, int pid)
{
	int	i;

	i = (CHAR_BIT - 1);
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
			kill(pid, SIGUSR1); 
		else
			kill(pid, SIGUSR2);
		usleep(250);
		i--;
	}
}

void	manage_str(pid_t pid, char *s)
{
	size_t	i;
	
	i = 0;
	ft_printf("%s\n", s);
	while (s[i] != '\0')
		send_signals(s[i++], pid);
	send_signals('\n', pid);
}

// topcmd >> Guard kill ppid 0,1,2
int main(int ac, char **av)
{
	pid_t			pid;

	if (ac == 3)
	{
		pid = (pid_t)ft_atoi(av[1]);
		if (pid < 100)
			exit(1);
		manage_str(pid, av[2]);
	}
	else
	{
		ft_printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
}
