/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/25 15:23:29 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/12/31 19:14:34 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char RED[] = "\033[1;31m";
char GREEN[] = "\033[0;32m";
char PURPLE[] = "\033[0;35m";
char YELLOW[] = "\033[0;33m";
char BLUE[] = "\033[0;36m";
char RESET[]= "\033[0m";

int main(void)
{
	int				ndi;
	ndi = -28;

	int broken;
	int	bonus;

	char			c = 'F';
	char			*s = "my string example";
	int				di = 28;
	int				*p = &di;
	unsigned int	u = 42;
	unsigned int	xcap = 185334478;
	unsigned int	x = 185334478;

	broken = 0;
	bonus = 0;

	printf("%sBEGINNING OF COMPARISON TESTS\n\n\n%s", RED, RESET);
	printf("%sBLUE IS LIBRARY PRINTF TESTS\n%s", BLUE, RESET);
	ft_printf("%sGREEN IS MY FT_PRINTF TESTS\n\n%s", GREEN, RESET);

	printf("%s --- Basics --- \n\n%s", RED, RESET);
	printf(" (%d)\n", printf("%s|Regular input without arguments|%s", BLUE, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%s|Regular input without arguments|%s", GREEN, RESET));

	printf(" (%d)\n", printf("%sa single character: |%c|%s", BLUE, c, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sa single character: |%c|%s", GREEN, c, RESET));

	printf(" (%d)\n", printf("%sa string: |%s|%s", BLUE, s, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sa string: |%s|%s", GREEN, s, RESET));

	printf(" (%d)\n", printf("%sa decimal: |%d|%s", BLUE, di, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sa decimal: |%d|%s", GREEN, di, RESET));

	printf(" (%d)\n", printf("%san integer: |%i|%s", BLUE, di, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%san integer: |%i|%s", GREEN, di, RESET));

	printf(" (%d)\n", printf("%sa zero integer: |%i|%s", BLUE, 0, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sa zero integer: |%i|%s", GREEN, 0, RESET));

	printf(" (%d)\n", printf("%sa pointer: |%p|%s", BLUE, &di, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sa pointer: |%p|%s", GREEN, &di, RESET));

	printf(" (%d)\n", printf("%san unsignted int |%u|%s", BLUE, u, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%san unsignted int |%u|%s", GREEN, u, RESET));

	printf(" (%d)\n", printf("%sA HEXADECIMAL |%X|%s", BLUE, xcap, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sA HEXADECIMAL |%X|%s", GREEN, xcap, RESET));

	printf(" (%d)\n", printf("%sa hexadecimal |%x|%s", BLUE, x, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sa hexadecimal |%x|%s", GREEN, x, RESET));

	printf(" (%d)\n", printf("%sAll types at once: |%c %s %p %d %i %u %x %X|%s", BLUE, c, s, p, di, di, u, x, x, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sAll types at once: |%c %s %p %d %i %u %x %X|%s", GREEN, c, s, p, di, di, u, x, x, RESET));

	// %% //
	printf(" (%d)\n", printf("%s%% x 2 > double percentage sign: |%%|%s", BLUE, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%s%% x 2 > double percentage sign: |%%|%s", GREEN, RESET));

	printf(" (%d)\n", printf("%s|%s|%s", BLUE, "a percentage sign % in a string?", RESET));
	ft_printf(" (%d)\n\n", ft_printf("%s|%s|%s", GREEN, "a percentage sign % in a string?", RESET));

	printf(" (%d)\n", printf("Type conversion specifiers inside string: %s|%s|%s", BLUE, "%c, %s, %p, %d, %i, %u, %x, %X, %%", RESET));
	ft_printf(" (%d)\n\n", ft_printf("Type conversion specifiers inside string: %s|%s|%s", GREEN, "%c, %s, %p, %d, %i, %u, %x, %X, %%", RESET));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);

	// MIN - MAX
	printf("%sMIN & MAX values%s\n\n", RED, RESET);

	printf(" (%d)\n", printf("%sChar: |%c|%s", BLUE, '%', RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sChar: |%c|%s", GREEN, '%', RESET));

	printf(" (%d)\n", printf("%sMAX Decimal: |%d|%s", BLUE, 2147483647, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX Decimal: |%d|%s", GREEN, 2147483647, RESET));

	printf(" (%d)\n", printf("%sMIN Decimal: |%d|%s", BLUE, ((int)(-2147483648)), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMIN Decimal: |%d|%s", GREEN, ((int)(-2147483648)), RESET));

	printf(" (%d)\n", printf("%sMAX Integer: |%i|%s", BLUE, 2147483647, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX Integer: |%i|%s", GREEN, 2147483647, RESET));

	printf(" (%d)\n", printf("%sMIN Integer: |%i|%s", BLUE, ((int)(-2147483648)), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMIN Integer: |%i|%s", GREEN, ((int)(-2147483648)), RESET));

	printf(" (%d)\n", printf("%sMAX Unsignted int |%u|%s", BLUE, (unsigned int)4294967295, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX Unsignted int |%u|%s", GREEN, (unsigned int)4294967295, RESET));

	printf(" (%d)\n", printf("%sMAX INT AS HEXADECIMAL |%X|%s", BLUE, 2147483647, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX INT AS HEXADECIMAL |%X|%s", GREEN, 2147483647, RESET));

	printf(" (%d)\n", printf("%sMAX HEXADECIMAL |%X|%s", BLUE, ((unsigned int)(4294967295)), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX HEXADECIMAL |%X|%s", GREEN, ((unsigned int)(4294967295)), RESET));

	printf(" (%d)\n", printf("%sHEXadecimal with negative number |%X|%s", BLUE, -42, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sHEXadecimal with negative number |%X|%s", GREEN, -42, RESET));

	printf(" (%d)\n", printf("%sHexadecimal with negative number |%x|%s", BLUE, -42, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sHexadecimal with negative number |%x|%s", GREEN, -42, RESET));

	printf(" (%d)\n", printf("%sMAX int as hex |%x|%s", BLUE, 2147483647, RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX int as hex |%x|%s", GREEN, 2147483647, RESET));

	printf(" (%d)\n", printf("%sMAX hex |%x|%s", BLUE, ((unsigned int)(4294967295)), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX hex |%x|%s", GREEN, ((unsigned int)(4294967295)), RESET));

	// MIN - 1 & MAX + 1 values
	printf("%sMIN - 1 & MAX + 1 values%s\n\n", RED, RESET);

	printf(" (%d)\n", printf("%sChar: |%c|%s", BLUE, ('%' + 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sChar: |%c|%s", GREEN, ('%' + 1), RESET));

	printf(" (%d)\n", printf("%sMAX Decimal: |%d|%s", BLUE, (2147483647 + 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX Decimal: |%d|%s", GREEN, (2147483647 + 1), RESET));

	printf(" (%d)\n", printf("%sMIN Decimal: |%d|%s", BLUE, (((int)(-2147483648))- 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMIN Decimal: |%d|%s", GREEN, (((int)(-2147483648))- 1), RESET));

	printf(" (%d)\n", printf("%sMAX Integer: |%i|%s", BLUE, (2147483647 + 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX Integer: |%i|%s", GREEN, (2147483647 + 1), RESET));

	printf(" (%d)\n", printf("%sMIN Integer: |%i|%s", BLUE, (((int)(-2147483648))- 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMIN Integer: |%i|%s", GREEN, (((int)(-2147483648))- 1), RESET));

	//why are the results 0 for hex + 1's?
	printf(" (%d)\n", printf("%sMAX HEX |%X|%s", BLUE, (((unsigned int)(4294967295)) + 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX HEX |%X|%s", GREEN, (((unsigned int)(4294967295)) + 1), RESET));

	printf(" (%d)\n", printf("%sMAX hex |%x|%s", BLUE, (((unsigned int)(4294967295)) + 1), RESET));
	ft_printf(" (%d)\n\n", ft_printf("%sMAX hex |%x|%s", GREEN, (((unsigned int)(4294967295)) + 1), RESET));

	// width with integer
	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sMINIMUM FIELD WIDTH %s (controls the min number of characters to print)\n", RED, RESET);
	printf("%s%%5d or %%23d = A number follows flags or percentage sign\n\n%s", PURPLE, RESET);


	printf(" (%d)\n", printf("%s(0) Mfw 0: |%0i|%s", BLUE, 0, RESET));
	ft_printf(" (%d)\n", ft_printf("%s(0) Mfw 0: |%0i|%s", GREEN, 0, RESET));
	printf(" (%d)\n", printf("%s(0) Mfw 1: |%1i|%s", BLUE, 0, RESET));
	ft_printf(" (%d)\n", ft_printf("%s(0) Mfw 1: |%1i|%s", GREEN, 0, RESET));
	printf(" (%d)\n", printf("Mfw 0: |%0i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 0: |%0i|", ndi));
	printf(" (%d)\n", printf("Mfw 1: |%1i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 1: |%1i|", ndi));
	printf(" (%d)\n", printf("Mfw 2: |%2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 2: |%2i|", ndi));
	printf(" (%d)\n", printf("Mfw 3: |%3i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 3: |%3i|", ndi));
	printf(" (%d)\n", printf("Mfw 4: |%4i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 4: |%4i|", ndi));
	printf(" (%d)\n", printf("Mfw 5: |%5i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 5: |%5i|", ndi));
	printf(" (%d)\n", printf("Mfw 10: |%10i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 10: |%10i|", ndi));
	printf(" (%d)\n", printf("Mfw 35: |%35i|", ndi));
	ft_printf(" (%d)\n", ft_printf("Mfw 35: |%35i|", ndi));

	// precision
	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sPRECISION%s (controls the max number of characters to print)\n", RED, RESET);
	printf("%s%%.5d or %%.02d = A dot (.) followed by a number\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) P. 0: |%.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P. 0: |%.0i|", 0));
	printf(" (%d)\n", printf("(0) P. 1: |%.1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P. 1: |%.1i|", 0));
	printf(" (%d)\n", printf("(0) P. 2: |%.2i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P. 2: |%.2i|", 0));
	printf(" (%d)\n", printf("P. 0: |%.0i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 0: |%.0i|", ndi));
	printf(" (%d)\n", printf("P. 1: |%.1i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 1: |%.1i|", ndi));
	printf(" (%d)\n", printf("P. 2: |%.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 2: |%.2i|", ndi));
	printf(" (%d)\n", printf("P. 3: |%.3i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 3: |%.3i|", ndi));
	printf(" (%d)\n", printf("P. 4: |%.4i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 4: |%.4i|", ndi));
	printf(" (%d)\n", printf("P. 5: |%.5i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 5: |%.5i|", ndi));
	printf(" (%d)\n", printf("P. 10: |%.10i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 10: |%.10i|", ndi));
	printf(" (%d)\n", printf("P. 15: |%.15i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 15: |%.15i|", ndi));
	printf(" (%d)\n", printf("P. 42: |%.42i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P. 42: |%.42i|", ndi));

	printf("\n");
	printf(" (%d)\n", printf("(0) P .00: |%.00i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P .00: |%.00i|", 0));
	printf(" (%d)\n", printf("(0) P .01: |%.01i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) P .01: |%.01i|", 0));
	printf(" (%d)\n", printf("P .00: |%.00i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .00: |%.00i|", ndi));
	printf(" (%d)\n", printf("P .01: |%.01i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .01: |%.01i|", ndi));
	printf(" (%d)\n", printf("P .02: |%.02i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .02: |%.02i|", ndi));
	printf(" (%d)\n", printf("P .03: |%.03i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .03: |%.03i|", ndi));
	printf(" (%d)\n", printf("P .04: |%.04i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .04: |%.04i|", ndi));
	printf(" (%d)\n", printf("P .05: |%.05i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .05: |%.05i|", ndi));
	printf(" (%d)\n", printf("P .010: |%.010i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .010: |%.010i|", ndi));
	printf(" (%d)\n", printf("P .015: |%.015i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .015: |%.015i|", ndi));
	printf(" (%d)\n", printf("P .042: |%.042i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .042: |%.042i|", ndi));

	printf(" (%d)\n", printf("P .007: |%.007i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .007: |%.007i|", ndi));
	printf(" (%d)\n", printf("P .000000000007: |%.000000000007i|", ndi));
	ft_printf(" (%d)\n", ft_printf("P .000000000007: |%.000000000007i|", ndi));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sPRECISION & MINIMUM FIELD WIDTH%s\n", RED, RESET);
	printf("%s%%10.5d or %%3.2d = Numbers followwed by a dot (.) followed by a number\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) 0.0: |%0.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 0.0: |%0.0i|", 0));
	printf(" (%d)\n", printf("(0) 1.0: |%1.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 1.0: |%1.0i|", 0));
	printf(" (%d)\n", printf("(10) 1.0: |%1.0i|", 10));
	ft_printf(" (%d)\n", ft_printf("(10) 1.0: |%1.0i|", 10));
	printf(" (%d)\n", printf("(0) 0.1: |%0.1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 0.1: |%0.1i|", 0));
	printf(" (%d)\n", printf("(0) 1.1: |%1.1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 1.1: |%1.1i|", 0));
	printf(" (%d)\n", printf("0.0: |%0.0i|", ndi));
	ft_printf(" (%d)\n", ft_printf("0.0: |%0.0i|", ndi));
	printf(" (%d)\n", printf("1.1: |%1.1i|", ndi));
	ft_printf(" (%d)\n", ft_printf("1.1: |%1.1i|", ndi));
	printf(" (%d)\n", printf("2.2: |%2.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("2.2: |%2.2i|", ndi));
	printf(" (%d)\n", printf("3.2: |%3.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("3.2: |%3.2i|", ndi));
	printf(" (%d)\n", printf("2.3: |%2.3i|", ndi));
	ft_printf(" (%d)\n", ft_printf("2.3: |%2.3i|", ndi));
	printf(" (%d)\n", printf("8.4: |%8.4i|", ndi));
	ft_printf(" (%d)\n", ft_printf("8.4: |%8.4i|", ndi));
	printf(" (%d)\n", printf("4.8: |%4.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("4.8: |%4.8i|", ndi));
	printf(" (%d)\n", printf("8.8: |%8.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("8.8: |%8.8i|", ndi));
	printf(" (%d)\n", printf("8.2: |%8.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("8.2: |%8.2i|", ndi));
	printf(" (%d)\n", printf("2.8: |%2.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("2.8: |%2.8i|", ndi));
	printf(" (%d)\n", printf("8.1: |%8.1i|", ndi));
	ft_printf(" (%d)\n", ft_printf("8.1: |%8.1i|", ndi));
	printf(" (%d)\n", printf("1.8: |%1.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("1.8: |%1.8i|", ndi));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%s(0) flag & & MFW & PRECISION %s\n", RED, RESET);
	printf("0 > Left-pads the number with zeroes (0) instead of spaces when padding is specified\n");
	printf("%s%%010.5d or %%03.2d = 0 followed by numbers & a dot+a number\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) 00.0: |%00.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 00.0: |%00.0i|", 0));
	printf(" (%d)\n", printf("(0) 01.0: |%01.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 01.0: |%01.0i|", 0));
	printf(" (%d)\n", printf("(0) 00.1: |%00.1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 00.1: |%00.1i|", 0));
	printf(" (%d)\n", printf("01.1: |%01.1i|", ndi));
	ft_printf(" (%d)\n", ft_printf("01.1: |%01.1i|", ndi));
	printf(" (%d)\n", printf("02.2: |%02.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("02.2: |%02.2i|", ndi));
	printf(" (%d)\n", printf("03.2: |%03.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("03.2: |%03.2i|", ndi));
	printf(" (%d)\n", printf("02.3: |%02.3i|", ndi));
	ft_printf(" (%d)\n", ft_printf("02.3: |%02.3i|", ndi));
	printf(" (%d)\n", printf("08.4: |%08.4i|", ndi));
	ft_printf(" (%d)\n", ft_printf("08.4: |%08.4i|", ndi));
	printf(" (%d)\n", printf("04.8: |%04.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("04.8: |%04.8i|", ndi));
	printf(" (%d)\n", printf("08.8: |%08.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("08.8: |%08.8i|", ndi));
	printf(" (%d)\n", printf("08.2: |%08.2i|", ndi));
	ft_printf(" (%d)\n", ft_printf("08.2: |%08.2i|", ndi));
	printf(" (%d)\n", printf("02.8: |%02.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("02.8: |%02.8i|", ndi));
	printf(" (%d)\n", printf("08.1: |%08.1i|", ndi));
	ft_printf(" (%d)\n", ft_printf("08.1: |%08.1i|", ndi));
	printf(" (%d)\n", printf("01.8: |%01.8i|", ndi));
	ft_printf(" (%d)\n", ft_printf("01.8: |%01.8i|", ndi));


	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%sMFW & (0) flag%s\n", RED, RESET);
	printf("0 > Left-pads the number with zeroes (0) instead of spaces when padding is specified\n");
	printf("%s%%010d or %%03d=0 followed by numbers\n\n%s", GREEN, RESET);

	printf(" (%d)\n", printf("(0) 0: |%0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 0: |%0i|", 0));
	printf(" (%d)\n", printf("(0) 00: |%00i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 00: |%00i|", 0));
	printf(" (%d)\n", printf("(0) 01: |%01i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 01: |%01i|", 0));
	printf(" (%d)\n", printf("(0) 02: |%02i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) 02: |%02i|", 0));
	printf(" (%d)\n", printf("0: |%0i|", ndi));
	ft_printf(" (%d)\n", ft_printf("0: |%0i|", ndi));
	printf(" (%d)\n", printf("00: |%00i|", ndi));
	ft_printf(" (%d)\n", ft_printf("00: |%00i|", ndi));
	printf(" (%d)\n", printf("01: |%01i|", ndi));
	ft_printf(" (%d)\n", ft_printf("01: |%01i|", ndi));
	printf(" (%d)\n", printf("02: |%02i|", ndi));
	ft_printf(" (%d)\n", ft_printf("02: |%02i|", ndi));
	printf(" (%d)\n", printf("03: |%03i|", ndi));
	ft_printf(" (%d)\n", ft_printf("03: |%03i|", ndi));
	printf(" (%d)\n", printf("08: |%08i|", ndi));
	ft_printf(" (%d)\n", ft_printf("08: |%08i|", ndi));
	printf(" (%d)\n", printf("000000000008: |%000000000008i|", ndi));
	ft_printf(" (%d)\n", ft_printf("000000000008: |%000000000008i|", ndi));
	printf(" (%d)\n", printf("010: |%010i|", ndi));
	ft_printf(" (%d)\n", ft_printf("010: |%010i|", ndi));
	printf(" (%d)\n", printf("0000000000010: |%0000000000010i|", ndi));
	ft_printf(" (%d)\n", ft_printf("0000000000010: |%0000000000010i|", ndi));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%s(-) flag & MFW\n%s", RED, RESET);
	printf("- > Left-justify within the given field width; Right justification is the default\n");
	printf("%s%%-10d or %%-3d = (-) followed by numbers\n\n%s", GREEN, RESET);

	// not compiling! " " (%d)\n", printf("(0) Mfw -0: |%-0%si|",0));
	// ft_printf(" (%d)\n", ft_printf("(0) Mfw -0: |%-0i|", 0));
	printf(" (%d)\n", printf("(0) Mfw -1: |%-1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) Mfw -1: |%-1i|", 0));
	printf(" (%d)\n", printf("(0) Mfw -2: |%-2i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) Mfw -2: |%-2i|", 0));

	// not compiling! " (%d)\n", printf("Mfw -0: |%-0i|", di));
	// ft_printf(" (%d)\n", ft_printf("Mfw -0: |%-0i|", di));
	printf(" (%d)\n", printf("Mfw -1: |%-1i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -1: |%-1i|", di));
	printf(" (%d)\n", printf("Mfw -2: |%-2i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -2: |%-2i|", di));
	printf(" (%d)\n", printf("Mfw -3: |%-3i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -3: |%-3i|", di));
	printf(" (%d)\n", printf("Mfw -4: |%-4i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -4: |%-4i|", di));
	printf(" (%d)\n", printf("Mfw -5: |%-5i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -5: |%-5i|", di));
	printf(" (%d)\n", printf("Mfw -10: |%-10i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -10: |%-10i|", di));
	printf(" (%d)\n", printf("Mfw --10: |%--10i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw --10: |%--10i|", di));
	printf(" (%d)\n", printf("Mfw ---10: |%---10i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw ---10: |%---10i|", di));
	printf(" (%d)\n", printf("Mfw -15: |%-15i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -15: |%-15i|", di));
	printf(" (%d)\n", printf("Mfw -42: |%-42i|", di));
	ft_printf(" (%d)\n", ft_printf("Mfw -42: |%-42i|", di));

	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
	printf("%s(-) flag & MFW & PRECISION%s\n\n", RED, RESET);

	//ppprintf(" (%d)\n", printf("(0) -0.0: |%-0.0i|", 0));
	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.0: |%-0.0i|", 0));
	///pppprintf(" (%d)\n", printf("(0) -0.1: |%-0.1i|", 0));
	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.1: |%-0.1i|", 0));
	printf(" (%d)\n", printf("(0) -1.0: |%-1.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) -1.0: |%-1.0i|", 0));
	printf(" (%d)\n", printf("(0) -1.1: |%-1.1i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) -1.1: |%-1.1i|", 0));
	////ppprintf(" (%d)\n", printf("(0) -0.2: |%-0.2i|", 0));
	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.2: |%-0.2i|", 0));
	printf(" (%d)\n", printf("(0) -2.0: |%-2.0i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) -2.0: |%-2.0i|", 0));
	printf(" (%d)\n", printf("(0) -2.2: |%-2.2i|", 0));
	ft_printf(" (%d)\n", ft_printf("(0) -2.2: |%-2.2i|", 0));


	//ppprintf(" (%d)\n", printf("-0.0: |%-0.0i|", 5));
	// ft_ppprintf(" (%d)\n", ft_printf("-0.0: |%-0.0i|", 5));
	///pprintf(" (%d)\n", printf("-0.1: |%-0.1i|", 5));
	// ft_ppprintf(" (%d)\n", ft_printf("-0.1: |%-0.1i|", 5));
	printf(" (%d)\n", printf("-1.0: |%-1.0i|", 5));
	ft_printf(" (%d)\n", ft_printf("-1.0: |%-1.0i|", 5));
	printf(" (%d)\n", printf("-1.1: |%-1.1i|", 5));
	ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1i|", 5));
	printf(" (%d)\n", printf("-2.0: |%-2.0i|", 5));
	ft_printf(" (%d)\n", ft_printf("-2.0: |%-2.0i|", 5));
	printf(" (%d)\n", printf("-2.2: |%-2.2i|", 5));
	ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2i|", 5));


	printf(" (%d)\n", printf("-1.1: |%-1.1i|", di));
	ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1i|", di));
	printf(" (%d)\n", printf("-2.2: |%-2.2i|", di));
	ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2i|", di));
	printf(" (%d)\n", printf("-3.2: |%-3.2i|", di));
	ft_printf(" (%d)\n", ft_printf("-3.2: |%-3.2i|", di));
	printf(" (%d)\n", printf("-2.3: |%-2.3i|", di));
	ft_printf(" (%d)\n", ft_printf("-2.3: |%-2.3i|", di));
	printf(" (%d)\n", printf("-8.4: |%-8.4i|", di));
	ft_printf(" (%d)\n", ft_printf("-8.4: |%-8.4i|", di));
	printf(" (%d)\n", printf("-4.8: |%-4.8i|", di));
	ft_printf(" (%d)\n", ft_printf("-4.8: |%-4.8i|", di));
	printf(" (%d)\n", printf("-8.8: |%-8.8i|", di));
	ft_printf(" (%d)\n", ft_printf("-8.8: |%-8.8i|", di));
	printf(" (%d)\n", printf("-8.2: |%-8.2i|", di));
	ft_printf(" (%d)\n", ft_printf("-8.2: |%-8.2i|", di));
	printf(" (%d)\n", printf("-2.8: |%-2.8i|", di));
	ft_printf(" (%d)\n", ft_printf("-2.8: |%-2.8i|", di));
	printf(" (%d)\n", printf("-8.1: |%-8.1i|", di));
	ft_printf(" (%d)\n", ft_printf("-8.1: |%-8.1i|", di));
	printf(" (%d)\n", printf("-1.8: |%-1.8i|", di));
	ft_printf(" (%d)\n", ft_printf("-1.8: |%-1.8i|", di));

	printf("\n------------------------------------------------------------------------------------------------\n\n");

	printf(" (%d)\n", printf("Negative ints are a pain:"));
	ft_printf(" (%d)\n", ft_printf("Negative ints are a pain:"));
	printf("\n");

	int negative_int = -1994;

	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
	// printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
	printf("\n");

	negative_int = -2147483648;

	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
	// printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
	printf("\n");

	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
	printf("\n");


	printf("\n------------------------------------------------------------------------------------------------\n\n");

	printf(" (%d)\n", printf("Some edge cases I thought of whilst writing:"));
	ft_printf(" (%d)\n", ft_printf("Some edge cases I thought of whilst writing:"));
	printf("\n");

	printf(" (%d)\n", printf("8.: |%8.i|", 0));
	ft_printf(" (%d)\n", ft_printf("8.: |%8.i|", 0));
	printf(" (%d)\n", printf("8.: |%8.i|", 42));
	ft_printf(" (%d)\n", ft_printf("8.: |%8.i|", 42));
	printf(" (%d)\n", printf("8.: |%8.s|", "test"));
	ft_printf(" (%d)\n", ft_printf("8.: |%8.s|", "test"));
	// printf(" (%d)\n", printf("08.*(-4): |%08.*i|", -4, 42));
	// ft_printf(" (%d)\n", ft_printf("08.*(-4): |%08.*i|", -4, 42));
	// printf(" (%d)\n", printf("(string) 8.*(-5): |%8.*s|", -5, "test"));
	// ft_printf(" (%d)\n", ft_printf("(string) 8.*(-5): |%8.*s|", -5, "test"));

	return (0);
}
