/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:43:17 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/09 19:07:26 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_function(char *str)
{
	printf("Error\n=> %s!\n", str);
	exit(1);
}

int	openfile(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if(fd < 0)
		error_function("file is not found");
	return (fd);
}

bool	str_direction(char *str)
{
	if(!ft_strncmp(str, "WE", ft_strlen(str)) || 
		!ft_strncmp(str, "EA", ft_strlen(str)) ||
		!ft_strncmp(str, "NO", ft_strlen(str)) || 
		!ft_strncmp(str, "SO", ft_strlen(str)))
		return (true);
	else
		return (false);
}

bool str_color(char *str)
{
	if(!ft_strncmp(str, "F", ft_strlen(str)) ||
		!ft_strncmp(str, "C", ft_strlen(str)))
		return (true);
	else
		return (false);
}

bool	sdigit(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	check_color(char *str)
{
	char	**spl;
	int		i;

	spl = ft_split(str, ',');
	if(ft_spllen(spl) != 3)
		error_function("Invalid Map: \"Colors\"");
	i = 0;
	while(i < 3)
	{
		if(!sdigit(spl[i]))
			error_function("Invalid Map: \"Colors\"");
		if(ft_atoi(spl[i]) < 0 || ft_atoi(spl[i]) > 255)
			error_function("Invalid Map: \"Colors\"");
		i++;
	}
}

void	collect_texture(t_data *data, char *dir, char *path)
{
	if(!str_color(dir))
		openfile(path);
	if(!ft_strncmp(dir, "NO", ft_strlen(dir)))
		data->no = path;
	else if(!ft_strncmp(dir, "SO", ft_strlen(dir)))
		data->so = path;
	else if(!ft_strncmp(dir, "WE", ft_strlen(dir)))
		data->we = path;
	else if(!ft_strncmp(dir, "EA", ft_strlen(dir)))
		data->ea = path;
	else if(!ft_strncmp(dir, "F", ft_strlen(dir)))
	{
		check_color(path);	
		data->f = path;
	}
	else if(!ft_strncmp(dir, "C", ft_strlen(dir)))
	{
		check_color(path);	
		data->c = path;
	}
}


void	collect_map(t_map *map, int fd, s_size size, char *str)
{
	int i;
	int j;

	map->matrice = malloc((size.maplines + 1) * sizeof(char*));
	if(!map->matrice)
		error_function("Allocation problem");
	i = 0;
	while(str)
	{
		if(str[ft_strlen(str) - 1] != '\n')
			str = ft_strcat(str, "\n");
		map->matrice[i] = malloc((size.longest ) * sizeof(char));
		if(!map->matrice[i])
			error_function("Allocation problem");
		map->matrice[i] = ft_strcpy(map->matrice[i], str);
		j = ft_strlen(str) - 1;
		while(j < size.longest - 1)
		{
			map->matrice[i][j] = ' ';
			j++;
		}
		map->matrice[i][j] = '\0';
		str = get_next_line(fd);
		i++;
	}
	map->matrice[i] = NULL;
}

void 	check_textures(int fd, int fd2, t_data *data, t_map *map)
{
	char *str;
	char **spl;
	int	i;
	int	drp;
	s_size	size;

	size = ft_textsize(fd2);
	str = get_next_line(fd);
	i = 0;
	drp = 0;
	while(i < size.textlines)
	{
		spl = ft_spl(str, ' ');
		if(ft_spllen(spl))
		{
			if(ft_spllen(spl) != 2 || (!str_direction(spl[0])
				&& !str_color(spl[0])))
				error_function("Invalide Map");
			if(!check_extension(spl[1], "xpm") && !str_color(spl[0]))
				error_function("Invalid extension \".xpm\" in the Map");
			collect_texture(data, spl[0], spl[1]);
			drp++;
		}
		i++;
		str = get_next_line(fd);
	}
	if(drp != 6)
		error_function("Invalid texture");
	collect_map(map, fd, size, str);
}


void parsing(int ac, char **av, t_data *data, t_map *map)
{
	int fd;
	int fd2;

	if(ac != 2)
		error_function("Invalid number of arguments");
	fd = openfile(av[1]);
	fd2 = openfile(av[1]);
	if(!check_extension(av[1], "cub"))
		error_function("Invalid extension: \".cub\"");
	check_textures(fd, fd2, data, map);
	check_map(map);
	close(fd);
	close(fd2);
}
