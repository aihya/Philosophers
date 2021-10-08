/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:26:28 by aihya             #+#    #+#             */
/*   Updated: 2021/10/08 20:35:45 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void     feedback(int id, char* msg)
{
    pthread_mutex_lock(&g_orch.output_mutex);
    printf("%ldms\t%d %s\n", timestamp(), id, msg);
    pthread_mutex_unlock(&g_orch.output_mutex);
}

int     pick_fork(int side, t_philo* p)
{
    int picked;
    int idx;

    idx = p->id;
    if (side == RIGHT)
        idx = (p->id + 1) % g_orch.np;
    picked = -1;
    pthread_mutex_lock(&g_orch.mutex[idx]);
    if (g_orch.forks[idx] == NOT_TAKEN)
    {
        g_orch.forks[idx] = TAKEN;
        feedback(p->id, "has taken a fork");
        picked = idx;
    }
    pthread_mutex_unlock(&g_orch.mutex[idx]);
    return (picked);
}

void    drop_fork(int side, t_philo* p)
{
    int idx;

    idx = p->id;
    if (side == RIGHT)
        idx = (p->id + 1) % g_orch.np;
    pthread_mutex_lock(&g_orch.mutex[idx]);
    g_orch.forks[idx] = NOT_TAKEN;
    // feedback(p->id, "has dropped a fork");
    pthread_mutex_unlock(&g_orch.mutex[idx]);
}

int     eating(t_philo* p)
{
    // int state;

    // state = FALSE;
    // if (pick_fork(LEFT, p))
    // {
        // if (pick_fork(RIGHT, p))
        // {
            feedback(p->id, "is eating");
            usleep(g_orch.te);
            drop_fork(RIGHT, p);
            p->td += g_orch.td;
            // state = TRUE;
        // }
            // drop_fork(LEFT, p);
    // }
    return (0);
}

void     sleeping(t_philo* p)
{
    feedback(p->id, "is sleeping");
    usleep(g_orch.ts);
}

void     thinking(t_philo* p)
{
    feedback(p->id, "is thinking");
}

void*    philosopher(void* arg)
{
    t_philo *p;
    int     l_fork;
    int     r_fork;

    p = (t_philo*)arg;
    if (p)
    {
        while (getcurrenttime() < p->td)
        {
            p->status = -1;
            
            l_fork = pick_fork(LEFT, p);
            if (l_fork >= 0)
            {
                r_fork = pick_fork(RIGHT, p);
                if (r_fork >= 0)
                    p->status = EAT;
                else
                    drop_fork(LEFT, p);
            }

            if (p->status == EAT)
                eating(p);
            else if (p->status == SLEEP)
                sleeping(p);
            else if (p->status == THINK)
                thinking(p);
            // if (eating(p))
            // {
                // sleeping(p);
                // thinking(p);
            // }
            
        }
        feedback(p->id, "DIED");
        exit(-1);
    }
    return (NULL);
}

void            threads_master()
{
    int i;
    int ret;

    g_orch.tid = malloc(sizeof(pthread_t) * g_orch.np);
    if (g_orch.tid)
    {
        g_orch.timeref = getcurrenttime();
        i = -1;
        while (++i < g_orch.np)
            pthread_create(&g_orch.tid[i], NULL, philosopher, (void *)&g_orch.philos[i]);
        i = -1;
        while (++i < g_orch.np)
            pthread_join(g_orch.tid[i], NULL);
    }
}
