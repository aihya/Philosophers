/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:53:25 by aihya             #+#    #+#             */
/*   Updated: 2021/10/07 20:18:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>

typedef enum {NOT_TAKEN, TAKEN} e_available;
typedef enum {FALSE, TRUE} e_bool;
typedef enum {DEAD, EATING, SLEEPING, THINKING} e_action;

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

// [0, 0, 0, 0, 0]
// [M, M, M, M, M]

typedef struct s_philo
{
    int id;
    int tid;
    int can_eat;
    unsigned long   td;
}               t_philo;

typedef struct s_orch
{
    int                 np;
    unsigned int        td;
    unsigned int        te;
    unsigned int        ts;
    unsigned int        nts;
    unsigned int*       forks;
    pthread_mutex_t*    mutex;
    pthread_mutex_t     output_mutex;
    pthread_t*          tid;
    t_philo*            philos;
    t_philo*            first_blood;
    struct timeval      ep;
}               t_orch;

t_orch  g_orch;

void    threads_master();

#endif
