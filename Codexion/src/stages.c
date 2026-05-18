/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:26:09 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/18 09:47:19 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

void	compilation_stage(t_coder *coder)
{
	size_t	time;

	pthread_mutex_lock(coder->coder_lock);
	coder->loop_start_time = get_time();
	pthread_mutex_unlock(coder->coder_lock);
	if (has_stopped(coder) == 1)
		return ;
	log_msg(coder, "is compiling", "\e[38;5;4m");
	pthread_mutex_lock(coder->coder_lock);
	time = get_time() - coder->loop_start_time + coder->time_to_burnout;
	if (time <= (size_t)coder->time_to_compile)
	{
		pthread_mutex_unlock(coder->coder_lock);
		usleep((time + 1) * 1000);
		return ;
	}
	pthread_mutex_unlock(coder->coder_lock);
	usleep(coder->time_to_compile * 1000);
	pthread_mutex_lock(coder->coder_lock);
	coder->compilations += 1;
	pthread_mutex_unlock(coder->coder_lock);
}

void	debugging_stage(t_coder *coder)
{
	if (has_stopped(coder) == 1)
		return ;
	log_msg(coder, "is debugging", "\e[38;5;10m");
	if (get_time() - coder->loop_start_time + coder->time_to_burnout
		< (size_t)coder->time_to_debug)
		usleep(coder->time_to_burnout * 1000);
	else
		usleep(coder->time_to_debug * 1000);
}

void	refactoring_stage(t_coder *coder)
{
	if (has_stopped(coder) == 1)
		return ;
	log_msg(coder, "is refactoring", "\e[38;5;185m");
	if (get_time() - coder->loop_start_time + coder->time_to_burnout
		< (size_t)coder->time_to_refactor)
		usleep((get_time() - coder->loop_start_time
				+ coder->time_to_burnout) * 1000);
	else
		usleep((coder->time_to_refactor) * 1000);
}
