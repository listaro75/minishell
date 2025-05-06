/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximehanarte <maximehanarte@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:18:02 by maximehanar       #+#    #+#             */
/*   Updated: 2024/11/26 17:59:36 by maximehanar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*mem;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		mem = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(mem, del);
	}
	*lst = NULL;
}
