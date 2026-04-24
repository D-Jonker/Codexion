/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monotoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:04:24 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 10:08:31 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONOTORING_H
# define MONOTORING_H
# include "source.h"

typedef struct s_monotoring
{
	int				nbr_of_coders;

	pthread_mutex_t	*monotoring_lock;
	int				nbr_of_compilations;
	int				needed_compilations;

	long			current_time;
	
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			time_to_cooldown;

	char			*scheduler;
	
	t_dongle		**dongles;
	int				nbr_dongles_created;

	t_coder			**coders;
	int				nbr_coders_created;
	int				nbr_of_coders_launched;

	pthread_mutex_t	*output_log;
}	t_monotoring;

#endif
