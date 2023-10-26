/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2023/10/26 22:06:50 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../../lib/ft_printf/ft_printf.h"
#include "../../lib/libft/libft.h"

int	*char_to_bin(char c);

int	**str_to_bin(char *str)
{
	int	**result;
	int	len;
	int	byte_index;

	len = strlen(str);
	byte_index = 0;
	result = (int **) calloc(len, sizeof(int *));
	if (!result)
		return (0);
	while (byte_index < len)
	{
		*(result + byte_index) = char_to_bin(str[byte_index]);
		if (!result[byte_index])
			return (0);
		// TODO: aquí hay que liberar toda la memoria, que me como leaks si no
		byte_index++;
	}
	return (result);
}

int	*char_to_bin(char c)
{
	int		bit_index;
	int		*bin_arr;
	int		i;

	bin_arr = (int *) calloc(8, sizeof(int));
	if (!bin_arr)
		return (0);
	bit_index = 7;
	i = 0;
	while (bit_index >= 0)
	{
		bin_arr[i++] = (c >> bit_index) & 1;
		bit_index--;
	}
	return (bin_arr);
}

void	send_to_server(int pid, int **binary_msg, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		printf("\nWord %d of %d:\n\n", i + 1, len);
		j = 0;
		while (j < 8)
		{
			if (binary_msg[i][j] == 1)
			{
				printf("Send 1\n");
				kill(pid, SIGUSR1);
			}
			else if (binary_msg[i][j] == 0)
			{
				printf("Send 0\n");
				kill(pid, SIGUSR2);
			}
			usleep(100); // ? Esto por qué
			// TODO: gestionar error si da otro número aquí 
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	**result;

	if (argc != 3)
	{
		ft_printf("Wrong parameters. Input:\n[1] SERVER PID\n[2] MESSAGE");
		return (-1);
	}
	result = str_to_bin(argv[2]);
	send_to_server(ft_atoi(argv[1]), str_to_bin(argv[2]), ft_strlen(argv[2]));
	return (0);
}
