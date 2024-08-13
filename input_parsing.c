/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:22:19 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/07/29 19:52:12 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_parsing(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_isnum(str[i]) == 0)
			return (0);
		i++;
	}
	if (ft_atoi(str[1]) > 200 || ft_atoi(str[1]) == 0
		|| ft_atoi(str[2]) == 0 || ft_atoi(str[3]) == 0
		|| ft_atoi(str[4]) == 0)
		return (0);
	return (1);
}
