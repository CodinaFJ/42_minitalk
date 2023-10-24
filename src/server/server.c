/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:43 by jcodina-          #+#    #+#             */
/*   Updated: 2023/10/24 19:54:44 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "../../lib/libft/libft.h"
#include "../../lib/ft_printf/ft_printf.h"

// Función de manejo de señales
void signal_handler(int signal) {
    ft_printf("Se recibió la señal %d (Ctrl+C).\n", signal);
    exit(1);
}

void    client_signal_handler(int signum, siginfo_t* info, void* context)
{
    ft_printf("Client contacted\n");
}

int main()
{
    int pid;
    // Registra la función de manejo de señales para SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
        ft_printf("No se pudo establecer un manejador de señales.\n");
        return (1);
    }

    pid = getpid();
    ft_printf("Este programa con PID: %d espera una señal SIGINT (Ctrl+C).\n", pid);

    while (1)
    {
        // El programa se ejecutará en un bucle infinito hasta que se reciba SIGINT
    }
    
    return (0);
}
