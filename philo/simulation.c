/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:40:50 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 21:10:26 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal = my_gettime();
	pthread_mutex_unlock(&philo->data->eat_lock);
	writer(philo->data, "has taken a fork", philo->philo_id);
	while (check_finished(philo->data) == 0)
		usleep(250);
	return (NULL);
}

void	*dinner(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal = philo->data->start_simulation;
	pthread_mutex_unlock(&philo->data->eat_lock);
	if (philo->philo_id % 2 == 0)
		my_sleep(philo->data, 200);
	while (check_finished(philo->data) == 0)
	{
		ft_eat(data);
		ft_sleep(data);
		ft_think(data);
	}
	return (NULL);
}

void	ft_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->right_fork);
	writer(philo->data, "has taken a fork", philo->philo_id);
	pthread_mutex_lock(philo->left_fork);
	writer(philo->data, "has taken a fork", philo->philo_id);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->last_meal = my_gettime();
	pthread_mutex_unlock(&philo->data->eat_lock);
	writer(philo->data, "is eating", philo->philo_id);
	my_sleep(philo->data, philo->time_to_eat);
	pthread_mutex_lock(&philo->data->eat_lock);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->data->eat_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philos *philo)
{
	writer(philo->data, "is sleeping", philo->philo_id);
	my_sleep(philo->data, philo->time_to_sleep);
}

void	ft_think(t_philos *philo)
{
	int	think_time;

	if ((philo->data->amount % 2) == 0)
		return ;
	think_time = (philo->time_to_eat * 2) - philo->time_to_sleep;
	if (think_time < 0)
		think_time = 1;
	writer(philo->data, "is thinking", philo->philo_id);
	my_sleep(philo->data, think_time);
}

// Not in use
// void	wait_all_philos(t_philos *philo)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->data->stop);
// 		if (philo->data->wait_start)
// 		{
// 			pthread_mutex_unlock(&philo->data->stop);
// 			return ;
// 		}
// 		pthread_mutex_unlock(&philo->data->stop);
// 	}
// }