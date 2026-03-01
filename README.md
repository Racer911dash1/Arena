# Arena

## Description

Arena is a C library for streamlining memory allocation while minimizing accidental memory leaks. By giving responsibility down to a single variable, it becomes much simpler to free allocated memory.

## Installation

Download the .zip and unzip it in the library directory of your project.

This project uses Make to compile the library with the following rules.

`make all`: Compile the library to create a static libary `arena.a` file.

`make clean`: Remove all object and dependency files, but keep the static library.

`make fclean`: Remove all object and dependecy files, including the static library.

`make re`: Recompile the library. Same as calling `make fclean` and then `make all`.

`make test`: Run unit tests for all functions.

## Usage

Take this simple example
```c
#include "arena.h"

int main(void)
{
	t_arena arena;
	char* ptr1;
	char* ptr2;
	char* ptr3;

	arena_build(&arena); // Initialize the arena
	ptr1 = arena_malloc(&arena, 8);
	ptr2 = arena_malloc(&arena, 40);
	ptr3 = arena_malloc(&arena, 97);
	arena_destroy(&arena); // Free the memory
}
```

Instead of calling free() 3 times for each variable, you only need to call a single function once.

## Roadmap

Adding more functions.

Adding more Unit tests.

## Contributing

No Contributing guidelines yet. Feel free to create Issues or Pull Requests as you like.

## License

Apache 2.0