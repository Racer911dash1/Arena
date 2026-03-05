# Library Name
NAME := arena.a

# Archive
AR := ar rcs

# Directories
SRCDIR		:= src/
OBJDIR		:= obj/
INCDIR		:= include/
TESTDIR		:= tests/
TESTOBJDIR	:= $(TESTDIR)obj_test/

# Compiler and Flags
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra
CFLAGS		+= -MMD -MP -g
INCLUDES	:= -I $(INCDIR)
MAKEFLAGS	+= --no-print-directory

# Sources
SRCS :=	arena_calloc.c \
		arena_destroy.c \
		arena_build.c \
		arena_malloc.c \
		arena_strsplit_collapse.c \
		arena_strsplit_preserve.c \
		arena_strdup.c \
		arena_strndup.c \
		arena_strtrim.c \

TESTSRCS :=	test_arena_build.c \
			test_arena_calloc.c \
			test_arena_destroy.c \
			test_arena_malloc.c \
			test_arena_strsplit_collapse.c \
			test_arena_strsplit_preserve.c \
			test_arena_strdup.c \
			test_arena_strndup.c \
			test_arena_strtrim.c \

# Objects and Dependencies
SRCPATH	:= $(addprefix $(SRCDIR),$(SRCS))
OBJS	:= $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRCPATH:.c=.o))
DEPS	:= $(OBJS:.o=.d)

$(OBJDIR)%.o: $(SRCDIR)%.c Makefile | $(OBJDIR)
	@echo $(BLUE)Compiling $@$(RESET)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) Makefile
	@$(AR) $(NAME) $(OBJS)
	@echo $(GREEN)Library $(NAME) compiled$(RESET)

clean:
	@rm -rf $(OBJDIR) $(TESTOBJDIR) $(TESTDIR)*.test
	@echo $(GREEN)$(NAME) object files cleaned$(RESET)

fclean: clean
	@rm -rf $(NAME)
	@echo $(GREEN)$(NAME) cleaned$(RESET)

re:	fclean all

TESTPATH := $(addprefix $(TESTDIR),$(TESTSRCS))
.SECONDARY: OBJS_TEST := $(patsubst $(TESTDIR)%,$(TESTOBJDIR)%,$(TESTPATH:.c=.o))
DEPS_TEST := $(OBJS_TEST:.o=.d)

TESTEXES := $(addprefix $(TESTDIR), $(TESTSRCS:.c=.test))

$(TESTOBJDIR)%.o: $(TESTDIR)%.c Makefile | $(TESTOBJDIR)
	@echo $(BLUE)Compiling $@$(RESET)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TESTDIR)%.test: $(TESTOBJDIR)%.o $(NAME)
	@echo $(PURPLE)Linking $@$(RESET)
	@$(CC) $(CFLAGS) $< $(NAME) -o $@

test: $(NAME) $(TESTEXES)
	@for unit_test in $(TESTEXES); do \
		echo $(BRIGHT_BLUE)Testing $$unit_test$(RESET); \
		./$$unit_test; \
	done; \

$(OBJDIR):
	@mkdir -p $@

$(TESTOBJDIR):
	@mkdir -p $@

-include $(DEPS)
-include $(DEPS_TEST)

.PHONY: all clean fclean re test

# Colors
BLACK	:= "\e[0;30m"
RED		:= "\e[0;31m"
GREEN	:= "\e[0;32m"
YELLOW	:= "\e[0;33m"
BLUE	:= "\e[0;34m"
PURPLE	:= "\e[0;35m"
CYAN	:= "\e[0;36m"
WHITE	:= "\e[0;37m"

BRIGHT_BLUE	:= "\e[0;94m"

RESET	:= "\e[0m"