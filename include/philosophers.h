/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:53:25 by aihya             #+#    #+#             */
/*   Updated: 2021/10/09 17:48:57 by aihya            ###   ########.fr       */
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

typedef enum {FALSE, TRUE} e_bool;
typedef enum {NONE, EAT, SLEEP, THINK} e_action;
typedef enum {L, R} e_side;

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

// [0, 0, 0, 0, 0]
// [M, M, M, M, M]

typedef struct s_philo
{
    int             id;
    int             tid;
    int             status;
    unsigned long   td;
}               t_philo;

typedef struct s_orch
{
    int                 np;
    unsigned int        td;
    unsigned int        te;
    unsigned int        ts;
    unsigned int        nts;
    pthread_mutex_t*    forks;
    pthread_mutex_t     output;
    pthread_t*          tid;
    t_philo*            philos;
    t_philo*            first_blood;
    unsigned long       timeref;
}               t_orch;

pthread_mutex_t g_mutex;
t_orch  g_orch;

void            threads_master();
unsigned long   getcurrenttime();
unsigned long   timestamp();

#endif
