/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:06:51 by nassm             #+#    #+#             */
/*   Updated: 2023/06/20 11:14:12 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc((n) * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1[i] && i <= n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
