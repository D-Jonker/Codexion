/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:06:43 by dijonker          #+#    #+#             */
/*   Updated: 2026/05/12 11:21:01 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOURCE_H
# define SOURCE_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include "dongles.h"
# include "coders.h"
# include "system.h"

int				codexion(t_system *system);

pthread_mutex_t	*mutex_init(void);

size_t			get_time(void);

int				monotoring_init(t_system *system);
void			*monotoring(void *system);

int				create_dongles(t_system *system);
void			get_dongles(t_coder *coder);
void			get_dongles_edf(t_coder *coder);
void			get_dongles_fifo(t_coder *coder);
void			release(t_coder *coder, t_dongle *dongle);

/**
 * @brief Allocates and innitialises a array of coders
 * 
 * @param system (t_system) is a struct with the base information of the program
 * 
 * @return t_coder** an array of t_coder with memory allocated to start a
 * 		   thread lather
 */
int				create_coders(t_system *system);
int				launch_coders(t_system *system);
int				join_coders(t_system *system);

void			compilation_stage(t_coder *coder);
void			debugging_stage(t_coder *coder);
void			refactoring_stage(t_coder *coder);
void			burnout_stage(t_coder *coder);

int				free_for_all(t_system *system, int mode);

int				has_stopped(t_coder *coder);
int				should_release(t_coder *coder);

#endif