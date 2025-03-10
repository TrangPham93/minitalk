/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:39:13 by trpham            #+#    #+#             */
/*   Updated: 2025/03/10 14:56:46 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int validate_PID(char *arg);

static void	send_signal(int	pid, unsigned char c);
static void action(int signal);

int	main(int ac, char *av[])
{
	char	*msg;
	int		i;
	int		PID;

	if (ac != 3)
	{
		ft_putstr_fd("Please provide PID and message\n", 1);
		exit(EXIT_FAILURE);
	}
	PID = validate_PID(av[1]);
	if (PID == -1)
		exit(EXIT_FAILURE);
	
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);

	msg = av[2];
	i = 0;
	while (msg[i])
	{
		send_signal(PID, msg[i]);	
		i++;
	}
	
	return (0);
}

static void	send_signal(int	pid, unsigned char c)
{
	int				i;

	i = 7;
	while (i >= 0)
	{
		// while (!ready_to_receive)
		// 	pause();
		if ((c & (1 << i)) == 0)
		{
			kill(pid, SIGUSR2); // 1 = 00000001, bitmask isolating the ith bit in c
		} 
		else
		{
			kill(pid, SIGUSR1);
		}
		i--;
		usleep(100); 
	}
	while (1)
	{
		pause();
	}
	
	// write(1, "\n", 1);
}

static void action(int signal)
{
	// static int	received;

	if (signal == SIGUSR1)
		// printf("receive %d/n", SIGUSR1);
		kill(getpid(), SIGUSR1);

	else
	{
		// printf("receive %d/n", SIGUSR2);
		kill(getpid(), SIGUSR2);

		// ft_putnbr_fd(received, 1);
		// exit(0);
	}
}

static int validate_PID(char *arg)
{
	int	PID;
	int	i;

	if (ft_strlen(arg) != 6)
	{
		ft_putstr_fd("Not a valid PID\n", 1);
		return (-1);
	}
	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == -1)
		{
			ft_putstr_fd("Not a valid PID\n", 1);
			return (-1);
		}
		i++;
	}
	PID = ft_atoi(arg);
	if (kill(PID, 0) == -1)
	{
		ft_putstr_fd("Invalid PID or process not exist\n", 1);
		return (-1);
	}
	return (PID);
}

/* 
Potential problem with signal transmission
1. timing issue / signal loss: 
	usleep: suspends execution for at least x microsecond --> return 0 on success
2. server's signal handling logic: 
3. validation: send to client after each byte is received. how?
4. check if pid is correct by sending a check to pid: kill return 0 if success else -1
 */
