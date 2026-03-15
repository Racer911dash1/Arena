# Arena

## Description

Arena is a C library for streamlining memory allocation while minimizing accidental memory leaks. By giving responsibility down to a single variable, it becomes much simpler to free allocated memory.

## Installation

There's a few ways to install this library, but this is the first thing you want to do regardless of what path you pick.
```sh
git clone https://codeberg.org/Racer911-1/Arena.git
cd Arena
make all
```
When installing system-wide.
```sh
make install
```
When installing locally
```sh
make install-local
```

When compiling your project, use the linker flag -larena like so
```sh
cc main.c -larena
```

This project uses Make to compile the library, for more info on which rules are available, use `make help`.

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

## Uninstalling

Go to the directory where you've cloned this repository and run.
```sh
make uninstall
```
or
```sh
make uninstall-local
```
depending on which installation you picked.

## Roadmap

Adding more functions.

Adding more Unit tests.

Updating the Wiki page.

## Contributing

No Contributing guidelines yet. Feel free to create Issues or Pull Requests as you like.

## License

Apache 2.0