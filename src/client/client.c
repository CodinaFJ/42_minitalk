/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 14:22:36 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_tab(int *tab, size_t size, int pid)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				error_exit("Error sending");
		}
		else if (tab[i] == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				error_exit("Error sending");
		}
		wait_for_server_ack(pid, SIGUSR2 - tab[i]);
		i++;
	}
}

void	send_size_to_server(size_t msg_size, int pid)
{
	int		*size_bin_tab;
	int		bit_index;
	size_t	i;

	size_bin_tab = ft_calloc(8 * sizeof(size_t), sizeof(int));
	if (size_bin_tab == NULL)
		error_exit("[ERROR] Memory allocation");
	i = -1;
	bit_index = 8 * sizeof(size_t) - 1;
	while (++i < 8 * sizeof(size_t))
	{
		size_bin_tab[i] = (msg_size >> bit_index) & 1;
		bit_index--;
	}
	if (kill(pid, SIGUSR1) == -1)
		error_exit("Error sending");
	wait_for_server_ack(pid, SIGUSR1);
	send_tab(size_bin_tab, 8 * sizeof(size_t), pid);
	free(size_bin_tab);
}

void	send_msg_to_server(t_client_data *client_data)
{
	size_t	i;

	i = 0;
	while (i < client_data->msg_len)
	{
		send_tab(client_data->binary_msg[i], 8, client_data->server_pid);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_client_data	*client_data;

	if (argc != 3 || ft_atoi(argv[1]) == 0)
		error_exit("Wrong parameters. Input:\n[1] SERVER PID\n[2] MESSAGE");
	client_data = client_data_init(argv[1], argv[2]);
	register_sig_handler();
	if (client_data->binary_msg == NULL)
		error_exit("Error creating binary message");
	send_size_to_server(client_data->msg_len, client_data->server_pid);
	if (client_data->msg_len > 0)
		send_msg_to_server(client_data);
	client_data_clean(client_data);
	return (0);
}
