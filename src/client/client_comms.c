/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_comms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:46 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/03 09:51:34 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	register_sig_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_ack_handler;
	sigaction(SIGUSR1, &sa, NULL);
}
