/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:15:12 by trpham            #+#    #+#             */
/*   Updated: 2025/03/07 19:24:11 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

static void	signal_handler(int signal);
static void	set_signal_action(void);
extern int ready_to_receive;
// static void	set_signal_action(void);

int	main()
{
	int	pid;

	pid =  getpid();
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	set_signal_action();
	while (1)
	{
		// if (set_signal_action())
		// 	ready_to_receive = true;
		// if (!ready_to_receive)
			pause();
		// signal(SIGTERM, signal_handler);
		// sigaction(SIGINT, &act, NULL);
	}
	return (0);
}

static void	set_signal_action(void)
{
	struct sigaction act;
	
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	// sigaction(SIGTERM, &act, NULL);
}

static void	signal_handler(int signal)
{
	static unsigned char	temp_c;
	static int				i;

	temp_c = temp_c << 1;
	if (signal == SIGTERM)
	{
		ft_putstr_fd("Transmission completed\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (signal == SIGUSR1)
	{
		// ft_putstr_fd("Receive bit 1 \n", 1);
		temp_c = temp_c | 1;
	}
	// else
	// 	ft_putstr_fd("Receive bit 0 \n", 1);
	i++;
	if (i == 8)
	{
		// if (temp_c == '\0')
		// {
		// 	ft_putstr_fd("\n", 1);
		// 	ft_putstr_fd("Transmission completed\n", 1);
		// 	// exit(EXIT_SUCCESS);
		// }
		ft_putchar_fd(temp_c, 1);
		temp_c = 0;
		i = 0;
	}
	ready_to_receive = TRUE;
}
