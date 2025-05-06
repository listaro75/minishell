/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximehanarte <maximehanarte@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:48:51 by maximehanar       #+#    #+#             */
/*   Updated: 2024/11/26 17:56:59 by maximehanar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*element;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	element = *lst;
	while (element && element->next)
		element = element->next;
	element->next = new;
	return ;
}
