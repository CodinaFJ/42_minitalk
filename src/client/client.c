/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2023/11/02 17:42:50 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	clean_matrix(int **matrix, int stop_index)
{
	int	i;

	i = 0;
	while (i < stop_index)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	*char_to_bin(char c)
{
	int		bit_index;
	int		*bin_arr;
	int		i;

	bin_arr = (int *) ft_calloc(8, sizeof(int));
	if (!bin_arr)
		return (NULL);
	bit_index = 7;
	i = 0;
	while (bit_index >= 0)
	{
		bin_arr[i++] = (c >> bit_index) & 1;
		bit_index--;
	}
	return (bin_arr);
}

int	**str_to_bin(char *str)
{
	int	**result;
	int	len;
	int	byte_index;

	len = strlen(str);
	byte_index = 0;
	result = (int **) ft_calloc(len, sizeof(int *));
	if (!result)
		return (0);
	while (byte_index < len)
	{
		*(result + byte_index) = char_to_bin(str[byte_index]);
		if (*(result + byte_index) == NULL)
		{
			clean_matrix(result, byte_index);
			return (NULL);
		}
		byte_index++;
	}
	return (result);
}

void	send_to_server(int pid, int **binary_msg, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < 8)
		{
			if (binary_msg[i][j] == 1)
				kill(pid, SIGUSR1);
			else if (binary_msg[i][j] == 0)
				kill(pid, SIGUSR2);
			wait_for_server_ack();
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	**binary_message;

	if (argc != 3)
	{
		ft_printf("Wrong parameters. Input:\n[1] SERVER PID\n[2] MESSAGE\n");
		return (1);
	}
	register_sig_handler();
	binary_message = str_to_bin(argv[2]);
	if (binary_message == NULL)
		return (1);
	send_to_server(ft_atoi(argv[1]), binary_message, ft_strlen(argv[2]));
	return (0);
}
