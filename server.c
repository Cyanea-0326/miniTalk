/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 03:19:40 by shonakam          #+#    #+#             */
/*   Updated: 2024/02/13 20:54:02 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "ft_printf/srcs/ft_printf.h"

// avoid magic number
#define BIT_PATTERN_LENGTH 8

typedef struct {
	int		sig_c;
	char	ascii;
} BitData;

// man signal >> The return of the argument int must be void
// share bit management using SIGNAL throughout the program.
BitData g_bit_data;

void	handle_signals(int sig)
{
	if (sig == SIGUSR1)
		g_bit_data.sig_c = (g_bit_data.sig_c << 1) | 0;
	else if (sig == SIGUSR2)
		g_bit_data.sig_c = (g_bit_data.sig_c << 1) | 1;

	if (++g_bit_data.ascii == BIT_PATTERN_LENGTH) {
		ft_printf("%c", (char)g_bit_data.sig_c);
		g_bit_data.sig_c = 0;
		g_bit_data.ascii = 0;
	}
}

int main(void)
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_signals;
	sa.sa_flags = 0;

	ft_printf("The server process ID is:\033[32m %d\n", getpid());
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	
	if (sigaction(SIGUSR1, &sa, NULL) == (-1))
	{
		ft_printf("SIGERR1\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == (-1))
	{
		ft_printf("SIGERR2\n");
		exit(1);
	}
	while (1)
	{
		pause();
	}
}