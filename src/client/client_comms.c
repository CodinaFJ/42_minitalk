/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_comms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:46 by jcodina-          #+#    #+#             */
/*   Updated: 2023/11/02 17:17:06 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_ack = FALSE;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void) signum;
	(void) info;
	(void) context;
	g_ack = TRUE;
}

void	wait_for_server_ack(void)
{
	int	k;

	k = 0;
	while (TRUE)
	{
		usleep(1);
		if (g_ack == TRUE)
		{
			g_ack = FALSE;
			break ;
		}
		if (k > TIMEOUT)
		{
			ft_printf("TIMEOUT - No acknowledge from server after %d seconds."
				" Wrong PID?\n", TIMEOUT / 100000);
			exit(1);
		}
		k++;
	}
}

void	register_sig_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
}
