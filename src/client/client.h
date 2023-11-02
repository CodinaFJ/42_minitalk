/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:42 by jcodina-          #+#    #+#             */
/*   Updated: 2023/11/02 17:16:34 by jcodina-         ###   ########.fr       */
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
# define TRUE 1
# define FALSE 0

void	register_sig_handler(void);
void	wait_for_server_ack(void);

#endif