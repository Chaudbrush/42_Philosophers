/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:37:44 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/13 09:22:53 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*fork_monitor(void *data)
{
	t_program	*prog;

	prog = (t_program *)data;
	while (1)
	{
		sem_wait(prog->eat_lock);
		if (my_gettime() - prog->philo.last_meal > prog->time_to_die)
		{
			monitor_change(data, 0);
			break ;
		}
		if (prog->philo.meals_count == prog->philo.meals_total)
		{
			monitor_change(data, 1);
			break ;
		}
		sem_post(prog->eat_lock);
	}
	sem_post(prog->eat_lock);
	return (NULL);
}

int	check_finished(t_program *data)
{
	sem_wait(data->stop);
	if (data->philo.stop)
	{
		sem_post(data->stop);
		return (1);
	}
	sem_post(data->stop);
	return (0);
}

void	monitor_change(t_program *data, int flag)
{
	sem_wait(data->stop);
	if (flag)
		data->philo.died = 1;
	data->philo.stop = 1;
	sem_post(data->stop);
}
