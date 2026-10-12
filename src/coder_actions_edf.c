/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions_edf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:20:49 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/22 10:18:40 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static void	take_dongle_edf(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	if (dongle->owner != coder->id)
	{
		dongle->c_locked = 1;
		pthread_cond_wait(dongle->c_lock, dongle->m_lock);
	}
	dongle->in_use = 1;
	coder->dongle_count += 1;
	if (has_stopped(coder) == 0 && get_time() < dongle->when_available
		&& dongle->when_available > get_loop_start(coder)
		+ coder->time_to_burnout)
		usleep((dongle->when_available - get_time()) * 1000);
	else if (has_stopped(coder) == 0
		&& get_time() < get_loop_start(coder) + coder->time_to_burnout)
		usleep((get_loop_start(coder) + coder->time_to_burnout) - get_time());
	log_msg(coder, "has taken a dongle", "\e[38;5;116m");
	pthread_mutex_unlock(dongle->m_lock);
}

static void	make_queue(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	if (dongle->queue[0] == NULL)
	{
		dongle->queue[0] = coder;
		while (dongle->queue[1] == NULL)
		{
			if (has_stopped(coder) == 1)
			{
				pthread_mutex_unlock(dongle->m_lock);
				return ;
			}
			pthread_cond_wait(dongle->c_lock, dongle->m_lock);
		}
	}
	else if (dongle->queue[1] == NULL)
	{
		dongle->queue[1] = coder;
		pthread_cond_broadcast(dongle->c_lock);
	}
	pthread_mutex_unlock(dongle->m_lock);
}

static void	order_based_on_burnout(t_dongle *dongle)
{
	t_coder	*tmp;
	long	difference;

	difference = (long)(get_loop_start((t_coder *)dongle->queue[0])
			- get_loop_start((t_coder *)dongle->queue[1]));
	if (difference == 0 && ((t_coder *)dongle->queue[0])->id % 2 == 0)
	{
		tmp = (t_coder *)dongle->queue[0];
		dongle->queue[0] = dongle->queue[1];
		dongle->queue[1] = tmp;
	}
	else if (difference > 0)
	{
		tmp = (t_coder *)dongle->queue[0];
		dongle->queue[0] = dongle->queue[1];
		dongle->queue[1] = tmp;
	}
}

static void	should_order(t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	if (!dongle->queue[0] || !dongle->queue[1])
	{
		pthread_mutex_unlock(dongle->m_lock);
		return ;
	}
	order_based_on_burnout(dongle);
	if (dongle->owner == 0 && dongle->next == 0)
	{
		dongle->owner = ((t_coder *)dongle->queue[0])->id;
		dongle->next = ((t_coder *)dongle->queue[1])->id;
	}
	else if (dongle->owner != 0 && dongle->next == 0
		&& dongle->owner != ((t_coder *)dongle->queue[0])->id)
		dongle->next = ((t_coder *)dongle->queue[0])->id;
	else if (dongle->owner != 0 && dongle->next == 0
		&& dongle->owner != ((t_coder *)dongle->queue[1])->id)
		dongle->next = ((t_coder *)dongle->queue[1])->id;
	pthread_mutex_unlock(dongle->m_lock);
}

void	get_dongles_edf(t_coder *coder)
{
	if (coder->left->id < coder->right->id)
	{
		make_queue(coder, coder->right);
		should_order(coder->right);
		make_queue(coder, coder->left);
		should_order(coder->left);
		to_get_two(coder->right, coder->left);
		take_dongle_edf(coder, coder->right);
		take_dongle_edf(coder, coder->left);
	}
	else
	{
		make_queue(coder, coder->left);
		should_order(coder->left);
		make_queue(coder, coder->right);
		should_order(coder->right);
		to_get_two(coder->left, coder->right);
		take_dongle_edf(coder, coder->left);
		take_dongle_edf(coder, coder->right);
	}
}
