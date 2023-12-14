/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:14:29 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/14 13:05:09 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	matrix_clean(int **matrix, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	print_arr(int *arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		ft_printf("%d", arr[i]);
		i++;
	}
}

void	print_tab(int **tab, size_t len)
{
	size_t	i;

	i = 0;
	ft_printf("\nPRINT TAB\n---------\n");
	while (i < len)
	{
		print_arr(tab[i], 8);
		ft_printf("\n");
		i++;
	}
	ft_printf("---------\n");
}
