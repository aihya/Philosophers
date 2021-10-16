/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:20:28 by aihya             #+#    #+#             */
/*   Updated: 2021/10/16 18:22:01 by aihya            ###   ########.fr       */
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
		queue->b = g_orch->np - 1;
		queue->queue = (int *)malloc(sizeof(int) * g_orch.np);
	}
	return (queue);
}

int		push_queue()
{
	
	return (0);
}

int		pop_queue()
{
	return (0);
}
