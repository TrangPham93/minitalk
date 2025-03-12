/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:39:13 by trpham            #+#    #+#             */
/*   Updated: 2025/03/12 12:12:22 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	validate_and_return_pid(char *arg);
static void	send_char(int pid, unsigned char c);
static void	action(int signal);
int			g_ready_to_receive = 0;
static int validate_and_return_PID(char *arg);
static void send_char(int pid, unsigned char c);
static void action(int signal);
int	ready_to_receive = 0;

int	main(int ac, char *av[])
{
	char	*msg;
	int		pid;

	if (ac != 3)
	{
		ft_putstr_fd("Please provide PID and message\n", 1);
		exit(EXIT_FAILURE);
	}
	pid = validate_and_return_pid(av[1]);
	if (pid == -1)
		exit(EXIT_FAILURE);
	msg = av[2];
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	while (*msg)
	{
		send_char(pid, *msg);
		msg++;
	}
	send_char(pid, '\0');
	return (0);
}

static int	validate_and_return_pid(char *arg)
{
	int	pid;
	int	i;

	// if (ft_strlen(arg) != 6)
	// {
	// 	ft_putstr_fd("Not a valid PID\n", 1);
	// 	return (-1);
	// }
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
	pid = ft_atoi(arg);
	if (kill(pid, 0) == -1)
	{
		ft_putstr_fd("Invalid PID or process not exist\n", 1);
		return (-1);
	}
	return (pid);
}

static void	action(int signal)
{
	if (signal == SIGUSR1)
	{
		g_ready_to_receive = 1;
	}
	else if (signal == SIGUSR2)
	{
		ft_putstr_fd("Transmission completed, server terminates \n", 1);
		exit(EXIT_SUCCESS);
	}
}

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c & (1 << i)) == 0) //1 = 00000001, bitmask isolating the ith bit in c
			send_signal(pid, SIGUSR2);
		else
			send_signal(pid, SIGUSR1);
		i--;
		while (g_ready_to_receive == 0)
			usleep(100);
		g_ready_to_receive = 0;
	}
}
