/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:05:36 by trpham            #+#    #+#             */
/*   Updated: 2025/03/12 11:59:00 by trpham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("Sending signal failed\n", 1);
		exit(EXIT_FAILURE);
	}
}
