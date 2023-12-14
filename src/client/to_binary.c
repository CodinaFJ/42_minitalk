/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:16:08 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/14 13:28:51 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
		return (NULL);
	while (byte_index < len)
	{
		*(result + byte_index) = char_to_bin(str[byte_index]);
		if (*(result + byte_index) == NULL)
		{
			matrix_clean(result, byte_index);
			return (NULL);
		}
		byte_index++;
	}
	return (result);
}

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
	ft_printf("%c", c);
	return ((unsigned char) c);
}
