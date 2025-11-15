/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:46:45 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/13 09:29:56 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitoring(void *data)
{
	t_program	*prog;

	prog = (t_program *)data;
	while (true)
	{
		if (should_finish(prog, 0, 0))
			break ;
	}
	return (NULL);
}

int	should_finish(t_program *prog, int i, int full)
{
	while (i < prog->amount)
	{
		pthread_mutex_lock(&prog->eat_lock);
		if (my_gettime() - prog->ph[i].last_meal > prog->time_to_die)
		{
			handle_death(prog, i);
			pthread_mutex_unlock(&prog->eat_lock);
			return (1);
		}
		if (prog->ph[i].meals_count == prog->ph[i].meals_total)
			full++;
		pthread_mutex_unlock(&prog->eat_lock);
		i++;
	}
	if (full == prog->amount)
	{
		pthread_mutex_lock(&prog->stop);
		prog->force_stop = 1;
		pthread_mutex_unlock(&prog->stop);
		return (1);
	}
	return (0);
}

void	handle_death(t_program *prog, int i)
{
	pthread_mutex_lock(&prog->print_lock);
	printer(my_gettime() - prog->start_simulation,
		prog->ph[i].philo_id, "died");
	pthread_mutex_lock(&prog->stop);
	prog->force_stop = 1;
	pthread_mutex_unlock(&prog->stop);
	usleep(200);
	pthread_mutex_unlock(&prog->print_lock);
}

int	check_finished(t_program *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->force_stop)
	{
		pthread_mutex_unlock(&data->stop);
		return (1);
	}
	pthread_mutex_unlock(&data->stop);
	return (0);
}
