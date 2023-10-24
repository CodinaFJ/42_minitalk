/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:43 by jcodina-          #+#    #+#             */
/*   Updated: 2023/10/24 20:17:52 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../../lib/libft/libft.h"
#include "../../lib/ft_printf/ft_printf.h"

void    client_signal_handler(int signum, siginfo_t* info, void* context)
{
	(void)	signum;
	(void)	info;
	(void)	context;
    ft_printf("Client contacted\n");
}

int main()
{
    int					pid;
    struct sigaction	sa;

    pid = getpid();
    ft_printf("Process PID: %d await for SIGUSR.\n", pid);
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART | SA_SIGINFO;
   sa.sa_sigaction = client_signal_handler;
   sigaction(SIGUSR1, &sa, NULL);
   while (1)
     sleep(1);
   return (0);
    
    return (0);
}
