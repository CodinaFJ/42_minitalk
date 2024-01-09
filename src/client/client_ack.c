/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:36:52 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/09 19:29:04 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_bool	g_server_ack = false;

void	sig_ack_handler(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	g_server_ack= true;
}

void	wait_for_server_ack(int pid)
{
	int	timer;
	int	delta_timer;

	timer = 0;
	delta_timer = 0;
	while (true)
	{
		usleep(1);
		if (g_server_ack == true)
		{
			g_server_ack = false;
			return ;
		}
		if (delta_timer > 100000)
		{
			kill(pid, SIGUSR1);
			ft_printf("Server busy\n");
			delta_timer = 0;	
		}
		if (timer > TIMEOUT)
		{
			ft_printf("TIMEOUT - No acknowledge from server after %d seconds."
				" Wrong PID?\n", TIMEOUT / 100000);
			exit(1);
		}
		delta_timer++;
		timer++;
	}
}
