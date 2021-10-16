/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:16:04 by aihya             #+#    #+#             */
/*   Updated: 2021/10/16 11:14:31 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    pick_forks(t_philo* p)
{
	if (p->id % 2)
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

void    drop_forks(t_philo* p)
{
	if (p->id % 2)
	{
		unlock(L, p);
		unlock(R, p);
	}
	else
	{
		unlock(L, p);
		unlock(R, p);
	}
}

void    eat(t_philo* p)
{
	pick_forks(p);
	p->te = getcurrenttime();
	feedback(p->id, "\x1b[32meating\x1b[0m");
	usleep(g_orch.te);
	drop_forks(p);
}

void     _sleep(t_philo* p)
{
	feedback(p->id, "\x1b[33msleeping\x1b[0m");
	usleep(g_orch.ts);
}

void     think(t_philo* p)
{
	feedback(p->id, "\x1b[34mthinking\x1b[0m");
}
