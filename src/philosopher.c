/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:26:28 by aihya             #+#    #+#             */
/*   Updated: 2021/10/07 20:49:10 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long    timestamp()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - 
            (g_orch.ep.tv_sec * 1000 + g_orch.ep.tv_usec / 1000));
}

void     feedback(int id, char* msg)
{
    pthread_mutex_lock(&g_orch.output_mutex);
    printf("%ld %d %s\n", timestamp(), id, msg);
    // printf("%d %s\n", id, msg);
    pthread_mutex_unlock(&g_orch.output_mutex);
}

void     eating(t_philo* p)
{
    // if (g_orch.forks[p->id] == NOT_TAKEN)
    // {
    // pthread_mutex_lock(&g_orch.mutex[p->id]);
    // // feedback(p->id, "locked left to use");
    //     g_orch.forks[p->id] = TAKEN;
    //     feedback(p->id, "has taken left fork");
    //     if (g_orch.forks[(p->id + 1) % g_orch.np] == NOT_TAKEN)
    //     {
    //     pthread_mutex_lock(&g_orch.mutex[(p->id + 1) % g_orch.np]);
    //     // feedback(p->id, "locked right");
    //         g_orch.forks[(p->id + 1) % g_orch.np] = TAKEN;
    //         feedback(p->id, "has taken right fork");
    //         feedback(p->id, "eating");
    //         usleep(g_orch.te * 1000);
    //         pthread_mutex_unlock(&g_orch.mutex[(p->id + 1) % g_orch.np]);
    //         // feedback(p->id, "unlocked right");
    //         pthread_mutex_unlock(&g_orch.mutex[p->id]);
    //         // feedback(p->id, "unlocked left");
    //     }
    //     else
    //     {
    //         // pthread_mutex_unlock(&g_orch.mutex[(p->id + 1) % g_orch.np]);
    //         // feedback(p->id, "unlocked right");
    //         pthread_mutex_lock(&g_orch.mutex[p->id]);
    //         // feedback(p->id, "locked left to release");
    //         g_orch.forks[p->id] = NOT_TAKEN;
    //         pthread_mutex_unlock(&g_orch.mutex[p->id]);
    //         // feedback(p->id, "unlocked left");
    //     }
    //     pthread_mutex_unlock(&g_orch.mutex[p->id]);
    //         // feedback(p->id, "unlocked left");
    // }
    
    // pthread_mutex_lock(&g_orch.mutex[p->id]);
    // pthread_mutex_lock(&g_orch.mutex[(p->id + 1) % g_orch.np]);
    // if (g_orch.forks[p->id] == NOT_TAKEN && g_orch.forks[(p->id + 1) % g_orch.np] == NOT_TAKEN)
    // {
    //     g_orch.forks[p->id] = TAKEN;
    //     g_orch.forks[(p->id + 1) % g_orch.np] = TAKEN;
    //     feedback(p->id, "eating");
    //     usleep(g_orch.te * 1000);
    //     g_orch.forks[p->id] = NOT_TAKEN;
    //     g_orch.forks[(p->id + 1) % g_orch.np] = NOT_TAKEN;
    // }
    // pthread_mutex_unlock(&g_orch.mutex[(p->id + 1) % g_orch.np]);
    // pthread_mutex_unlock(&g_orch.mutex[p->id]);

    pthread_mutex_lock(&master->forks[get_smaller_fork(p->id)]);
    print_action_message(philo->id, "took a fork");
    if (!pthread_mutex_lock(&master->forks[get_bigger_fork(philo->id)]))
    {
        print_action_message(philo->id, "took a fork");
        print_action_message(philo->id, "is eating");
        usleep(philo->game_rules.time_to_eat_us);
        philo->dying_time += philo->game_rules.time_to_die;
        philo->meal_number++;
        if (philo->meal_number == master->game_rules.number_of_times_eat)
            master->full_counter++;
        if (master->full_counter == master->game_rules.philo_number)
            master->first_blood = 1;
        pthread_mutex_unlock(&master->forks[get_bigger_fork(philo->id)]);
    }
    else
        while(1)
            if (get_current_time() >= philo->dying_time)
                print_action_message(philo->id, "died");
    pthread_mutex_unlock(&master->forks[get_smaller_fork(philo->id)]);
}

void     sleeping(t_philo* p)
{
    feedback(p->id, "sleeping");
    usleep(g_orch.ts * 1000);
}

void     thinking(t_philo* p)
{
    feedback(p->id, "thinking");
}

void*    philosopher(void* arg)
{
    t_philo         *p;

    p = (t_philo*)arg;
    if (p)
    {
        while (1)
        {
            eating(p);
            sleeping(p);
            thinking(p);
        }
        feedback(p->id, "died");
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
        gettimeofday(&g_orch.ep, NULL);
        i = -1;
        while (++i < g_orch.np)
            pthread_create(&g_orch.tid[i], NULL, philosopher, (void *)&g_orch.philos[i]);
        i = -1;
        while (++i < g_orch.np)
            pthread_join(g_orch.tid[i], NULL);
    }
}
