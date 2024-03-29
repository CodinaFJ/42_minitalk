/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:43 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 11:53:09 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

unsigned char	bin_to_char(int *bin)
{
	int	bit_index;
	int	c;

	c = 0;
	bit_index = 0;
	while (bit_index < 8)
	{
		if (bin[bit_index] == 1)
			c = (c << 1) | 1;
		else
			c = (c << 1);
		bit_index++;
	}
	return ((unsigned char) c);
}

int	main(void)
{
	ft_printf("Process PID: %d await for SIGUSR.\n", getpid());
	register_sig_handler();
	while (1)
		pause();
	exit(0);
}
