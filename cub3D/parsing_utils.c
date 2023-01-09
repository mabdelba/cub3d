/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:29:06 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/08 00:31:30 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_spllen(char **spl)
{
	int	i;

	i = 0;
	while(spl[i])
		i++;
	return (i);
}

bool	check_extension(char *str, char *ext)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(str) - 4;
	if(str[j] != '.')
		return	(false);
	j++;
	while (ext[i])
	{
		if(ext[i] != str[j])
			return (false);
		i++;
		j++;
	}
	return (true);	
}


bool	digit_string(char *str)
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
	if(ft_strchr(str, '0') != 0 || ft_strchr(str, '1') != 0)
		return (true);
	else
		return (false);
}

s_size	ft_textsize(int fd)
{
	char	*ptr;
	s_size	size;
	int		drp;

	ptr = get_next_line(fd);
	size.textlines = 0;
	size.maplines = 0;
	size.longest = ft_strlen(ptr);
	drp = 0;
	while (ptr)
	{
		if(digit_string(ptr))
			drp = 1;
		if(!digit_string(ptr) && drp == 0)
			size.textlines++;
		else if(drp == 1)
			size.maplines++;
		if((int)ft_strlen(ptr) > size.longest)
			size.longest = ft_strlen(ptr);
		ptr = get_next_line(fd);
	}
	close(fd);
	return (size);
}