#include "lemin.h"

int	in_range(int num, int floor, int ceil)
{
	if (num >= floor && num <= ceil)
		return (1);
	return (0);
}