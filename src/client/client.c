/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <jcodina-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 19:54:51 by jcodina-          #+#    #+#             */
/*   Updated: 2023/10/24 19:54:52 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Función de manejo de señales
void signal_handler(int signal) {
    printf("Se recibió la señal %d (Ctrl+C).\n", signal);
    exit(1);
}

int main()
{
    int pid;
    // Registra la función de manejo de señales para SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
        printf("No se pudo establecer un manejador de señales.\n");
        return (1);
    }

    pid = getpid();
    printf("Este programa con PID: %d espera una señal SIGINT (Ctrl+C).\n", pid);

    while (1)
    {
        // El programa se ejecutará en un bucle infinito hasta que se reciba SIGINT
    }
    
    return (0);
}