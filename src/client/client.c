/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/03 10:36:02 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_tab(int *tab, size_t size, int pid)
{
	size_t i;
	
	i = 0;
	while (i < size)
	{
		if (tab[i] == 1)
			kill(pid, SIGUSR1);
		else if (tab[i] == 0)
			kill(pid, SIGUSR2);
		wait_for_server_ack();
		i++;
	}
}

void	send_size_to_server(size_t msg_size, int pid)
{
	int		*size_bin_tab;
	int		bit_index;
	size_t	i;

	size_bin_tab = ft_calloc(8 * sizeof(size_t), sizeof(int));
	i = 0;
	bit_index = 8 * sizeof(size_t) - 1;
	while (i < 8 * sizeof(size_t))
	{
		size_bin_tab[i] = (msg_size >> bit_index) & 1;
		i++;
		bit_index--;
	}
	print_arr(size_bin_tab, 8 * sizeof(size_t));
	ft_printf("\n");
	kill(pid, SIGUSR1);
	wait_for_server_ack();
	send_tab(size_bin_tab, 8 * sizeof(size_t), pid);
}

void	send_msg_to_server(t_client_data *client_data)
{
	size_t	i;

	i = 0;
	ft_printf("Msg len: %d\n", (int) client_data->msg_len);
	while (i < client_data->msg_len)
	{
		//bin_to_int(client_data->binary_msg[i]);
		send_tab(client_data->binary_msg[i], 8, client_data->server_pid);
		i++;
	}
}

// !Probablemente para que funcione con UTF-16 haya que cambiar de char a wchar
int	main(int argc, char **argv)
{
	t_client_data	*client_data;
	if (argc != 3)
	{
		ft_printf("Wrong parameters. Input:\n[1] SERVER PID\n[2] MESSAGE\n");
		return (1);
	}
	client_data = client_data_init(argv[1], argv[2]);
	register_sig_handler();
	print_tab(client_data->binary_msg, client_data->msg_len);
	if (client_data->binary_msg == NULL)
	{
		ft_printf("Error creating binary message");
		return (1);
	}
	send_size_to_server(client_data->msg_len, client_data->server_pid);
	send_msg_to_server(client_data);
	client_data_clean(client_data);
	return (0);
}
