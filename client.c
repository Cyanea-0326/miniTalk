/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:01:58 by shonakam          #+#    #+#             */
/*   Updated: 2024/02/14 12:18:39 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf/srcs/ft_printf.h"

// avoid magic number
#define BIT_PATTERN_LENGTH 8

void	send_signals(unsigned char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
		{
			kill(pid, SIGUSR1); 
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(150);
		i--;
	}
}

// topcmd >> Guard kill ppid 0,1,2
int main(int ac, char **av)
{
	pid_t	pid;
	size_t	i;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid < 100)
			exit(1);
		i = 0;
		while (av[2][i] != '\0')
		{
			send_signals(av[2][i++], pid);
		}
		send_signals('\n', pid);
	}
	else
	{
		ft_printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
}