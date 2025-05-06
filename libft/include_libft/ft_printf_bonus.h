/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:08:35 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 14:33:58 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_int_format
{
	char	*str;
	char	*num;
	char	sign;
	int		num_len;
	int		pad_zeros;
	int		pad_spaces;
	int		total_len;
}			t_int_format;

typedef struct s_format
{
	int		fd;
	int		flag_minus;
	int		flag_zero;
	int		flag_plus;
	int		flag_space;
	int		flag_hash;
	int		width;
	int		precision;
	int		precision_specified;
	char	specifier;
}			t_format;

// ft_printf.c
int			ft_printf(const char *s, char *color, int fd, ...);
int			handle_format(t_format *format, va_list args);

// parsing.c
void		parse_format(const char **s, t_format *format, int fd);
void		fill_flag(const char **s, t_format *format);
void		fill_width(const char **s, t_format *format);
void		fill_precision(const char **s, t_format *format);
void		fill_specifier(const char **s, t_format *format);

// print_integer.c
int			print_integer(int n, t_format *f);

// print_char.c
int			print_char(char c, t_format *f);

// print_string.c
int			print_string(char *str, t_format *f);
int			print_string_spe(t_format *f);

// print_ptr.c
int			print_ptr(unsigned long ptr, t_format *f, int asc);

// print_unsigned.c
int			print_unsigned(unsigned int n, t_format *f);

// print_hexa.c
int			print_hexa(unsigned int n, t_format *f, int upper);

// utils.c
int			check_flag(t_format *f);
void		init_pads(int *pad_zeros, int *pad_spaces, int *total_len);
int			print_padding(int count, char c, int fd);

#endif