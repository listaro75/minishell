/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:07:01 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:09:58 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	parse_format(const char **s, t_format *format, int fd)
{
	ft_bzero(format, sizeof(t_format));
	format->fd = fd;
	fill_flag(s, format);
	fill_width(s, format);
	fill_precision(s, format);
	fill_specifier(s, format);
	if (format->flag_minus)
		format->flag_zero = 0;
	if (format->flag_plus)
		format->flag_space = 0;
}

void	fill_flag(const char **s, t_format *format)
{
	while (**s && ft_strchr("-0+ #", **s))
	{
		if (**s == '-')
			format->flag_minus = 1;
		if (**s == '0')
			format->flag_zero = 1;
		if (**s == '+')
			format->flag_plus = 1;
		if (**s == ' ')
			format->flag_space = 1;
		if (**s == '#')
			format->flag_hash = 1;
		(*s)++;
	}
}

void	fill_width(const char **s, t_format *format)
{
	if (ft_isdigit(**s))
	{
		format->width = ft_atoi(*s);
		while (ft_isdigit(**s))
			(*s)++;
	}
}

void	fill_precision(const char **s, t_format *format)
{
	if (**s == '.')
	{
		format->precision_specified = 1;
		(*s)++;
		format->precision = ft_atoi(*s);
		while (ft_isdigit(**s))
			(*s)++;
	}
}

void	fill_specifier(const char **s, t_format *format)
{
	if (ft_strchr("cspdiuxX%", **s))
	{
		format->specifier = **s;
		(*s)++;
	}
}
