/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:39:13 by trpham            #+#    #+#             */
/*   Updated: 2025/03/11 15:21:54 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_message(int pid, char *message);
static int validate_and_return_PID(char *arg);
static void action(int signal);

int	main(int ac, char *av[])
{
	char	*msg;
	// int		i;
	int		PID;

	if (ac != 3)
	{
		ft_putstr_fd("Please provide PID and message\n", 1);
		exit(EXIT_FAILURE);
	}
	PID = validate_and_return_PID(av[1]);
	if (PID == -1)
		exit(EXIT_FAILURE);
	msg = av[2];
	
	send_signal(PID, SIGUSR1); //signal start of communication
	printf("Initiate communication successfully\n");
	
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	
	send_message(PID, msg);

	// i = 0;
	// while (msg[i])
	// {
	// 	send_signal(PID, msg[i]);	
	// 	i++;
	// }
	// kill(PID, '\0');
	return (0);
}

static void	send_message(int pid, char *message)
{
	int	i;
	unsigned char	c; //1 unsign char is 8 bits to write, sign char has 1 sign bit

	while (*message)
	{
		c = *message;
		printf("Sending character %c\n", c);
		i = 7;
		while (i >= 0)
		{
			if ((c & (1 << i)) == 0)
			{
				send_signal(pid, SIGUSR2);
				// printf("Send 0 \n");
				// kill(pid, SIGUSR2); // 1 = 00000001, bitmask isolating the ith bit in c
			} 
			else
			{
				send_signal(pid, SIGUSR1);
				// kill(pid, SIGUSR1);
				// printf("Send 1\n");
			}
			i--;
			usleep(100); 
		}
		message++;
	}
	send_signal(pid, SIGUSR2); //sending termination signal 0
}

static int validate_and_return_PID(char *arg)
{
	int	PID;
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
	PID = ft_atoi(arg);
	if (kill(PID, 0) == -1)
	{
		ft_putstr_fd("Invalid PID or process not exist\n", 1);
		return (-1);
	}
	return (PID);
}

static void action(int signal)
{
	static int	ready_to_receive;

	if (signal == SIGUSR1)
	{
		// printf("Server received transmited bit %d\n", signal);
		ready_to_receive = 1;
	}
		// kill(getpid(), SIGUSR1);
	else if (signal == SIGUSR2)
	{
		if (ready_to_receive)
		{
			printf("Server send termination \n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("server ready to receive first communication \n");
			// exit(EXIT_FAILURE);
		}
		// kill(getpid(), SIGUSR2);

		// ft_putnbr_fd(received, 1);
		// exit(0);
	}
}


/* 
Potential problem with signal transmission
1. timing issue / signal loss: 
	usleep: suspends execution for at least x microsecond --> return 0 on success
2. server's signal handling logic: 
3. validation: send to client after each byte is received. how?
4. check if pid is correct by sending a check to pid: kill return 0 if success else -1
 */
