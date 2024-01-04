/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:57:19 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/04 10:18:03 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

extern t_server_data	*g_server_data;

void    register_sig_handler(void)
{
    struct sigaction	sa;
    
    sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = client_signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

void	idle_signal_handler(int signum, siginfo_t *info)
{
	(void) signum;
	if (signum != SIGUSR1)
		ft_printf("[ERROR] Incompatible signal with server state\n");
	g_server_data->state = RCV_SIZE;
	g_server_data->client_pid = info->si_pid;
	kill(info->si_pid, SIGUSR1);
}

void	rcv_size_signal_handler(int signum, siginfo_t *info)
{
	static size_t bit = 0;
	
	
	if (info->si_pid != g_server_data->client_pid)
		return ;
	if (signum == SIGUSR1)
		g_server_data->msg_size += ft_pow(2, 8 * sizeof(size_t) - bit - 1);
	bit++;
	if (bit >= 8 * sizeof(size_t))
	{
		g_server_data->state = RCV_MSG;
		g_server_data->msg = malloc(g_server_data->msg_size + 1);
		if (g_server_data->msg == NULL)
		{
			ft_printf("[ERROR] Fail message memory allocation\n");
			return ;
		}
		ft_bzero(g_server_data->msg, g_server_data->msg_size + 1);
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	rcv_char(int signum)
{
	static int	bit = 0;
	static int	*binary_char;
	char		c;

	if (bit == 0)
	{
		binary_char = (int *) ft_calloc(8, sizeof(int));
		if (!binary_char)
			return ;
	}
	if (signum == SIGUSR1)
		binary_char[bit] = 1;
	else if (signum == SIGUSR2)
		binary_char[bit] = 0;
	bit++;
	if (bit == 8)
	{
		c = (char) bin_to_char(binary_char);
		ft_strncat(g_server_data->msg, &c, 1);
		bit = 0;
		if (binary_char)
			free(binary_char);
	}
}

void	rcv_msg_signal_handler(int signum, siginfo_t *info)
{
	if (info->si_pid != g_server_data->client_pid)
		return ;
	rcv_char(signum);
	if (ft_strlen(g_server_data->msg) >= g_server_data->msg_size)
	{
		ft_printf("%s", g_server_data->msg);
		clear_server_data(g_server_data);
	}
	kill(info->si_pid, SIGUSR1);
}

void	client_signal_handler(int signum, siginfo_t *info, void *context)
{
	(void) context;
	if (g_server_data->state == IDLE)
		idle_signal_handler(signum, info);
	else if(g_server_data->state == RCV_SIZE)
		rcv_size_signal_handler(signum, info);
	else if (g_server_data->state == RCV_MSG)
		rcv_msg_signal_handler(signum, info);
}