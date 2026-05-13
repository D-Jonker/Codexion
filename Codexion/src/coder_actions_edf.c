/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions_edf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:20:49 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/13 13:07:29 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

static void	take_dongle_edf(t_coder *coder, t_dongle *dongle)
{
	if (has_stopped(coder) == 1)
		return ;
	printf("\e[38;5;245m%lu %d has %d as owner as seen by %d\n", get_time() - coder->program_start_time, dongle->id, dongle->owner, coder->id); //
	pthread_mutex_lock(dongle->m_lock);
	while (dongle->owner != coder->id)
	{
		printf("\e[38;5;250m   coder %d waits on %d\n", coder->id, dongle->id); //
		dongle->c_locked = 1;
		pthread_cond_wait(dongle->c_lock, dongle->m_lock);
	}
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

static void	request_dongle_edf(t_coder *coder, t_dongle *dongle)
{
	t_coder	*coder_1;
	t_coder	*coder_2;

	if (has_stopped(coder) == 1)
		return ;
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

	if (has_stopped(coder) == 1)
		return ;
	pthread_mutex_lock(dongle->m_lock);
	coder_1 = dongle->queue[0];
	coder_2 = dongle->queue[1];
	if (1)
	{
		printf("%d %d %d\n", dongle->id, dongle->owner, dongle->next);
		pthread_mutex_lock(coder_1->coder_lock);
		pthread_mutex_lock(coder_2->coder_lock);
		if (coder_1->loop_start_time == coder_2->loop_start_time)
		{
			if (coder_1->id < coder_2->id)
			{
				dongle->owner = coder_1->id;
				dongle->next = coder_2->id;
			}
			else
			{
				dongle->owner = coder_2->id;
				dongle->next = coder_1->id;
			}
		}
		else if (coder_1->loop_start_time < coder_2->loop_start_time)
		{
			dongle->owner = coder_1->id;
			dongle->next = coder_2->id;
		}
		else
		{
			dongle->owner = coder_2->id;
			dongle->next = coder_1->id;
		}
		pthread_mutex_unlock(coder_1->coder_lock);
		pthread_mutex_unlock(coder_2->coder_lock);
	}
	pthread_mutex_unlock(dongle->m_lock);
	printf("%lu %d has exited\n", get_time() - coder->program_start_time, coder->id);
}

void	get_dongles_edf(t_coder *coder)
{
	if (coder->left->id < coder->right->id)
	{
		request_dongle_edf(coder, coder->right);
		request_dongle_edf(coder, coder->left);
		if (should_release(coder) == 1)
			return ;
		take_dongle_edf(coder, coder->right);
		if (should_release(coder) == 1)
			return ;
		take_dongle_edf(coder, coder->left);
		return ;
	}
	request_dongle_edf(coder, coder->left);
	request_dongle_edf(coder, coder->right);
	if (should_release(coder) == 1)
		return ;
	take_dongle_edf(coder, coder->left);
	if (should_release(coder) == 1)
		return ;
	take_dongle_edf(coder, coder->right);
}
