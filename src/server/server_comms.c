/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_comms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:57:19 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/03 10:58:36 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void    register_sig_handler(void)
{
    struct sigaction	sa;
    
    sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = client_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}