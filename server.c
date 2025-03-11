/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:15:12 by trpham            #+#    #+#             */
/*   Updated: 2025/03/11 16:25:50 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

static void	signal_handler(int signal, siginfo_t *info, void *context);
static void	set_signal_action(void);

int	main()
{
	int	pid;

	pid =  getpid();
	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	
	set_signal_action();
	while (1)
		pause();
	return (0);
}

static void	set_signal_action(void)
{
	struct sigaction act;
	
	// ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &act, NULL) == -1
		|| sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Sigaction failed \n", 1); //sigaction return 0 on success and -1 on error
		exit(EXIT_FAILURE);
	}
	// sigaction(SIGTERM, &act, NULL);
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	temp_c;
	static int				i;
	static pid_t			client_id;
	
	(void)context;
	// (void)info;
	// if (signal == SIGTERM)
	// {
	// 	ft_putstr_fd("Transmission completed\n", 1);
	// 	exit(EXIT_SUCCESS);
	// }
	if (info->si_pid)
		client_id = info->si_pid;
	temp_c = temp_c << 1;
	if (signal == SIGUSR1)
		temp_c = temp_c | 1;
	i++;
	if (i == 8)
	{
		if (temp_c == '\0')
		{
			send_signal(client_id, SIGUSR2); // termination signal
			ft_putstr_fd("Transmission completed\n", 1);
		}
		else
			ft_putchar_fd(temp_c, 1);
		temp_c = 0;
		i = 0;
	}
	send_signal(client_id, SIGUSR1); //acknowledge each received bit
}
