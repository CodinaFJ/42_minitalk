/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:14:06 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/04 10:00:22 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server_data	*initialize_server_data()
{
	t_server_data	*server_data;
	
	server_data = ft_calloc(1, sizeof(t_server_data));
	if (server_data == NULL)
		return (NULL);
	ft_bzero(server_data, sizeof(t_server_data));
	server_data->state = IDLE;
	return (server_data);
}

void	free_server_data(t_server_data *server_data)
{
	if (!server_data)
		return ;
	if (server_data->msg)
		free(server_data->msg);
	free(server_data);
}

void	clear_server_data(t_server_data *server_data)
{
	if (!server_data)
		return ;
	if (server_data->msg)
		free(server_data->msg);
	ft_bzero(server_data, sizeof(t_server_data));
	server_data->state = IDLE;
}
