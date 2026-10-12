/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:04:24 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/18 11:34:16 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H
# include "source.h"

typedef struct s_system
{
	int				nbr_coders;
	int				needed_compilations;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				time_to_cooldown;

	char			*schedule;

	pthread_t		*monotoring;
	pthread_mutex_t	*monotoring_lock; //m
	int				stop;

	t_dongle		**dongles;
	int				nbr_dongles_created;

	t_coder			**coders;
	int				nbr_coders_created;
	int				nbr_launched;

	pthread_mutex_t	*output_log;
	size_t			program_start_time;
}					t_system;

#endif
