/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:49:41 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 12:19:32 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "../../lib/ft_printf/ft_printf.h"
# include "../../lib/libft/includes/libft.h"

/* ************************************************************************** */
/*   Typedefs															      */
/* ************************************************************************** */

typedef enum e_server_state
{
	IDLE = 0,
	RCV_SIZE = 1,
	RCV_MSG = 2
}	t_server_state;

typedef struct s_server_data
{
	t_server_state	state;
	size_t			msg_size;
	char			*msg;
	int				client_pid;
}	t_server_data;

/* ************************************************************************** */
/*   Functions															      */
/* ************************************************************************** */

/*									SERVER COMMS							  */

void			register_sig_handler(void);
void			client_signal_handler(int signum, siginfo_t *info, void *ctx);
unsigned char	bin_to_char(int *bin);

/*									SERVER DATA							  */

t_server_data	*initialize_server_data(void);
void			free_server_data(t_server_data *server_data);
void			clear_server_data(t_server_data *server_data);

/*									ERROR								  */

void			error_exit(char *error_msg);

#endif