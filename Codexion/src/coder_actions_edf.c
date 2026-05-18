/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions_edf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:20:49 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/18 10:03:06 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static void	take_dongle_edf(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	while (dongle->owner != coder->id)
	{
		dongle->c_locked = 1;
		if (dongle->owner == 0 || has_stopped(coder) == 1)
			break ;
		pthread_cond_wait(dongle->c_lock, dongle->m_lock);
	}
	coder->dongle_count += 1;
	if (has_stopped(coder) == 0 && get_time() < dongle->when_available)
		usleep((dongle->when_available - get_time()) * 1000);
	log_msg(coder, "has taken a dongle", "\e[38;5;116m");
	pthread_mutex_unlock(dongle->m_lock);
}

static void	priority_stamp(t_dongle *dongle, int coder1_id, int coder2_id)
{
	if (dongle->owner == 0 && dongle->next == 0)
	{
		dongle->owner = coder1_id;
		dongle->next = coder2_id;
	}
	else if (dongle->owner != coder1_id && dongle->next == 0)
		dongle->next = coder1_id;
}

static void	assign_priority(t_dongle *dongle)
{
	t_coder			*coder_1;
	t_coder			*coder_2;

	pthread_mutex_lock(dongle->m_lock);
	coder_1 = dongle->queue[0];
	coder_2 = dongle->queue[1];
	if (!coder_1 || !coder_2)
	{
		pthread_mutex_unlock(dongle->m_lock);
		return ;
	}
	if (get_loop_start(coder_1) == get_loop_start(coder_2))
	{
		if (coder_1->id % 2)
			priority_stamp(dongle, coder_1->id, coder_2->id);
		else
			priority_stamp(dongle, coder_2->id, coder_1->id);
	}
	else if (get_loop_start(coder_1) < get_loop_start(coder_2))
		priority_stamp(dongle, coder_1->id, coder_2->id);
	else
		priority_stamp(dongle, coder_2->id, coder_1->id);
	pthread_mutex_unlock(dongle->m_lock);
}

static void	make_queue(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(dongle->m_lock);
	if (dongle->queue[0] == NULL)
	{
		dongle->queue[0] = coder;
		while (dongle->queue[1] == NULL && dongle->owner == 0)
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

void	get_dongles_edf(t_coder *coder)
{
	if (coder->left->id < coder->right->id)
	{
		make_queue(coder, coder->right);
		assign_priority(coder->right);
		make_queue(coder, coder->left);
		assign_priority(coder->left);
		take_dongle_edf(coder, coder->right);
		take_dongle_edf(coder, coder->left);
		return ;
	}
	make_queue(coder, coder->left);
	assign_priority(coder->left);
	make_queue(coder, coder->right);
	assign_priority(coder->right);
	take_dongle_edf(coder, coder->left);
	take_dongle_edf(coder, coder->right);
}
