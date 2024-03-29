/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 13:56:08 by jcodina-          #+#    #+#             */
/*   Updated: 2024/03/03 11:58:50 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
 * Calculates the power of a number.
*/
int	ft_pow(const int base, const int power)
{
	if (power == 1)
		return (base);
	else if (power == 0)
		return (1);
	else if (power < 0 || base == 0)
		return (0);
	return (base * ft_pow(base, power - 1));
}

long long	ft_powl(const long long base, const long long power)
{
	if (power == 1)
		return (base);
	else if (power == 0)
		return (1);
	else if (power < 0 || base == 0)
		return (0);
	return (base * ft_pow(base, power - 1));
}
