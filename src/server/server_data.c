/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:14:06 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/10 19:40:46 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server_data	*initialize_server_data(void)
{
	t_server_data	*server_data;

	server_data = ft_calloc(1, sizeof(t_server_data));
	if (server_data == NULL)
		return (NULL);
	ft_bzero(server_data, sizeof(t_server_data));
	server_data->client_queue = NULL;
	server_data->state = IDLE;
	server_data->client_pid = 0;
	return (server_data);
}

void	free_server_data(t_server_data *server_data)
{
	if (!server_data)
		return ;
	if (server_data->msg)
		free(server_data->msg);
	if (server_data->client_queue != NULL)
		ft_lstclear(&(server_data->client_queue), free);
	free(server_data);
}

void	clear_client_data(t_server_data *server_data)
{
	if (!server_data)
		return ;
	if (server_data->msg)
		free(server_data->msg);
	server_data->msg_size = 0;
	server_data->client_pid = 0;
	server_data->state = IDLE;
}
