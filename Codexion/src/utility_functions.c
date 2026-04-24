/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dijonker <dijonker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:09:26 by dijonker          #+#    #+#             */
/*   Updated: 2026/04/24 15:22:28 by dijonker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/source.h"

void	free_for_all(t_monotoring *data)
{
	int count;

	count = 0;
	while (count < data->nbr_coders_created)
	{
		free(*(data->coders + count));
		count++;
	}
	if (data->coders)
		free(data->coders);
	count = 0;
	while (count < data->nbr_dongles_created)
	{
		free(*(data->dongles + count));
		count++;
	}
	if (data->dongles)
		free(data->dongles);
}

char	*ft_strdup(const char *s)
{
	char			*dest;
	unsigned int	i;
	int				length;

	length = 0;
	while (s[length] != '\0')
		length++;
	dest = malloc((length + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
