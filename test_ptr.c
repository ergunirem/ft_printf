/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_ptr.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/29 18:37:37 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/12/29 18:38:46 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.c"

int		main(void)
{
	// unsigned int val = 42;
	//void	*val = NULL;
	//char	*val = "An example string";

	 int		pointed = 867676769;
	 int		*val = &pointed;

	int broken = 0;
	int	bonus = 0;

	printf(" (%d)\n", printf("Handling precision"));
	ft_printf(" (%d)\n", ft_printf("Handling precision"));

	printf(" (%d)\n", printf("(0) Precis. 0: |%.0p|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) Precis. 0: |%.0p|", 0));
	printf(" (%d)\n", printf("(0) Precis. 1: |%.1p|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) Precis. 1: |%.1p|", 0));
	printf(" (%d)\n", printf("(0) Precis. 2: |%.2p|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) Precis. 2: |%.2p|", 0));
	printf(" (%d)\n", printf("Precis. 0: |%.0p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 0: |%.0p|", val));
	printf(" (%d)\n", printf("Precis. 1: |%.1p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 1: |%.1p|", val));
	printf(" (%d)\n", printf("Precis. 2: |%.2p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 2: |%.2p|", val));
	printf(" (%d)\n", printf("Precis. 3: |%.3p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 3: |%.3p|", val));
	printf(" (%d)\n", printf("Precis. 4: |%.4p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 4: |%.4p|", val));
	printf(" (%d)\n", printf("Precis. 5: |%.5p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 5: |%.5p|", val));
	printf(" (%d)\n", printf("Precis. 10: |%.10p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 10: |%.10p|", val));
	printf(" (%d)\n", printf("Precis. 15: |%.15p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 15: |%.15p|", val));
	printf(" (%d)\n", printf("Precis. 42: |%.42p|", val));
	ft_printf(" (%d)\n", ft_printf("Precis. 42: |%.42p|", val));

	printf(" (%d)\n", printf("(0) P .00: |%.00p|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P .00: |%.00p|", 0));
	printf(" (%d)\n", printf("(0) P .01: |%.01p|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P .01: |%.01p|", 0));
	printf(" (%d)\n", printf("P .00: |%.00p|", val));
	ft_printf(" (%d)\n", ft_printf("P .00: |%.00p|", val));
	printf(" (%d)\n", printf("P .01: |%.01p|", val));
	ft_printf(" (%d)\n", ft_printf("P .01: |%.01p|", val));
	printf(" (%d)\n", printf("P .02: |%.02p|", val));
	ft_printf(" (%d)\n", ft_printf("P .02: |%.02p|", val));
	printf(" (%d)\n", printf("P .03: |%.03p|", val));
	ft_printf(" (%d)\n", ft_printf("P .03: |%.03p|", val));
	printf(" (%d)\n", printf("P .04: |%.04p|", val));
	ft_printf(" (%d)\n", ft_printf("P .04: |%.04p|", val));
	printf(" (%d)\n", printf("P .05: |%.05p|", val));
	ft_printf(" (%d)\n", ft_printf("P .05: |%.05p|", val));
	printf(" (%d)\n", printf("P .010: |%.010p|", val));
	ft_printf(" (%d)\n", ft_printf("P .010: |%.010p|", val));
	printf(" (%d)\n", printf("P .015: |%.015p|", val));
	ft_printf(" (%d)\n", ft_printf("P .015: |%.015p|", val));
	printf(" (%d)\n", printf("P .042: |%.042p|", val));
	ft_printf(" (%d)\n", ft_printf("P .042: |%.042p|", val));

	printf(" (%d)\n", printf("P .007: |%.007p|", val));
	ft_printf(" (%d)\n", ft_printf("P .007: |%.007p|", val));
	printf(" (%d)\n", printf("P .000000000007: |%.000000000007p|", val));
	ft_printf(" (%d)\n", ft_printf("P .000000000007: |%.000000000007p|", val));

	return(0);
}
