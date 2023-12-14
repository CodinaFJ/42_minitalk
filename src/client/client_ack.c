/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_ack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:36:52 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/14 13:24:37 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

extern t_client_data	g_client_data;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	g_client_data.ack = true;
}

void	wait_for_server_ack()
{
	int	timer;

	timer = 0;
	while (true)
	{
		usleep(1);
		if (g_client_data.ack == true)
		{
			g_client_data.ack = false;
			return ;
		}
		if (timer > TIMEOUT)
		{
			ft_printf("TIMEOUT - No acknowledge from server after %d seconds."
				" Wrong PID?\n", TIMEOUT / 100000);
			exit(1);
		}
		timer++;
	}
}