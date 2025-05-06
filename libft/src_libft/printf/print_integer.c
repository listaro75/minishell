/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:20:26 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:16:31 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	get_sign_char(int n, t_format *f)
{
	if (n < 0)
		return ('-');
	if (f->flag_plus)
		return ('+');
	if (f->flag_space)
		return (' ');
	return (0);
}

static void	update_pads(t_format *f, t_int_format *fmt, int sign_len)
{
	fmt->pad_zeros = 0;
	fmt->pad_spaces = 0;
	fmt->total_len = fmt->num_len + sign_len;
	if (f->precision_specified && f->precision > fmt->num_len)
	{
		fmt->pad_zeros = f->precision - fmt->num_len;
		fmt->total_len += fmt->pad_zeros;
	}
	if (f->width > fmt->total_len)
		fmt->pad_spaces = f->width - fmt->total_len;
}

static void	init_int_format(t_int_format *fmt, int n, t_format *f)
{
	fmt->str = ft_itoa(n);
	fmt->sign = get_sign_char(n, f);
	if (n < 0)
		fmt->num = fmt->str + 1;
	else
		fmt->num = fmt->str;
	fmt->num_len = ft_strlen(fmt->num);
	if (f->precision_specified && f->precision == 0 && n == 0)
		fmt->num_len = 0;
	update_pads(f, fmt, (fmt->sign != 0));
}

static int	write_integer_body(t_int_format *fmt, t_format *f)
{
	int	len;

	len = 0;
	if (!f->flag_minus && (!f->flag_zero || f->precision_specified))
		len += print_padding(fmt->pad_spaces, ' ', f->fd);
	if (fmt->sign)
		len += write(f->fd, &fmt->sign, 1);
	if (!f->precision_specified && f->flag_zero && !f->flag_minus)
		len += print_padding(fmt->pad_spaces, '0', f->fd);
	else
		len += print_padding(fmt->pad_zeros, '0', f->fd);
	if (fmt->num_len)
		len += write(f->fd, fmt->num, fmt->num_len);
	if (f->flag_minus)
		len += print_padding(fmt->pad_spaces, ' ', f->fd);
	return (len);
}

int	print_integer(int n, t_format *f)
{
	t_int_format	fmt;
	int				len;

	init_int_format(&fmt, n, f);
	len = write_integer_body(&fmt, f);
	free(fmt.str);
	return (len);
}
