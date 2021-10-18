/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:26:28 by aihya             #+#    #+#             */
/*   Updated: 2021/10/18 14:17:33 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	feedback(int id, char* msg)
{
	unsigned long   ts;

	ts = timestamp(g_orch.timeref);
	pthread_mutex_lock(&g_orch.output);
	printf("%ldms\t%d\t%s\n", ts, id + 1, msg);
	pthread_mutex_unlock(&g_orch.output);
}

void*	thread(void* arg)
{
	t_philo			*p;
	unsigned long	t;

	p = (t_philo*)arg;
	if (p)
	{
		while (timestamp(p->te) < g_orch.td)
		{
			eat(p);
			_sleep(p);
			think(p);
		}
		dead = p->id;
	}
	return (NULL);
}

void	threads_master()
{
	int		i;
	t_philo	*p;
	int		count;

	count = 0;
	first_enter = 0;
	g_orch.tid = malloc(sizeof(pthread_t) * g_orch.np);
	if (g_orch.tid)
	{
		i = -1;
		while (++i < g_orch.np)
		{
			p = &g_orch.philos[i];
			if (!pthread_create(&g_orch.tid[i], NULL, thread, (void *)p))
				count++;
			else
				break;
		}
		if (count == g_orch.np)
		{
			printf("Error: %d/%d threads were created\n", count, g_orch.np);
			return ;
		}
		while (!dead)
			;
    	feedback(dead, "\x1b[31mDEAD\x1b[0m");
	}
}
