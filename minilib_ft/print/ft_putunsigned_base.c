/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:03:58 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:05:14 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_base_check(char	*base)
{
	int	i;
	int	z;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		z = i + 1;
		while (base[z] != '\0')
		{	
			if (base[i] == base[z])
				return (0);
			z++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static void	ft_print_base_numb(long nbr, char	*base)
{
	if ((long)(nbr % ft_strlen(base)) != nbr)
		ft_print_base_numb(nbr / ft_strlen(base), base);
	ft_putchar(base[nbr % ft_strlen(base)]);
}

void	ft_putunsigned_base(unsigned long nbr, char *base)
{
	if (!ft_base_check(base))
		return;
	ft_print_base_numb(nbr, base);
}
