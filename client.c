/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:39:13 by trpham            #+#    #+#             */
/*   Updated: 2025/03/07 16:33:48 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_signal(int	pid, unsigned char c);
bool		ready_to_receive = false;

int	main(int ac, char *av[])
{
	char	*msg;
	int		i;

	if (ac != 3)
	{
		ft_putstr_fd("Please provide PID and message\n", 1);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(av[1]) != 6)
	{
		ft_putstr_fd("Not a valid PID\n", 1);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (av[1][i])
	{
		if (ft_isdigit(av[1][i]) == -1)
		{
			ft_putstr_fd("Not a valid PID\n", 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	msg = av[2];
	i = 0;
	while (msg[i])
	{
		if (!ready_to_receive)
			pause()
		send_signal(ft_atoi(av[1]), msg[i]);
		i++;
	}
	
	return (0);
}

void	send_signal(int	pid, unsigned char c)
{
	int				i;

	i = 7;
	while (i >= 0)
	{
		if ((c & (1 << i)) == 0)
		{
			kill(pid, SIGUSR2); // 1 = 00000001, bitmask isolating the ith bit in c
		} 
		else
		{
			kill(pid, SIGUSR1);
		}
		i--;
		usleep(500);
	}
	write(1, "\n", 1);
}
