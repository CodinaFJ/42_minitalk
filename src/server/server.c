/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:43 by jcodina-          #+#    #+#             */
/*   Updated: 2024/01/03 10:59:38 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

struct t_server_data	g_server_data;

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

void	client_signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	*binary_char;

	(void) info;
	(void) context;
	if (bit == 0)
	{
		if (binary_char)
			free(binary_char);
		binary_char = (int *) ft_calloc(8, sizeof(int));
		if (!binary_char)
			return ;
	}
	if (signum == SIGUSR1)
		binary_char[bit] = 1;
	else if (signum == SIGUSR2)
		binary_char[bit] = 0;
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", bin_to_char(binary_char));
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

// !Probablemente para que funcione con UTF-16 haya que cambiar de char a wchar
int	main(void)
{
	int					pid;
	

	pid = getpid();
	ft_printf("Process PID: %d await for SIGUSR.\n", pid);
	register_sig_handler();
	while (1)
	{
		pause();
	}
	return (0);
}
