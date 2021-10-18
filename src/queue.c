/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:20:28 by aihya             #+#    #+#             */
/*   Updated: 2021/10/18 13:43:55 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_queue()
{
	t_queue *queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (queue)
	{
		queue->f = 0;
		queue->b = g_orch.np - 1;
		queue->arr = (int *)malloc(sizeof(int) * g_orch.np);
	}
}

void	push_queue(int id)
{
	g_orch.queue->f = (g_orch.queue->f + 1) % g_orch.np;
	g_orch.queue->arr[g_orch.queue->f] = id;
}

void	pop_queue()
{
	
}
