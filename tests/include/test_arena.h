#ifndef TEST_ARENA_H
# define TEST_ARENA_H

#include "arena.h"
#include "colors.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

# define RUN_TEST(function)										\
	do															\
	{															\
		int return_condition = (function)();					\
		if (return_condition == EXIT_SUCCESS)					\
		{														\
			fprintf(stdout, GREEN "OK " RESET);					\
		}														\
		else													\
		{														\
			fprintf(stderr, RED "KO " RESET "%s\n", #function);	\
		}														\
	} while (0)

#endif