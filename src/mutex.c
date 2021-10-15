/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:17:49 by aihya             #+#    #+#             */
/*   Updated: 2021/10/15 11:18:13 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    lock(int side, t_philo* p)
{
	pthread_mutex_lock(&g_orch.forks[(p->id + side) % g_orch.np]);
}

void    unlock(int side, t_philo* p)
{
	pthread_mutex_unlock(&g_orch.forks[(p->id + side) % g_orch.np]);
}
