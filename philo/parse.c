/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:41:45 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 14:57:52 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(char **av, int *args)
{
	int		i;

	i = 0;
	if (!av[4])
		args[4] = -1;
	while (av[i])
	{
		args[i] = mod_atoi(av[i]);
		if (args[i] < 0 || ft_strlen(av[i]) > 10 || !av[i][0])
		{
			ft_putstr_fd("-error: Invalid numeric argument\n", 2);
			return (1);
		}
		i++;
	}
	if (args[0] > 200)
	{
		ft_putstr_fd("-error: At maximum 200 philosophers\n", 2);
		return (1);
	}
	return (0);
}

int	mod_atoi(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] != '\0' || num > INT_MAX)
		return (-1);
	else
		return (num);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
