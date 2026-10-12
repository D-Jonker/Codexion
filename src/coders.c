/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:18:06 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/22 10:18:28 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

void	release(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	dongle->owner = dongle->next;
	dongle->next = 0;
	coder->dongle_count -= 1;
	dongle->when_available = get_time() + *dongle->cooldown_time;
	if (dongle->in_use == 1)
		dongle->in_use = 0;
	if (dongle->c_locked == 1)
		pthread_cond_broadcast(dongle->c_lock);
	dongle->c_locked = 0;
	pthread_mutex_unlock(dongle->m_lock);
}

static void	get_dongles(t_coder *coder)
{
	if (coder->scheduler == 1)
	{
		get_dongles_edf(coder);
		return ;
	}
	get_dongles_fifo(coder);
}

static void	sleep_if_uneven(t_coder *coder)
{
	if (coder->id % 2 == 0)
		return ;
	if (*coder->left->cooldown_time < coder->time_to_burnout)
		usleep(*coder->left->cooldown_time * 500);
	else
		usleep(coder->time_to_burnout * 500);
}

void	*coders_thread(void *coder_void)
{
	t_coder	*coder;

	coder = (t_coder *)coder_void;
	if (coder->left->id == coder->right->id)
		one_coder(coder);
	if (has_stopped(coder) == 1)
		return (NULL);
	sleep_if_uneven(coder);
	pthread_mutex_lock(coder->coder_lock);
	coder->loop_start_time = get_time();
	pthread_mutex_unlock(coder->coder_lock);
	while (1)
	{
		get_dongles(coder);
		compilation_stage(coder);
		release(coder, coder->left);
		release(coder, coder->right);
		debugging_stage(coder);
		refactoring_stage(coder);
		if (has_stopped(coder) == 1)
			break ;
	}
	return (NULL);
}
