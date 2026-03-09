# Project Name
PROJECT	:= arena
VERSION	:= 1.2.0
PREFIX	?= /usr/local

# Directories
SRCDIR	:= src
OBJDIR	:= obj
INCDIR	:= $(PREFIX)/include/$(PROJECT)
LIBDIR	:= $(PREFIX)/lib

# Sources, Objects and Dependencies
SRCS :=	arena_build.c \
		arena_calloc.c \
		arena_destroy.c \
		arena_malloc.c \
		arena_strdup.c \
		arena_strjoin.c \
		arena_strndup.c \
		arena_strreplace.c \
		arena_strsplit_collapse.c \
		arena_strsplit_preserve.c \
		arena_strtrim.c \
		arena_substr.c \

SRCPATH	:= $(addprefix $(SRCDIR)/,$(SRCS))
OBJS	:= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCPATH:.c=.o))
DEPS	:= $(OBJS:.o=.d)

# Compiler and Flags
CC			:= cc
CFLAGS		:= -Wall -Wextra -O2 -fPIC
CFLAGS		+= -MMD -MP
INCLUDES	:= -I include/arena	-I include
AR			:= ar
ARFLAGS		:= rcs
ifndef VERBOSE
MAKEFLAGS	+= --no-print-directory
endif

# Static Library
STATIC_LIB := $(PROJECT).a

# Shared Library
SHARED_LIB	:= $(PROJECT).so.$(VERSION)
SO_MAJOR	:= $(word 1,$(subst ., ,$(VERSION)))
SO_MINOR	:= $(word 2,$(subst ., ,$(VERSION)))
SONAME		:= $(PROJECT).so.$(SO_MAJOR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile | $(OBJDIR)
	@echo $(BLUE)Compiling $@$(RESET)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: help
help: ## Show all Makefile rules.
	@grep -h '\s##\s' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf ""$(CYAN)"  %-20s"$(RESET)" %s\n", $$1, $$2}'

.PHONY: all
all: $(STATIC_LIB) $(SHARED_LIB) ## Compile the library to create a static libary arena.a and a shared object arena.so.X.X.X file.

$(STATIC_LIB): $(OBJS) Makefile
	@$(AR) $(ARFLAGS) $(STATIC_LIB) $(OBJS)
	@echo $(GREEN)Static Library $(STATIC_LIB) compiled$(RESET)

$(SHARED_LIB): $(OBJS)
	@$(CC) -shared -Wl,-soname,$(SONAME) -o $@ $^
	@echo $(GREEN)Shared Object $(SHARED_LIB) compiled$(RESET)

$(OBJDIR):
	@mkdir -p $@

HEADERS := $(wildcard include/$(PROJECT)/*.h) $(wildcard include/*.h)

.PHONY: install
install: ## Copy the headers and libraries to their respective directories inside /usr/local (or similar). May require sudo permissions.
	@echo $(YELLOW)Installing $(PROJECT) in $(PREFIX)$(RESET)
	@echo $(GREEN)Creating $(DESTDIR)$(INCDIR) and $(DESTDIR)$(LIBDIR)$(RESET)
	@mkdir -p $(DESTDIR)$(INCDIR) $(DESTDIR)$(LIBDIR)

	@echo $(BLUE)Installing $(HEADERS) in $(DESTDIR)$(INCDIR)$(RESET)
	@install -m 644 $(HEADERS) $(DESTDIR)$(INCDIR)
	@echo $(BLUE)Installing $(STATIC_LIB) in $(DESTDIR)$(LIBDIR)$(RESET)
	@install -m 644 $(STATIC_LIB) $(DESTDIR)$(LIBDIR)
	@echo $(BLUE)Installing $(SHARED_LIB) in $(DESTDIR)$(LIBDIR)$(RESET)
	@install -m 644 $(SHARED_LIB) $(DESTDIR)$(LIBDIR)
	@echo $(PURPLE)Linking $(SHARED_LIB) with $(PROJECT).so$(RESET)
	@echo $(PURPLE)Linking $(SHARED_LIB) with $(PROJECT).so.$(SO_MAJOR)$(RESET)
	@cd $(DESTDIR)$(LIBDIR) && \
		ln -sf $(SHARED_LIB) $(PROJECT).so && \
		ln -sf $(SHARED_LIB) $(PROJECT).so.$(SO_MAJOR)

	@echo $(GREEN)Installation complete$(RESET)

.PHONY: uninstall
uninstall: ## Remove the headers and libraries copied from the installment. May require sudo permissions.
	@echo $(BRIGHT_RED)Removing $(PROJECT) from $(PREFIX)$(RESET)
	@rm -f $(DESTDIR)$(INCDIR)/*.h
	@echo $(BRIGHT_RED)Removing $(DESTDIR)$(INCDIR)$(RESET) \(if empty\)
	@rmdir --ignore-fail-on-non-empty $(DESTDIR)$(INCDIR)
	@echo $(BRIGHT_RED)Removing $(DESTDIR)$(LIBDIR)/$(STATIC_LIB)$(RESET)
	@rm -f $(DESTDIR)$(LIBDIR)/$(STATIC_LIB)
	@echo $(BRIGHT_RED)Removing $(DESTDIR)$(LIBDIR)/$(SHARED_LIB)$(RESET)
	@rm -f $(DESTDIR)$(LIBDIR)/$(SHARED_LIB)
	@echo $(BRIGHT_RED)Removing $(DESTDIR)$(LIBDIR)/$(PROJECT).so$(RESET)
	@rm -f $(DESTDIR)$(LIBDIR)/$(PROJECT).so
	@echo $(BRIGHT_RED)Removing $(DESTDIR)$(LIBDIR)/$(PROJECT).so.$(SO_MAJOR)$(RESET)
	@rm -f $(DESTDIR)$(LIBDIR)/$(PROJECT).so.$(SO_MAJOR)
	@echo $(BRIGHT_RED)Removing $(DESTDIR)$(LIBDIR)$(RESET) \(if empty\)
	@rmdir --ignore-fail-on-non-empty $(DESTDIR)$(LIBDIR)

.PHONY: clean
clean: ## Remove all object and dependency files, but keep the static library and shared object library.
	@echo $(BRIGHT_RED)Removing $(OBJDIR) $(TESTOBJDIR) $(TESTDIR)*.test$(RESET)
	@rm -rf $(OBJDIR) $(TESTOBJDIR) $(TESTDIR)*.test
	@echo $(BRIGHT_RED)Objects cleaned$(RESET)

.PHONY: fclean
fclean: clean ## Remove all object and dependecy files, including the static library and shared object library.
	@echo $(BRIGHT_RED)Removing $(STATIC_LIB) $(SHARED_LIB)$(RESET)
	@rm -f $(STATIC_LIB) $(SHARED_LIB)
	@echo $(BRIGHT_RED)$(PROJECT) cleaned$(RESET)

# Unit tests
TESTDIR		:= tests/
TESTOBJDIR	:= $(TESTDIR)obj_test/

TESTCFLAGS	:= $(CFLAGS) -g -fsanitize=address

TESTSRCS :=	test_arena_build.c \
			test_arena_calloc.c \
			test_arena_destroy.c \
			test_arena_malloc.c \
			test_arena_strdup.c \
			test_arena_strjoin.c \
			test_arena_strndup.c \
			test_arena_strreplace.c \
			test_arena_strsplit_collapse.c \
			test_arena_strsplit_preserve.c \
			test_arena_strtrim.c \
			test_arena_substr.c \

TESTPATH := $(addprefix $(TESTDIR),$(TESTSRCS))
.SECONDARY: TESTOBJS := $(patsubst $(TESTDIR)%,$(TESTOBJDIR)%,$(TESTPATH:.c=.o))
TESTDEPS := $(TESTOBJS:.o=.d)
TESTEXES := $(addprefix $(TESTDIR), $(TESTSRCS:.c=.test))

$(TESTOBJDIR)%.o: $(TESTDIR)%.c Makefile | $(TESTOBJDIR)
	@echo $(BLUE)Compiling $@$(RESET)
	@$(CC) $(TESTCFLAGS) $(INCLUDES) -c $< -o $@

$(TESTDIR)%.test: $(TESTOBJDIR)%.o $(STATIC_LIB)
	@echo $(PURPLE)Linking $@$(RESET)
	@$(CC) $(TESTCFLAGS) $< $(STATIC_LIB) -o $@

.PHONY: test
test: all $(TESTEXES) ## Run unit tests for all functions.
	@for unit_test in $(TESTEXES); do \
		echo $(BRIGHT_BLUE)Testing $$unit_test$(RESET); \
		./$$unit_test; \
	done; \

$(TESTOBJDIR):
	@mkdir -p $@

-include $(DEPS)
-include $(TESTDEPS)

# Colors
BLACK	:= "\033[0;30m"
RED		:= "\033[0;31m"
GREEN	:= "\033[0;32m"
YELLOW	:= "\033[0;33m"
BLUE	:= "\033[0;34m"
PURPLE	:= "\033[0;35m"
CYAN	:= "\033[0;36m"
WHITE	:= "\033[0;37m"

BRIGHT_RED	:= "\033[0;91m"
BRIGHT_BLUE	:= "\033[0;94m"

RESET	:= "\033[0m"