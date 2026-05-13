/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions_fifo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:17:46 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/13 12:37:01 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static void	take_dongle_fifo(t_coder *coder, t_dongle *dongle)
{
	if (has_stopped(coder) == 1)
		return ;
	pthread_mutex_lock(dongle->m_lock);
	while (dongle->owner != 0 && dongle->owner != coder->id)
	{
		dongle->c_locked = 1;
		pthread_cond_wait(dongle->c_lock, dongle->m_lock);
	}
	dongle->owner = coder->id;
	if (has_stopped(coder) == 1)
	{
		pthread_mutex_unlock(dongle->m_lock);
		return ;
	}
	pthread_mutex_lock(coder->output_log);
	printf("  \e[38;5;116m%10lu %3d has taken a dongle %d\n",
		get_time() - coder->program_start_time, coder->id, dongle->id);
	pthread_mutex_unlock(coder->output_log);
	if (get_time() < dongle->when_available)
		usleep((dongle->when_available - get_time()) * 1000);
	coder->dongle_count += 1;
	pthread_mutex_unlock(dongle->m_lock);
}

static void request_dongles_fifo(t_coder *coder)
{
	pthread_mutex_lock(coder->coder_lock);
	pthread_mutex_lock(coder->left->m_lock);
	pthread_mutex_lock(coder->right->m_lock);
	if (coder->left->owner == 0 && coder->right->owner == 0)
	{
		coder->left->owner = coder->id;
		coder->right->owner = coder->id;
	}
	pthread_mutex_unlock(coder->coder_lock);
	pthread_mutex_unlock(coder->left->m_lock);
	pthread_mutex_unlock(coder->right->m_lock);
}

void	get_dongles_fifo(t_coder *coder)
{
	request_dongles_fifo(coder);
	if (coder->left->id < coder->right->id)
	{
		take_dongle_fifo(coder, coder->left);
		take_dongle_fifo(coder, coder->right);
		return ;
	}
	take_dongle_fifo(coder, coder->right);
	take_dongle_fifo(coder, coder->left);
}
