/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:20:10 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:41:23 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	handle_format(t_format *format, va_list args)
{
	if (format->specifier == 'c')
		return (print_char(va_arg(args, int), format));
	if (format->specifier == 's')
		return (print_string(va_arg(args, char *), format));
	if (format->specifier == 'p')
		return (print_ptr((unsigned long)va_arg(args, void *), format, 'a'
				- 10));
	if (format->specifier == 'd' || format->specifier == 'i')
		return (print_integer(va_arg(args, int), format));
	if (format->specifier == 'u')
		return (print_unsigned(va_arg(args, unsigned int), format));
	if (format->specifier == 'x')
		return (print_hexa(va_arg(args, unsigned int), format, 0));
	if (format->specifier == 'X')
		return (print_hexa(va_arg(args, unsigned int), format, 1));
	if (format->specifier == '%')
		return (write(format->fd, "%", 1));
	return (0);
}

int	ft_printf(const char *s, char *color, int fd, ...)
{
	va_list		args;
	int			len;
	t_format	format;

	if (!color)
		color = RESET;
	write(fd, color, ft_strlen(color));
	len = 0;
	va_start(args, fd);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			s++;
			parse_format(&s, &format, fd);
			len += handle_format(&format, args);
		}
		else
			len += write(fd, s++, 1);
	}
	va_end(args);
	write(fd, RESET, ft_strlen(RESET));
	return (len);
}
