/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:57:19 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/10 19:44:38 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

extern t_server_data	*g_server_data;

void	idle_signal_handler(int signum, int pid)
{
	(void) signum;
	if (signum != SIGUSR1)
		ft_printf("[ERROR] Incompatible signal with server state\n");
	g_server_data->state = RCV_SIZE;
	g_server_data->client_pid = pid;
	kill(pid, SIGUSR1);
}

void	rcv_size_signal_handler(int signum, int pid)
{
	static size_t	bit = 0;

	if (signum == SIGUSR1)
		g_server_data->msg_size += ft_pow(2, 8 * sizeof(size_t) - bit - 1);
	bit++;
	if (bit >= 8 * sizeof(size_t))
	{
		if (g_server_data->msg_size == 0)
			clear_client_data(g_server_data);
		else
		{
			g_server_data->state = RCV_MSG;
			g_server_data->msg = malloc(g_server_data->msg_size + 1);
			if (g_server_data->msg == NULL)
			{
				ft_printf("[ERROR] Fail message memory allocation\n");
				return ;
			}
			ft_bzero(g_server_data->msg, g_server_data->msg_size + 1);
		}
		bit = 0;
	}
	kill(pid, SIGUSR1);
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

void	rcv_msg_signal_handler(int signum, int pid)
{
	rcv_char(signum);
	if (ft_strlen(g_server_data->msg) >= g_server_data->msg_size)
	{
		ft_printf("%s\n", g_server_data->msg);
		clear_client_data(g_server_data);
		kill(pid, SIGUSR1);
		return ;
	}
	kill(pid, SIGUSR1);
}

void	client_signal_handler(int signum, siginfo_t *info, void *context)
{
	int		pid;

	(void) context;
	pid = info->si_pid;
	if (g_server_data->state == IDLE)
		idle_signal_handler(signum, pid);
	else if (pid != g_server_data->client_pid || pid == 0)
		return ;
	else if (g_server_data->state == RCV_SIZE)
		rcv_size_signal_handler(signum, pid);
	else if (g_server_data->state == RCV_MSG)
		rcv_msg_signal_handler(signum, pid);
}
