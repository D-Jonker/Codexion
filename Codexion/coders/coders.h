/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:05:10 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 10:06:14 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H
# include "source.h"

typedef struct s_coder
{
	int			coder_id;
	int			dongle_count;
	pthread_t	thread;
	long		start_time;
	long		when_burnout; //time_to_burnout + start_time
	long		start_compiling; // Time started compiling
	long		start_debug; // Time start debug
	long		start_refactor; // Time starts refactoring
}	t_coder;

#endif
