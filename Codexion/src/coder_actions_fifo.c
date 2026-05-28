/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions_fifo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:17:46 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/21 15:36:48 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static void	take_dongle_fifo(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	while (dongle->owner != coder->id && has_stopped(coder) == 0)
	{
		dongle->c_locked = 1;
		pthread_cond_wait(dongle->c_lock, dongle->m_lock);
	}
	dongle->in_use = 1;
	if (has_stopped(coder) == 0 && get_time() < dongle->when_available)
		usleep((dongle->when_available - get_time()) * 1000);
	log_msg(coder, "has taken a dongle", "\e[38;5;116m");
	coder->dongle_count += 1;
	pthread_mutex_unlock(dongle->m_lock);
}

static void	request_dongles_fifo(int coder_id,
	t_dongle *first, t_dongle *second)
{
	pthread_mutex_lock(first->m_lock);
	pthread_mutex_lock(second->m_lock);
	if (first->owner == 0 && first->next != coder_id)
		first->owner = coder_id;
	else if (first->owner != 0 && first->next == 0
		&& first->owner != coder_id)
		first->next = coder_id;
	if (second->owner == 0 && second->next != coder_id)
		second->owner = coder_id;
	else if (second->owner != 0 && second->next == 0
		&& second->owner != coder_id)
		second->next = coder_id;
	pthread_mutex_unlock(second->m_lock);
	pthread_mutex_unlock(first->m_lock);
}

void	to_get_two(t_dongle *first, t_dongle *second)
{
	int	tmp;

	pthread_mutex_lock(first->m_lock);
	pthread_mutex_lock(second->m_lock);
	if (first->owner != second->owner)
	{
		if (first->owner == second->next && second->in_use == 0)
		{
			tmp = second->owner;
			second->owner = second->next;
			second->next = tmp;
		}
		else if (second->owner == first->next && first->in_use == 0)
		{
			tmp = first->owner;
			first->owner = first->next;
			first->next = tmp;
		}
	}
	pthread_mutex_unlock(second->m_lock);
	pthread_mutex_unlock(first->m_lock);
}

void	get_dongles_fifo(t_coder *coder)
{
	if (coder->left->id < coder->right->id)
	{
		request_dongles_fifo(coder->id, coder->left, coder->right);
		to_get_two(coder->left, coder->right);
		take_dongle_fifo(coder, coder->left);
		take_dongle_fifo(coder, coder->right);
	}
	else if (coder->left->id > coder->right->id)
	{
		request_dongles_fifo(coder->id, coder->right, coder->left);
		to_get_two(coder->right, coder->left);
		take_dongle_fifo(coder, coder->right);
		take_dongle_fifo(coder, coder->left);
	}
}
