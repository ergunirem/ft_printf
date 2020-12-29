/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/25 15:23:29 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/12/29 23:28:55 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"
#include <stdio.h>
#include "debugger.c"

// char RED[] = "\033[1;31m";
// char GREEN[] = "\033[0;32m";
// char PURPLE[] = "\033[0;35m";
// char YELLOW[] = "\033[0;33m";
// char BLUE[] = "\033[0;36m";
// char RESET[]= "\033[0m";

int main(void)
{
	int				di = 28;


	// width with integer
	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling minimum field width%s (controls the min number of characters to print)\n", PURPLE, RESET);
	printf("%sA number follows flags or percentage sign > %%5d or %%23d\n\n%s", GREEN, RESET);
	printf(" (%d)\n", printf("(0) Mfw 0: |%0i|", 0));
	//ft_ppprintf(" (%d)\n", ft_printf("(0) Mfw 0: |%0i|", 0));
	printf(" (%d)\n", printf("(0) Mfw 1: |%1i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) Mfw 1: |%1i|", 0));
	printf(" (%d)\n", printf("Mfw 0: |%0i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 0: |%0i|", di));
	printf(" (%d)\n", printf("Mfw 1: |%1i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 1: |%1i|", di));
	printf(" (%d)\n", printf("Mfw 2: |%2i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 2: |%2i|", di));
	printf(" (%d)\n", printf("Mfw 3: |%3i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 3: |%3i|", di));
	printf(" (%d)\n", printf("Mfw 4: |%4i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 4: |%4i|", di));
	printf(" (%d)\n", printf("Mfw 5: |%5i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 5: |%5i|", di));
	printf(" (%d)\n", printf("Mfw 10: |%10i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 10: |%10i|", di));
	printf(" (%d)\n", printf("Mfw 35: |%35i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw 42: |%42i|", di));


	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling precision%s (controls the max number of characters to print)\n", PURPLE, RESET);
	printf("%sA dot (.) followed by a number > %%.5d or %%.02d\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) P. 0: |%.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P. 0: |%.0i|", 0));
	printf(" (%d)\n", printf("(0) P. 1: |%.1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P. 1: |%.1i|", 0));
	printf(" (%d)\n", printf("(0) P. 2: |%.2i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P. 2: |%.2i|", 0));
	printf(" (%d)\n", printf("P. 0: |%.0i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 0: |%.0i|", di));
	printf(" (%d)\n", printf("P. 1: |%.1i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 1: |%.1i|", di));
	printf(" (%d)\n", printf("P. 2: |%.2i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 2: |%.2i|", di));
	printf(" (%d)\n", printf("P. 3: |%.3i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 3: |%.3i|", di));
	printf(" (%d)\n", printf("P. 4: |%.4i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 4: |%.4i|", di));
	printf(" (%d)\n", printf("P. 5: |%.5i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 5: |%.5i|", di));
	printf(" (%d)\n", printf("P. 10: |%.10i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 10: |%.10i|", di));
	printf(" (%d)\n", printf("P. 15: |%.15i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 15: |%.15i|", di));
	printf(" (%d)\n", printf("P. 42: |%.42i|", di));
	ft_printf(" (%d)\n", ft_printf("P. 42: |%.42i|", di));

	printf("\n");
	printf(" (%d)\n", printf("(0) P .00: |%.00i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P .00: |%.00i|", 0));
	printf(" (%d)\n", printf("(0) P .01: |%.01i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P .01: |%.01i|", 0));
	printf(" (%d)\n", printf("P .00: |%.00i|", di));
	ft_printf(" (%d)\n", ft_printf("P .00: |%.00i|", di));
	printf(" (%d)\n", printf("P .01: |%.01i|", di));
	ft_printf(" (%d)\n", ft_printf("P .01: |%.01i|", di));
	printf(" (%d)\n", printf("P .02: |%.02i|", di));
	ft_printf(" (%d)\n", ft_printf("P .02: |%.02i|", di));
	printf(" (%d)\n", printf("P .03: |%.03i|", di));
	ft_printf(" (%d)\n", ft_printf("P .03: |%.03i|", di));
	printf(" (%d)\n", printf("P .04: |%.04i|", di));
	ft_printf(" (%d)\n", ft_printf("P .04: |%.04i|", di));
	printf(" (%d)\n", printf("P .05: |%.05i|", di));
	ft_printf(" (%d)\n", ft_printf("P .05: |%.05i|", di));
	printf(" (%d)\n", printf("P .010: |%.010i|", di));
	ft_printf(" (%d)\n", ft_printf("P .010: |%.010i|", di));
	printf(" (%d)\n", printf("P .015: |%.015i|", di));
	ft_printf(" (%d)\n", ft_printf("P .015: |%.015i|", di));
	printf(" (%d)\n", printf("P .042: |%.042i|", di));
	ft_printf(" (%d)\n", ft_printf("P .042: |%.042i|", di));

	printf(" (%d)\n", printf("P .007: |%.007i|", di));
	ft_printf(" (%d)\n", ft_printf("P .007: |%.007i|", di));
	printf(" (%d)\n", printf("P .000000000007: |%.000000000007i|", di));
	ft_printf(" (%d)\n", ft_printf("P .000000000007: |%.000000000007i|", di));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling precision & minimum field width%s\n", PURPLE, RESET);
	printf("%sNumbers followwed by a dot (.) followed by a number > %%10.5d or %%3.2d\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) 0.0: |%0.0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 0.0: |%0.0i|", 0));
	printf(" (%d)\n", printf("(0) 1.0: |%1.0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 1.0: |%1.0i|", 0));
	printf(" (%d)\n", printf("(10) 1.0: |%1.0i|", 10));
	// ft_printf(" (%d)\n", ft_printf("(10) 1.0: |%1.0i|", 10));
	printf(" (%d)\n", printf("(0) 0.1: |%0.1i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 0.1: |%0.1i|", 0));
	printf(" (%d)\n", printf("(0) 1.1: |%1.1i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 1.1: |%1.1i|", 0));
	printf(" (%d)\n", printf("0.0: |%0.0i|", di));
	// ft_printf(" (%d)\n", ft_printf("0.0: |%0.0i|", di));
	printf(" (%d)\n", printf("1.1: |%1.1i|", di));
	// ft_printf(" (%d)\n", ft_printf("1.1: |%1.1i|", di));
	printf(" (%d)\n", printf("2.2: |%2.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("2.2: |%2.2i|", di));
	printf(" (%d)\n", printf("3.2: |%3.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("3.2: |%3.2i|", di));
	printf(" (%d)\n", printf("2.3: |%2.3i|", di));
	// ft_printf(" (%d)\n", ft_printf("2.3: |%2.3i|", di));
	printf(" (%d)\n", printf("8.4: |%8.4i|", di));
	// ft_printf(" (%d)\n", ft_printf("8.4: |%8.4i|", di));
	printf(" (%d)\n", printf("4.8: |%4.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("4.8: |%4.8i|", di));
	printf(" (%d)\n", printf("8.8: |%8.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("8.8: |%8.8i|", di));
	printf(" (%d)\n", printf("8.2: |%8.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("8.2: |%8.2i|", di));
	printf(" (%d)\n", printf("2.8: |%2.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("2.8: |%2.8i|", di));
	printf(" (%d)\n", printf("8.1: |%8.1i|", di));
	// ft_printf(" (%d)\n", ft_printf("8.1: |%8.1i|", di));
	printf(" (%d)\n", printf("1.8: |%1.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("1.8: |%1.8i|", di));


	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling precision & minimum field width & (0) flag%s\n", PURPLE, RESET);
	printf("0 > Left-pads the number with zeroes (0) instead of spaces when padding is specified\n");
	printf("%s0 followed by numbers & a dot+a number > %%010.5d or %%03.2d\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) 00.0: |%00.0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 00.0: |%00.0i|", 0));
	printf(" (%d)\n", printf("(0) 01.0: |%01.0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 01.0: |%01.0i|", 0));
	printf(" (%d)\n", printf("(0) 00.1: |%00.1i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 00.1: |%00.1i|", 0));
	printf(" (%d)\n", printf("01.1: |%01.1i|", di));
	// ft_printf(" (%d)\n", ft_printf("01.1: |%01.1i|", di));
	printf(" (%d)\n", printf("02.2: |%02.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("02.2: |%02.2i|", di));
	printf(" (%d)\n", printf("03.2: |%03.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("03.2: |%03.2i|", di));
	printf(" (%d)\n", printf("02.3: |%02.3i|", di));
	// ft_printf(" (%d)\n", ft_printf("02.3: |%02.3i|", di));
	printf(" (%d)\n", printf("08.4: |%08.4i|", di));
	// ft_printf(" (%d)\n", ft_printf("08.4: |%08.4i|", di));
	printf(" (%d)\n", printf("04.8: |%04.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("04.8: |%04.8i|", di));
	printf(" (%d)\n", printf("08.8: |%08.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("08.8: |%08.8i|", di));
	printf(" (%d)\n", printf("08.2: |%08.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("08.2: |%08.2i|", di));
	printf(" (%d)\n", printf("02.8: |%02.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("02.8: |%02.8i|", di));
	printf(" (%d)\n", printf("08.1: |%08.1i|", di));
	// ft_printf(" (%d)\n", ft_printf("08.1: |%08.1i|", di));
	printf(" (%d)\n", printf("01.8: |%01.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("01.8: |%01.8i|", di));


	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling minimum field width & (0) flag%s\n", PURPLE, RESET);
	printf("0 > Left-pads the number with zeroes (0) instead of spaces when padding is specified\n");
	printf("%s0 followed by numbers > %%010d or %%03d\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) 0: |%0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 0: |%0i|", 0));
	printf(" (%d)\n", printf("(0) 00: |%00i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 00: |%00i|", 0));
	printf(" (%d)\n", printf("(0) 01: |%01i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 01: |%01i|", 0));
	printf(" (%d)\n", printf("(0) 02: |%02i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) 02: |%02i|", 0));
	printf(" (%d)\n", printf("0: |%0i|", di));
	// ft_printf(" (%d)\n", ft_printf("0: |%0i|", di));
	printf(" (%d)\n", printf("00: |%00i|", di));
	// ft_printf(" (%d)\n", ft_printf("00: |%00i|", di));
	printf(" (%d)\n", printf("01: |%01i|", di));
	// ft_printf(" (%d)\n", ft_printf("01: |%01i|", di));
	printf(" (%d)\n", printf("02: |%02i|", di));
	// ft_printf(" (%d)\n", ft_printf("02: |%02i|", di));
	printf(" (%d)\n", printf("03: |%03i|", di));
	// ft_printf(" (%d)\n", ft_printf("03: |%03i|", di));
	printf(" (%d)\n", printf("08: |%08i|", di));
	// ft_printf(" (%d)\n", ft_printf("08: |%08i|", di));
	printf(" (%d)\n", printf("000000000008: |%000000000008i|", di));
	// ft_printf(" (%d)\n", ft_printf("000000000008: |%000000000008i|", di));
	printf(" (%d)\n", printf("010: |%010i|", di));
	// ft_printf(" (%d)\n", ft_printf("010: |%010i|", di));
	printf(" (%d)\n", printf("0000000000010: |%0000000000010i|", di));
	// ft_printf(" (%d)\n", ft_printf("0000000000010: |%0000000000010i|", di));


	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling minimum field width & (0)(-) flag%s\n", PURPLE, RESET);
	printf("- > Left-justify within the given field width; Right justification is the default\n");
	printf("%s0- followed by numbers > %%-010d or %%0-3d\n\n%s", GREEN, RESET);

	// printf(" (%d)\n", printf("(0) -0: |%-0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -0: |%-0i|", 0));
	// printf(" (%d)\n", printf("(0) -00: |%-00i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -00: |%-00i|", 0));
	// printf(" (%d)\n", printf("(0) -01: |%-01i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -01: |%-01i|", 0));
	// printf(" (%d)\n", printf("(0) -02: |%-02i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -02: |%-02i|", 0));

	// printf(" (%d)\n", printf("-0: |%-0i|", di));
	// ft_printf(" (%d)\n", ft_printf("-0: |%-0i|", di));
	// printf(" (%d)\n", printf("-00: |%-00i|", di));
	// ft_printf(" (%d)\n", ft_printf("-00: |%-00i|", di));
	// printf(" (%d)\n", printf("-01: |%-01i|", di));
	// ft_printf(" (%d)\n", ft_printf("-01: |%-01i|", di));
	// printf(" (%d)\n", printf("-02: |%-02i|", di));
	// ft_printf(" (%d)\n", ft_printf("-02: |%-02i|", di));
	// printf(" (%d)\n", printf("-03: |%-03i|", di));
	// ft_printf(" (%d)\n", ft_printf("-03: |%-03i|", di));
	// printf(" (%d)\n", printf("-08: |%-08i|", di));
	// ft_printf(" (%d)\n", ft_printf("-08: |%-08i|", di));
	// printf(" (%d)\n", printf("0-8: |%0-8i|", di));
	// ft_printf(" (%d)\n", ft_printf("0-8: |%0-8i|", di));
	// printf(" (%d)\n", printf("-000000000008: |%-000000000008i|", di));
	// ft_printf(" (%d)\n", ft_printf("-000000000008: |%-000000000008i|", di));
	// printf(" (%d)\n", printf("-010: |%-010i|", di));
	// ft_printf(" (%d)\n", ft_printf("-010: |%-010i|", di));
	// printf(" (%d)\n", printf("-0000000000010: |%-0000000000010i|", di));
	// ft_printf(" (%d)\n", ft_printf("-0000000000010: |%-0000000000010i|", di));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling minimum field width & left justification%s\n", PURPLE, RESET);
	printf("- > Left-justify within the given field width; Right justification is the default\n");
	printf("%s- followed by numbers > %%-10d or %%-3d\n\n%s", GREEN, RESET);

	// not compiling! " " (%d)\n", printf("(0) Mfw -0: |%-0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) Mfw -0: |%-0i|", 0));
	printf(" (%d)\n", printf("(0) Mfw -1: |%-1i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) Mfw -1: |%-1i|", 0));
	printf(" (%d)\n", printf("(0) Mfw -2: |%-2i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) Mfw -2: |%-2i|", 0));

	// not compiling! " (%d)\n", printf("Mfw -0: |%-0i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -0: |%-0i|", di));
	printf(" (%d)\n", printf("Mfw -1: |%-1i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -1: |%-1i|", di));
	printf(" (%d)\n", printf("Mfw -2: |%-2i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -2: |%-2i|", di));
	printf(" (%d)\n", printf("Mfw -3: |%-3i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -3: |%-3i|", di));
	printf(" (%d)\n", printf("Mfw -4: |%-4i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -4: |%-4i|", di));
	printf(" (%d)\n", printf("Mfw -5: |%-5i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -5: |%-5i|", di));
	printf(" (%d)\n", printf("Mfw -10: |%-10i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -10: |%-10i|", di));
	printf(" (%d)\n", printf("Mfw --10: |%--10i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw --10: |%--10i|", di));
	printf(" (%d)\n", printf("Mfw ---10: |%---10i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw ---10: |%---10i|", di));
	printf(" (%d)\n", printf("Mfw -15: |%-15i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -15: |%-15i|", di));
	printf(" (%d)\n", printf("Mfw -42: |%-42i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -42: |%-42i|", di));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sHandling precision & minimum field width & left justification%s\n", PURPLE, RESET);

	//ppprintf(" (%d)\n", printf("(0) -0.0: |%-0.0i|", 0));
	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.0: |%-0.0i|", 0));
	///pppprintf(" (%d)\n", printf("(0) -0.1: |%-0.1i|", 0));
	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.1: |%-0.1i|", 0));
	printf(" (%d)\n", printf("(0) -1.0: |%-1.0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -1.0: |%-1.0i|", 0));
	printf(" (%d)\n", printf("(0) -1.1: |%-1.1i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -1.1: |%-1.1i|", 0));
	////ppprintf(" (%d)\n", printf("(0) -0.2: |%-0.2i|", 0));
	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.2: |%-0.2i|", 0));
	printf(" (%d)\n", printf("(0) -2.0: |%-2.0i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -2.0: |%-2.0i|", 0));
	printf(" (%d)\n", printf("(0) -2.2: |%-2.2i|", 0));
	// ft_printf(" (%d)\n", ft_printf("(0) -2.2: |%-2.2i|", 0));


	//ppprintf(" (%d)\n", printf("-0.0: |%-0.0i|", 5));
	// ft_ppprintf(" (%d)\n", ft_printf("-0.0: |%-0.0i|", 5));
	///pprintf(" (%d)\n", printf("-0.1: |%-0.1i|", 5));
	// ft_ppprintf(" (%d)\n", ft_printf("-0.1: |%-0.1i|", 5));
	printf(" (%d)\n", printf("-1.0: |%-1.0i|", 5));
	// ft_printf(" (%d)\n", ft_printf("-1.0: |%-1.0i|", 5));
	printf(" (%d)\n", printf("-1.1: |%-1.1i|", 5));
	// ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1i|", 5));
	printf(" (%d)\n", printf("-2.0: |%-2.0i|", 5));
	// ft_printf(" (%d)\n", ft_printf("-2.0: |%-2.0i|", 5));
	printf(" (%d)\n", printf("-2.2: |%-2.2i|", 5));
	// ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2i|", 5));


	printf(" (%d)\n", printf("-1.1: |%-1.1i|", di));
	// ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1i|", di));
	printf(" (%d)\n", printf("-2.2: |%-2.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2i|", di));
	printf(" (%d)\n", printf("-3.2: |%-3.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("-3.2: |%-3.2i|", di));
	printf(" (%d)\n", printf("-2.3: |%-2.3i|", di));
	// ft_printf(" (%d)\n", ft_printf("-2.3: |%-2.3i|", di));
	printf(" (%d)\n", printf("-8.4: |%-8.4i|", di));
	// ft_printf(" (%d)\n", ft_printf("-8.4: |%-8.4i|", di));
	printf(" (%d)\n", printf("-4.8: |%-4.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("-4.8: |%-4.8i|", di));
	printf(" (%d)\n", printf("-8.8: |%-8.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("-8.8: |%-8.8i|", di));
	printf(" (%d)\n", printf("-8.2: |%-8.2i|", di));
	// ft_printf(" (%d)\n", ft_printf("-8.2: |%-8.2i|", di));
	printf(" (%d)\n", printf("-2.8: |%-2.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("-2.8: |%-2.8i|", di));
	printf(" (%d)\n", printf("-8.1: |%-8.1i|", di));
	// ft_printf(" (%d)\n", ft_printf("-8.1: |%-8.1i|", di));
	printf(" (%d)\n", printf("-1.8: |%-1.8i|", di));
	// ft_printf(" (%d)\n", ft_printf("-1.8: |%-1.8i|", di));
	return (0);
}
