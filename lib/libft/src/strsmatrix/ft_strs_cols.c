/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_cols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:46:52 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 11:59:52 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * Calculates the number of columns of a constant columns length matrix of
 * strings.
*/
unsigned int	ft_strs_cols(const char **strs)
{
	return (ft_strlen(strs[0]));
}
