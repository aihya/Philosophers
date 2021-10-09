/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:26:28 by aihya             #+#    #+#             */
/*   Updated: 2021/10/09 19:39:40 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void     feedback(int id, char* msg)
{

    pthread_mutex_lock(&g_orch.output);
    printf("%ldms\t%d %ld %s \n", timestamp(), id, g_orch.philos[id].td, msg);
    pthread_mutex_unlock(&g_orch.output);
}

void    lock(int side, t_philo* p)
{
    pthread_mutex_lock(&g_orch.forks[(p->id + side) % g_orch.np]);
}

void    pick_forks(t_philo* p)
{
    if (p->id % 2 == 0)
    {
        lock(L, p);
        feedback(p->id, "picked L fork");
        lock(R, p);
        feedback(p->id, "picked R fork");
    }
    else
    {
        lock(R, p);
        feedback(p->id, "picked R fork");
        lock(L, p);
        feedback(p->id, "picked L fork");
    }
}

void    unlock(int side, t_philo* p)
{
    pthread_mutex_unlock(&g_orch.forks[(p->id + side) % g_orch.np]);
}

void    drop_forks(t_philo* p)
{
    unlock(L, p);
    unlock(R, p);
}

void    eating(t_philo* p)
{
    pick_forks(p);
    p->td += g_orch.td;
    feedback(p->id, "is \x1b[32meating\x1b[0m");
    usleep(g_orch.te);
    drop_forks(p);
}

void     sleeping(t_philo* p)
{
    feedback(p->id, "is \x1b[33msleeping\x1b[0m");
    usleep(g_orch.ts);
}

void     thinking(t_philo* p)
{
    feedback(p->id, "is \x1b[34mthinking\x1b[0m");
}

void*    thread(void* arg)
{
    t_philo *p;

    p = (t_philo*)arg;
    if (p)
    {
        p->td = getcurrenttime() + g_orch.td;
        while (TRUE)
        {
            eating(p);
            sleeping(p);
            thinking(p);
        }
    }
    return (NULL);
}

void*   watcher(void* args)
{
    int i;
    int z;

    z = g_orch.np;
    while (TRUE)
    {
        i = -1;
        while (++i < z)
        {
            if (getcurrenttime() < g_orch.philos[i].td)
            {
                feedback(i, "DEAD");
                exit(-1);
            }
        }
    }
}

void            threads_master()
{
    int         i;
    int         ret;
    pthread_t   death_watcher;

    g_orch.tid = malloc(sizeof(pthread_t) * g_orch.np);
    if (g_orch.tid)
    {
        i = -1;
        while (++i < g_orch.np)
        {
            pthread_create(&g_orch.tid[i], NULL, thread, (void *)&g_orch.philos[i]);
            // pthread_detach(g_orch.tid[i]);
        }
        // i = -1;
        // while (++i < g_orch.np)
        //     pthread_join(g_orch.tid[i], NULL);
        pthread_create(&death_watcher, NULL, watcher, NULL);
        pthread_join(death_watcher, NULL);
    }
}
