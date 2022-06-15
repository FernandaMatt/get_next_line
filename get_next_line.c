//HEADER
int ft()
{
	static int i = 0;
	i ++;
	return (i);
}

#include <stdio.h>
int main(void)
{
	printf("%d\n", ft());
	printf("%d\n", ft());
	printf("%d\n", ft());
	return (0);
}
