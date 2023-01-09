/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:56:22 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/09 20:54:13 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	line_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] != ' ' && str[i] != '\t' && str[i] != '0' && str[i] != '1'
			&& str[i] != '\n' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != 'N' && str[i] != 'S')
			return (false);
		i++;
	}
	return (true);
}

int	exist_player(char *str, int drp)
{
	int i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if(str[i] == 'S' || str[i] == 'N' || str[i] == 'W' || str[i] == 'E')
		{
			res++;
			if(drp == 1)
				return (i);	
		}
		i++;
	}
	if(drp == 1)
		return (-1);
	return (res);	
}

bool	line_iswall(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '0')
			return (false);
		i++;
	}
	return (true);
}

void	check_walls(t_map *map)
{
	int	last;

	last = ft_spllen(map->matrice) - 1;

	if(!line_iswall(map->matrice[0]) || !line_iswall(map->matrice[last])|| exist_player(map->matrice[0],0) || 
		exist_player(map->matrice[last], 0))
		error_function("Invalid Map: walls");
}


void	check_map(t_map *map)
{
	int	i;
	int	flg;
	
	i = 0;
	flg = 0;
	while(map->matrice[i])
	{
		flg += exist_player(map->matrice[i], 0);
		if(!line_isdigit(map->matrice[i]) || flg > 1)
			error_function("Invalid Map");
		if(exist_player(map->matrice[i], 0) && exist_player(map->matrice[i], 1) != -1 )
		{
			map->y = i;
			map->x = exist_player(map->matrice[i], 1);
		}
		i++;
	}
	if(flg == 0)
		error_function("Invalid Map: No player");
	check_walls(map);
}




// printf("[%s]\n", map->matrice[i]);