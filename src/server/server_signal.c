/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:57:19 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 12:20:36 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	idle_signal_handler(int signum, int pid, t_server_data *server_data)
{
	(void) signum;
	if (signum != SIGUSR1)
		ft_printf("[ERROR] Incompatible signal with server state");
	server_data->state = RCV_SIZE;
	server_data->client_pid = pid;
	kill(pid, SIGUSR1);
}

void	rcv_size_signal_handler(int signum, int pid, t_server_data *server_data)
{
	static size_t	bit = 0;

	if (signum == SIGUSR1)
		server_data->msg_size += ft_pow(2, 8 * sizeof(size_t) - bit - 1);
	bit++;
	if (bit >= 8 * sizeof(size_t))
	{
		if (server_data->msg_size == 0)
			clear_server_data(server_data);
		else
		{
			server_data->state = RCV_MSG;
			server_data->msg = malloc(server_data->msg_size + 1);
			if (server_data->msg == NULL)
				error_exit("[ERROR] Fail message memory allocation");
			ft_bzero(server_data->msg, server_data->msg_size + 1);
		}
		bit = 0;
	}
	kill(pid, SIGUSR1);
}

void	rcv_char(int signum, t_server_data *server_data)
{
	static int	bit = 0;
	static int	*binary_char;
	char		c;

	if (bit == 0)
	{
		binary_char = (int *) ft_calloc(8, sizeof(int));
		if (!binary_char)
			error_exit("[ERROR] Memory allocation");
	}
	if (signum == SIGUSR1)
		binary_char[bit] = 1;
	else if (signum == SIGUSR2)
		binary_char[bit] = 0;
	bit++;
	if (bit == 8)
	{
		c = (char) bin_to_char(binary_char);
		ft_strncat(server_data->msg, &c, 1);
		bit = 0;
		if (binary_char)
			free(binary_char);
	}
}

void	rcv_msg_signal_handler(int signum, int pid, t_server_data *server_data)
{
	rcv_char(signum, server_data);
	if (ft_strlen(server_data->msg) >= server_data->msg_size)
	{
		ft_printf("%s\n", server_data->msg);
		clear_server_data(server_data);
		kill(pid, SIGUSR1);
		return ;
	}
	kill(pid, SIGUSR1);
}

void	client_signal_handler(int signum, siginfo_t *info, void *context)
{
	int						pid;
	static t_server_data	*server_data;

	(void) context;
	if (server_data == NULL)
	{
		server_data = initialize_server_data();
		if (server_data == NULL)
			error_exit("[ERROR] Memory allocation");
	}
	pid = info->si_pid;
	if (server_data->state == IDLE)
		idle_signal_handler(signum, pid, server_data);
	else if (pid != server_data->client_pid || pid == 0)
		return ;
	else if (server_data->state == RCV_SIZE)
		rcv_size_signal_handler(signum, pid, server_data);
	else if (server_data->state == RCV_MSG)
		rcv_msg_signal_handler(signum, pid, server_data);
}
