/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:39:26 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 14:19:43 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ulong	my_gettime(void)
{
	t_ulong			curr_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (curr_time);
}

void	my_sleep(t_program *data, t_ulong target_time)
{
	t_ulong	initial_time;

	initial_time = my_gettime();
	while (my_gettime() - initial_time < target_time)
	{
		if (check_finished(data))
			break ;
		usleep(100);
	}
}

void	writer(t_program *data, char *str, int i)
{
	t_ulong	timestamp;

	pthread_mutex_lock(&data->print_lock);
	timestamp = my_gettime() - data->start_simulation;
	if (check_finished(data))
	{
		pthread_mutex_unlock(&data->print_lock);
		return ;
	}
	printer(timestamp, i, str);
	pthread_mutex_unlock(&data->print_lock);
}

void	printer(t_ulong time, int id, char *str)
{
	int		i;
	int		j;
	char	buffer[256];

	i = 0;
	j = 0;
	num_to_buffer(&buffer[i], time, &i);
	buffer[i++] = '\t';
	num_to_buffer(&buffer[i], id, &i);
	buffer[i++] = '\t';
	while (str[j])
		buffer[i++] = str[j++];
	buffer[i++] = '\n';
	buffer[i] = '\0';
	write(1, buffer, ft_strlen(buffer));
}

void	num_to_buffer(char *buffer, t_ulong num, int *index)
{
	int	len;
	int	tmp;

	len = 0;
	tmp = num;
	if (num == 0)
	{
		buffer[0] = '0';
		*index += 1;
		return ;
	}
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	tmp = num;
	buffer[len] = '\0';
	*index += len;
	while (len > 0)
	{
		buffer[len - 1] = (tmp % 10) + '0';
		len--;
		tmp /= 10;
	}
}
