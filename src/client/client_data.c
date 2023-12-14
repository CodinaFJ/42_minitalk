/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:01:09 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/14 13:21:58 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

extern t_client_data g_client_data;

void	client_data_init(char *pid, char *msg)
{
	ft_bzero(&g_client_data, sizeof(t_client_data));
	g_client_data.ack = false;
	g_client_data.server_pid = ft_atoi(pid);
	g_client_data.binary_msg = str_to_bin(msg);
	g_client_data.binary_msg_len = ft_strlen(msg);
}

void	client_data_clean(t_client_data *client_data)
{
	matrix_clean(client_data->binary_msg, client_data->binary_msg_len);
	free(client_data);
}