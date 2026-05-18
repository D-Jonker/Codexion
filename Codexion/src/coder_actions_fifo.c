/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions_fifo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:17:46 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/15 15:16:45 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static void	take_dongle_fifo(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	if (dongle->owner != 0 && dongle->owner != coder->id)
	{
		dongle->c_locked = 1;
		pthread_cond_wait(dongle->c_lock, dongle->m_lock);
	}
	coder->dongle_count += 1;
	if (has_stopped(coder) == 0 && get_time() < dongle->when_available)
		usleep((dongle->when_available - get_time()) * 1000);
	log_msg(coder, "has taken a dongle", "\e[38;5;116m");
	pthread_mutex_unlock(dongle->m_lock);
}

static void	request_dongles_fifo_1(t_coder *coder)
{
	pthread_mutex_lock(coder->right->m_lock);
	pthread_mutex_lock(coder->left->m_lock);
	if (coder->left->owner == 0 && coder->right->owner == 0)
	{
		coder->left->owner = coder->id;
		coder->right->owner = coder->id;
	}
	else if (coder->left->next == 0 && coder->right->next == 0)
	{
		coder->left->next = coder->id;
		coder->right->next = coder->id;
	}
	pthread_mutex_unlock(coder->left->m_lock);
	pthread_mutex_unlock(coder->right->m_lock);
}

static void	request_dongles_fifo_2(t_coder *coder)
{
	pthread_mutex_lock(coder->left->m_lock);
	pthread_mutex_lock(coder->right->m_lock);
	if (coder->left->owner == 0 && coder->right->owner == 0)
	{
		coder->left->owner = coder->id;
		coder->right->owner = coder->id;
	}
	else if (coder->left->next == 0 && coder->right->next == 0)
	{
		coder->left->next = coder->id;
		coder->right->next = coder->id;
	}
	pthread_mutex_unlock(coder->right->m_lock);
	pthread_mutex_unlock(coder->left->m_lock);
}

void	get_dongles_fifo(t_coder *coder)
{
	if (coder->left->id < coder->right->id)
	{
		request_dongles_fifo_1(coder);
		take_dongle_fifo(coder, coder->left);
		take_dongle_fifo(coder, coder->right);
		return ;
	}
	request_dongles_fifo_2(coder);
	take_dongle_fifo(coder, coder->right);
	take_dongle_fifo(coder, coder->left);
}
