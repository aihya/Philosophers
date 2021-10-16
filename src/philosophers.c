/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:53:27 by aihya             #+#    #+#             */
/*   Updated: 2021/10/16 18:41:52 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t g_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

void    init_forks()
{
    int i;

    g_orch.forks = malloc(sizeof(pthread_mutex_t) * g_orch.np);
    i = -1;
    while (++i < g_orch.np)
        pthread_mutex_init(&g_orch.forks[i], NULL);
}

void    init_philos()
{
    int i;

    g_orch.philos = malloc(sizeof(t_philo) * g_orch.np);
    i = -1;
    while (++i < g_orch.np)
    {
        g_orch.philos[i].te = getcurrenttime();
        g_orch.philos[i].id = i;
    }
}

void    init(char **argv)
{
    g_orch.np = atoi(argv[1]);
    g_orch.td = atoi(argv[2]);
    g_orch.te = atoi(argv[3]) * 1000;
    g_orch.ts = atoi(argv[4]) * 1000;
    init_forks();
    init_philos();
    pthread_mutex_init(&g_orch.output, NULL);
}

int    main(int argc, char** argv)
{
    int ret;

    if (argc != 5)
        return (-1);
    g_orch.timeref = getcurrenttime();
    init(argv);
    dead = 0;
    threads_master();
    if (dead)
	    feedback(dead, "\x1b[31mDEAD\x1b[0m");
    return (0);
}
