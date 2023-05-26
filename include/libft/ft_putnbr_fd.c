/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:45:23 by nsalhi            #+#    #+#             */
/*   Updated: 2022/11/09 18:11:40 by nsalhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	c;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		c = n * -1;
	}
	else
		c = n;
	if (c > 9)
	{
		ft_putnbr_fd(c / 10, fd);
		ft_putnbr_fd(c % 10, fd);
	}
	else
	{
		ft_putchar_fd(c + '0', fd);
	}
}
