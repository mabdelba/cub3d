/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:56:22 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/11 23:51:29 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	char_isdirection(char c)
{
	if(c == 'E' || c == 'W' || c == 'S' || c == 'N')
		return (true);
	else
		return (false);
}


bool	line_isdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(str[i] != ' ' && str[i] != '0' && str[i] != '1'
			&& str[i] != '\n' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != 'N' && str[i] != 'S')
			return (false);
		i++;
	}
	return (true);
}

bool	line_isspace(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] != ' ')
			return(false);
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
			if(drp == 2)
				return (str[i]);
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

bool	vertical_walls(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	while(str[i])
	{
		if(str[i] == '1')
			break;
		if(str[i] == '0' || char_isdirection(str[i]))
			return (false);
		i++;
	}
	while(j >= 0)
	{
		if(str[j] == '1')
			break;
		if(str[j] == '0' || char_isdirection(str[j]))
			return (false);	
		j--;
	}
	return (true);
}

void	checkup_holes(char **str, int j)
{
	int	i;

	i = 0;
	if(str[i][j] == ' ')
	{
		i++;
		while(str[i] && str[i][j] != '1')
		{
			if(str[i][j] == '0' || char_isdirection(str[i][j]))
				error_function("Invalid Map: Map is not closed");
			i++;
		}
	}
}

void	checkdown_holes(char **str, int j)
{
	int	i;

	i = ft_spllen(str) - 1;
	if(str[i][j] == ' ')
	{
		i--;
		while(i >= 0 && str[i][j] != '1')
		{
			if(str[i][j] == '0' || char_isdirection(str[i][j]))
				error_function("Invalid Map: Map is not closed");
			i--;
		}
	}
}

void	check_holes(t_map *map)
{
	int	len;
	int	i;

	len = ft_strlen(map->matrice[0]);
	i = 0;
	while(i < len)
	{
		checkup_holes(map->matrice, i);
		checkdown_holes(map->matrice, i);		
		i++;
	}
}


void	check_walls(t_map *map)
{
	int	last;
	int i;

	i = 0;
	last = ft_spllen(map->matrice) - 1;
	if(!line_iswall(map->matrice[0]) || !line_iswall(map->matrice[last])|| exist_player(map->matrice[0],0) || 
		exist_player(map->matrice[last], 0))
		error_function("Invalid Map: walls");
	while (map->matrice[i])
	{
		if(!vertical_walls(map->matrice[i]))
			error_function("Invalid Map: walls");
		if(map->matrice[i+1] && line_isspace(map->matrice[i]))
		{
			if(!line_isspace(map->matrice[i+1]) && !line_iswall(map->matrice[i+1]))
				error_function("Invalid Map");
		}
		i++;
	}
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
			map->dir = (char)exist_player(map->matrice[i], 2);
		}
		i++;
	}
	if(flg == 0)
		error_function("Invalid Map: No player");
	check_walls(map);
	check_holes(map);
}


// printf("[%s]\n", map->matrice[i]);

