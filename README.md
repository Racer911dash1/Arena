# Arena

## Description

Arena is a C library for streamlining memory allocation while minimizing accidental memory leaks. By giving responsibility down to a single variable, it becomes much simpler to free allocated memory.

## Installation

Clone the repository and enter
```sh
git clone https://codeberg.org/Racer911-1/Arena.git
cd Arena
make all
```
When installing this library system-wide use `make install`.

If you don't have sudo permissions or only want it for your login use `make install-local` instead.
Make sure to restart your profile with `. ~/.profile` after installing it locally.

To make use of the library in projects, you will need to provide the linker flag `-larena` when compiling the code.
```sh
cc main.c -larena
```

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

Go to the directory where you've cloned this repository and run. `make uninstall` or `make uninstall-local` depending on which installation type you picked.

## Roadmap

Adding more functions.

Adding more Unit tests.

Updating the Wiki page.

## Contributing

No Contributing guidelines yet. Feel free to create Issues or Pull Requests as you like.

## License

Apache 2.0