/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:59:11 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/03 23:15:46 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	info_init(int argc, char**av, t_info *info)
{
	int	i;

	info->philos = ft_atoi(av[1]);
	info->t2die = ft_atoi(av[2]);
	info->t2eat = ft_atoi(av[3]);
	info->t2sleep = ft_atoi(av[4]);
	if (argc == 6)
		info->meals = ft_atoi(av[5]);
	else
		info->meals = -1;
	info->time_bc = 0;
	info->dead = 0;
	i = 0;
	while (i < info->philos)
	{
		info->forks[i] = 0;
		i++;
	}
}

int	parsing(int ac, char **av, t_info *info)
{
	if (ac != 5 && ac != 6)
	{
		printf("wrong amount of arguements\n");
		return (0);
	}
	else if (input_parsing(av))
	{
		info_init(ac, av, info);
		return (1);
	}
	else
	{
		printf("input invalid\n");
		return (0);
	}
}
