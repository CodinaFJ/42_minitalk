/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2023/10/24 20:15:45 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../../lib/ft_printf/ft_printf.h"
#include "../../lib/libft/libft.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Wrong number of parameters. Needed server PID input");
        return (-1);
    }
    kill(ft_atoi(argv[1]), SIGUSR1);

    return (0);
}