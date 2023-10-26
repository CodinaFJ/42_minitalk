/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:34:01 by jcodina-          #+#    #+#             */
/*   Updated: 2023/10/26 20:42:58 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int	*char_to_bin(char c);

int **str_to_bin(char *str)
{
	int **result;
	int len;
	int byte_index;
	
	len = strlen(str);
	result = (int **) calloc(len, sizeof(int *));
	byte_index = 0;
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

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	char *str = argv[1];
	int **result = str_to_bin(str);
	int	len = strlen(str);
	if (result != 0)
	{
		printf("Convert %s to bin -> \n", str);
		for (int i = 0; i < len ; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				printf("%d", result[i][j]);
			}
			printf("\n");
		}
		free(str);
	}
	return (0);
}