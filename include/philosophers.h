/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:53:25 by aihya             #+#    #+#             */
/*   Updated: 2021/10/16 11:11:12 by aihya            ###   ########.fr       */
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

typedef enum {FALSE, TRUE}				e_bool;
typedef enum {NONE, EAT, SLEEP, THINK}	e_action;
typedef enum {L, R}						e_side;

typedef struct s_queue
{
	int	f;
	int	b;
    int *arr;
}		t_queue;

typedef struct s_philo
{
	int				id;
	int				tid;
	int				status;
	int				can_eat;
	unsigned long	te;
}					t_philo;

typedef struct s_orch
{
	int					np;
	unsigned int		td;
	unsigned int		te;
	unsigned int		ts;
	unsigned int		nts;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output;
	pthread_t			*tid;
	t_philo				*philos;
	t_philo				*first_blood;
	unsigned long		timeref;
    t_queue				*queue;
}						t_orch;

int		dead;
int		first_enter;

pthread_mutex_t	g_mutex;
t_orch			g_orch;

void			threads_master(void);
unsigned long	getcurrenttime(void);
unsigned long	timestamp(unsigned long ref);
void			lock(int side, t_philo* p);
void			unlock(int side, t_philo* p);
void			eat(t_philo* p);
void			think(t_philo* p);
void			_sleep(t_philo* p);
void			feedback(int id, char* msg);
#endif
