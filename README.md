# Arena

## Description

Arena is a C library for streamlining memory allocation while minimizing accidental memory leaks. By giving responsibility down to a single variable, it becomes much simpler to free allocated memory.

## Installation

Here's the bare minimum amount of steps needed.
```console
$> git clone https://codeberg.org/Racer911-1/Arena.git
$> cd Arena
$> make all
$> make install
```

This project uses Make to compile the library with the following rules.

`make all`: Compile the library to create a static libary `arena.a` and a shared object `arena.so.X.X.X` file.

`make install`: Copy the headers and libraries to their respective directories inside /usr/local (or similar). May require sudo permissions.

`make uninstall`: Remove the headers and libraries copied from the installment. May require sudo permissions.

`make clean`: Remove all object and dependency files, but keep the static library and shared object library.

`make fclean`: Remove all object and dependecy files, including the static library and shared object library.

`make test`: Run unit tests for all functions.

## Usage

Take this simple example
```c
#include "arena/arena.h"

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

You can learn more about the available functions in the wiki section.
[List of functions](https://codeberg.org/Racer911-1/Arena/wiki/Home)

## Roadmap

Adding more functions.

Adding more Unit tests.

Updating the Wiki page.

## Contributing

No Contributing guidelines yet. Feel free to create Issues or Pull Requests as you like.

## License

Apache 2.0