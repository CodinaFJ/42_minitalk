/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:01:09 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 12:33:02 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client_data	*client_data_init(char *pid, char *msg)
{
	t_client_data	*client_data;

	client_data = ft_calloc(1, sizeof(t_client_data));
	if (client_data == NULL)
		error_exit("[ERROR] Memory allocation error");
	client_data->ack = false;
	client_data->server_pid = ft_atoi(pid);
	client_data->binary_msg = str_to_bin(msg);
	if (client_data->binary_msg == NULL)
		error_exit("[ERROR] Memory allocation error");
	client_data->msg_len = ft_strlen(msg);
	return (client_data);
}

void	client_data_clean(t_client_data *client_data)
{
	matrix_clean(client_data->binary_msg, client_data->msg_len);
	free(client_data);
}
