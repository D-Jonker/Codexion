/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:05:10 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/07 12:15:35 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H
# include "source.h"

typedef struct s_coder
{
	pthread_mutex_t	*coder_lock;
	pthread_mutex_t	*output_log;
	pthread_mutex_t	*monotoring_lock;
	int				*stop;
	pthread_t		*thread;
	t_dongle		*left;
	t_dongle		*right;
	int				id;
	int				dongle_count;
	int				scheduler;
	size_t			program_start_time;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	size_t			loop_start_time;
	int				compilations;
	int				min_compilations;
}	t_coder;

#endif
