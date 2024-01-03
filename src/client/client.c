/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/03 09:38:20 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_to_server(t_client_data *client_data)
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("Msg len: %d\n", (int) client_data->binary_msg_len);
	while (i < client_data->binary_msg_len)
	{
		j = 0;
		bin_to_char(client_data->binary_msg[i]);
		while (j < 8)
		{
			if (client_data->binary_msg[i][j] == 1)
				kill(client_data->server_pid, SIGUSR1);
			else if (client_data->binary_msg[i][j] == 0)
				kill(client_data->server_pid, SIGUSR2);
			wait_for_server_ack();
			j++;
		}
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
	print_tab(client_data->binary_msg, client_data->binary_msg_len);
	if (client_data->binary_msg == NULL)
	{
		ft_printf("Error creating binary message");
		return (1);
	}
	send_to_server(client_data);
	client_data_clean(client_data);
	return (0);
}
