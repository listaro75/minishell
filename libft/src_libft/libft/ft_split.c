/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:32:10 by mhanarte          #+#    #+#             */
/*   Updated: 2025/02/17 14:44:54 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkinput1(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*ft_countformalloc(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	while (s[i] == c && s[i])
		i++;
	return ((char *)s + i);
}

char	*ft_copy_word(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i + j] != '\0' && s[i + j] != c)
		j++;
	word = (char *)malloc(sizeof(char) * (j + 1));
	if (!word)
		return (NULL);
	k = 0;
	while (k < j)
	{
		word[k] = s[i + k];
		k++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_free_split(char **array, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(array[j]);
		j++;
	}
	free (array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	char	**array;

	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	count = ft_checkinput1(s, c);
	i = 0;
	array = (char **) malloc (sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	while (i < count)
	{
		array[i] = ft_copy_word(s, c);
		if (!array[i])
			return (ft_free_split(array, i));
		s = ft_countformalloc(s, c);
		i++;
	}
	array[i] = NULL;
	return (array);
}

// int	main(void)
// {
// 	char	str[]="cccbonjourccheycchelloc";
// 	char	c = 'c';
// 	char	**strr;
// 	int	i;
// 	i = 0;
// 	strr = ft_split(str, c);
// 	while (strr[i])
// 	{
// 		printf("%s\n", strr[i]);
// 		free (strr[i]);
// 		i++;
// 	}
// 	return (0);
// }