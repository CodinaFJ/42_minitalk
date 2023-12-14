/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/14 13:33:17 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client_data	g_client_data;

void	send_to_server()
{
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("Msg len: %d\n", (int) g_client_data.binary_msg_len);
	while (i < g_client_data.binary_msg_len)
	{
		j = 0;
		bin_to_char(g_client_data.binary_msg[i]);
		while (j < 8)
		{
			if (g_client_data.binary_msg[i][j] == 1)
				kill(g_client_data.server_pid, SIGUSR1);
			else if (g_client_data.binary_msg[i][j] == 0)
				kill(g_client_data.server_pid, SIGUSR2);
			wait_for_server_ack();
			j++;
		}
		i++;
	}
}

// !Probablemente para que funcione con UTF-16 haya que cambiar de char a wchar
int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Wrong parameters. Input:\n[1] SERVER PID\n[2] MESSAGE\n");
		return (1);
	}
	client_data_init(argv[1], argv[2]);
	register_sig_handler();
	print_tab(g_client_data.binary_msg, g_client_data.binary_msg_len);
	if (g_client_data.binary_msg == NULL)
	{
		ft_printf("Error creating binary message");
		return (1);
	}
	send_to_server();
	return (0);
}
