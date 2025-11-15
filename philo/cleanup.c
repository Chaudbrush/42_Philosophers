/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:49:00 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/10 11:11:18 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_program *data)
{
	int	i;

	i = -1;
	while (++i < data->amount)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_lock);
	free(data->ph);
	free(data->forks);
}

void	clean_mutex(t_program *data, int i, int flag)
{
	while (--i >= 0)
		pthread_mutex_destroy(&data->forks[i]);
	if (flag == 1)
		pthread_mutex_destroy(&data->eat_lock);
	else if (flag == 2)
	{
		pthread_mutex_destroy(&data->eat_lock);
		pthread_mutex_destroy(&data->print_lock);
	}
	free(data->ph);
	free(data->forks);
}
