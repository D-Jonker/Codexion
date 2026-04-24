/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:26:09 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 10:43:30 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

void	*compilation_stage(int current_time, int coder_id, int sleep_time)
{
	printf("%d %d is compiling", current_time, coder_id);
	usleep(sleep_time);
	return (NULL);
}

void	*debugging_stage(int current_time, int coder_id, int sleep_time)
{
	printf("%d %d is debugging", current_time, coder_id);
	usleep(sleep_time);
	return (NULL);
}

void	*refactoring_stage(int current_time, int coder_id, int sleep_time)
{
	printf("%d %d is refactoring", current_time, coder_id);
	usleep(sleep_time);
	return (NULL);
}

