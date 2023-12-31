/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:49:41 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/04 10:01:04 by jcodina-         ###   ########.fr       */
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
    IDLE,
    RCV_SIZE,
    RCV_MSG
}   e_t_server_state;

typedef struct s_server_data
{
    e_t_server_state    state;
    size_t              msg_size;
    char                *msg;
    int					client_pid;
}   t_server_data;

/* ************************************************************************** */
/*   Functions															      */
/* ************************************************************************** */

/*									SERVER COMMS							  */

void    		register_sig_handler(void);

/*									SERVER DATA							  */

t_server_data	*initialize_server_data();
void			free_server_data(t_server_data *server_data);
void			clear_server_data(t_server_data *server_data);


void	client_signal_handler(int signum, siginfo_t *info, void *context);
unsigned char	bin_to_char(int *bin);

#endif