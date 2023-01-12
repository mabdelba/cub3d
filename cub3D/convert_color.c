/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:48:01 by mabdelba          #+#    #+#             */
/*   Updated: 2023/01/12 18:54:42 by mabdelba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *c_tos(char c)
{
	char tab[2];

	tab[0] = c;
	tab[1] = '\0';

	return (ft_strdup(tab));
}

char *dec_to_hex(int n)
{
    char	hexa[2];
	int		temp;
	char	*ret;
 
    int i = 0;
    while(n != 0)
	{
		temp= 0;
        temp = n % 16;
        if (temp < 10)
		{
            hexa[i] = temp + 48;
            i++;
        }
        else 
		{
            hexa[i] = temp + 55;
            i++;
        }
        n = n / 16;
    }
 	ret = ft_strdup("");
    if (i == 2) {
        ret = ft_strjoin(ret, c_tos(hexa[1]));
        ret = ft_strjoin(ret, c_tos(hexa[0]));
    }
    else if (i == 1) {
        ret = ft_strdup("0");
		ret = ft_strjoin(ret, c_tos(hexa[0]));
    }
    else if (i == 0)
        ret = ft_strdup("00");

    return (ret);	
}

char *convert_rgb(int r, int g, int b)
{
	char *str;

	str = ft_strdup("");
	str = ft_strjoin(str, dec_to_hex(r));
	str = ft_strjoin(str, dec_to_hex(g));
	str = ft_strjoin(str, dec_to_hex(b));

	return (str);
}

int hex_to_dec(char *hexVal)
{
    int len;
	int base;
	int dec_val;
	int	i;

	len = ft_strlen(hexVal);
    base = 1;
    dec_val = 0;
	i = len - 1;
	while(i >= 0)
	{
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
		{
            dec_val += (hexVal[i] - 48) * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
		{
            dec_val += (hexVal[i] - 55) * base;
            base = base * 16;
        }
		i--;
	}
    return dec_val;
}


int	convert_color(char *str)
{
	char	**spl;
	char	*col;
	int		r;
	int 	g;
	int 	b;

	spl = ft_split(str, ',');
	r = ft_atoi(spl[0]);
	g = ft_atoi(spl[1]);
	b = ft_atoi(spl[2]);
	col = convert_rgb(r, g, b);
	return (hex_to_dec(col));
}