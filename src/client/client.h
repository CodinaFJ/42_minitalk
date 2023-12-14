/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:42 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/14 13:29:39 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "../../lib/ft_printf/ft_printf.h"
# include "../../lib/libft/libft.h"

# define TIMEOUT 500000

/* ************************************************************************** */
/*   Typedefs															      */
/* ************************************************************************** */

/*									ENUMS									*/

typedef enum
{
	true = 1,
	false = 0
}	t_bool;

/*									STRUCTS									*/

typedef struct s_client_data
{
	t_bool	ack;
	int		server_pid;
	int		**binary_msg;
	size_t	binary_msg_len;
}	t_client_data;

/* ************************************************************************** */
/*   Functions															      */
/* ************************************************************************** */

/*									CLIENT COMMS							  */

void			register_sig_handler(void);

/*									CLIENT ACK								  */

void			wait_for_server_ack(void);
void			sig_handler(int signum, siginfo_t *info, void *context);

/*									CLIENT DATA								  */

void			client_data_init(char *pid, char *msg);
void			client_data_clean(t_client_data *client_data);

/*									MATRIX									  */

void			matrix_clean(int **matrix, int len);
void			print_tab(int **tab, size_t len);
void			print_arr(int *arr, size_t len);

/*									TO BINARY								  */

int				**str_to_bin(char *str);
unsigned char	bin_to_char(int *bin);

#endif