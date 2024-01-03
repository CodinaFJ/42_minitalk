/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:01:09 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/03 09:34:15 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client_data	*client_data_init(char *pid, char *msg)
{
	t_client_data	*client_data;
	
	client_data = malloc(sizeof(t_client_data));
	ft_bzero(client_data, sizeof(t_client_data));
	client_data->ack = false;
	client_data->server_pid = ft_atoi(pid);
	client_data->binary_msg = str_to_bin(msg);
	client_data->binary_msg_len = ft_strlen(msg);
	return (client_data);
}

void	client_data_clean(t_client_data *client_data)
{
	matrix_clean(client_data->binary_msg, client_data->binary_msg_len);
	free(client_data);
}