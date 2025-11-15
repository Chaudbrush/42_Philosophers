/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:48:24 by vloureir          #+#    #+#             */
/*   Updated: 2025/11/12 20:43:34 by vloureir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int			args[5];
	t_program	data;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("-error: Invalid amount of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else if (parse_args(&argv[1], args))
		return (EXIT_FAILURE);
	else if (args[4] == 0)
		return (EXIT_SUCCESS);
	if (data_init(args, &data))
		return (EXIT_FAILURE);
	philos_init(&data);
	cleanup(&data);
	return (0);
}
