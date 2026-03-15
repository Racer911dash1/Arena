# Project Name
PROJECT	:= libarena
VERSION	:= 1.3.1
PREFIX	?= /usr/local

# Directories
SRCDIR	:= src
OBJDIR	:= obj
INCDIR	:= $(PREFIX)/include/arena
LIBDIR	:= $(PREFIX)/lib

# Sources, Objects and Dependencies
SRCS :=	arena_build.c \
		arena_calloc.c \
		arena_destroy.c \
		arena_getnextline.c \
		arena_malloc.c \
		arena_merge.c \
		arena_strdup.c \
		arena_strjoin.c \
		arena_strndup.c \
		arena_strnjoin.c \
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
CFLAGS		+= -MMD -MP -g
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
all: $(STATIC_LIB) $(SHARED_LIB) ## Compile the library to create a static/shared libary file.

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
install: ## Install the headers and libraries system-wide. May require sudo permissions.
	@echo $(YELLOW)Installing $(PROJECT) in $(PREFIX)$(RESET)
	@echo $(GREEN)Creating $(DESTDIR)$(INCDIR) and $(DESTDIR)$(LIBDIR)$(RESET)
	@mkdir -p $(DESTDIR)$(INCDIR) $(DESTDIR)$(LIBDIR)

	@echo $(BLUE)Installing $(HEADERS) in $(DESTDIR)$(INCDIR)$(RESET)
	@install -m 644 $(HEADERS) $(DESTDIR)$(INCDIR)
	@echo $(BLUE)Installing $(STATIC_LIB) in $(DESTDIR)$(LIBDIR)$(RESET)
	@install -m 644 $(STATIC_LIB) $(DESTDIR)$(LIBDIR)
	@echo $(BLUE)Installing $(SHARED_LIB) in $(DESTDIR)$(LIBDIR)$(RESET)
	@install -m 755 $(SHARED_LIB) $(DESTDIR)$(LIBDIR)

	@echo $(PURPLE)Linking $(SHARED_LIB) with $(PROJECT).so$(RESET)
	@echo $(PURPLE)Linking $(SHARED_LIB) with $(PROJECT).so.$(SO_MAJOR)$(RESET)
	@cd $(DESTDIR)$(LIBDIR) && \
		ln -sf $(SHARED_LIB) $(PROJECT).so && \
		ln -sf $(SHARED_LIB) $(PROJECT).so.$(SO_MAJOR)

	@ldconfig
	@echo $(GREEN)Installation complete$(RESET)

.PHONY: uninstall
uninstall: ## Remove the system-wide installed headers and libraries. May require sudo permissions.
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

	@echo $(YELLOW)Uninstallation complete${RESET}

INSTALL_SCRIPT		:= install.sh
UNINSTALL_SCRIPT	:= uninstall.sh
LOCAL_DIR			:= $(HOME)/.local
INCDIR_LOCAL		:= $(LOCAL_DIR)/include/arena
LIBDIR_LOCAL		:= $(LOCAL_DIR)/lib

.PHONY: install-local
install-local: ## Install the headers and libraries locally inside ~/.local.
	@echo $(YELLOW)Installing $(PROJECT) in $(LOCAL_DIR)$(RESET)

	@echo $(GREEN)Creating $(INCDIR_LOCAL) and $(LIBDIR_LOCAL)$(RESET)
	@mkdir -p $(INCDIR_LOCAL) $(LIBDIR_LOCAL)

	@echo Running $(WHITE)$(INSTALL_SCRIPT)$(RESET)
	@./$(INSTALL_SCRIPT)

	@echo $(BLUE)Installing $(HEADERS) in $(INCDIR_LOCAL)$(RESET)
	@install -m 644 $(HEADERS) $(INCDIR_LOCAL)
	@echo $(BLUE)Installing $(STATIC_LIB) in $(LIBDIR_LOCAL)$(RESET)
	@install -m 644 $(STATIC_LIB) $(LIBDIR_LOCAL)
	@echo $(BLUE)Installing $(SHARED_LIB) in $(LIBDIR_LOCAL)$(RESET)
	@install -m 755 $(SHARED_LIB) $(LIBDIR_LOCAL)

	@echo $(PURPLE)Linking $(SHARED_LIB) with $(PROJECT).so$(RESET)
	@echo $(PURPLE)Linking $(SHARED_LIB) with $(PROJECT).so.$(SO_MAJOR)$(RESET)
	@cd $(LIBDIR_LOCAL) && \
		ln -sf $(SHARED_LIB) $(PROJECT).so && \
		ln -sf $(SHARED_LIB) $(PROJECT).so.$(SO_MAJOR)

	@echo $(GREEN)Local installation complete$(RESET)
	@echo Run \'$(BRIGHT_BLUE). \~/.profile$(RESET)\' or restart your terminal to apply changes

.PHONY: uninstall-local
uninstall-local: ## Remove the locally installed headers and libraries.
	@echo $(BRIGHT_RED)Removing $(PROJECT) from $(LOCAL_DIR)$(RESET)
	@rm -f $(INCDIR_LOCAL)/*.h

	@echo Running $(WHITE)$(UNINSTALL_SCRIPT)$(RESET)
	@./$(UNINSTALL_SCRIPT)

	@echo $(BRIGHT_RED)Removing $(INCDIR_LOCAL)$(RESET) \(if empty\)
	@rmdir --ignore-fail-on-non-empty $(INCDIR_LOCAL)

	@echo $(BRIGHT_RED)Removing $(LIBDIR_LOCAL)/$(STATIC_LIB)$(RESET)
	@rm -f $(LIBDIR_LOCAL)/$(STATIC_LIB)
	@echo $(BRIGHT_RED)Removing $(LIBDIR_LOCAL)/$(SHARED_LIB)$(RESET)
	@rm -f $(LIBDIR_LOCAL)/$(SHARED_LIB)

	@echo $(BRIGHT_RED)Removing $(LIBDIR_LOCAL)/$(PROJECT).so$(RESET)
	@rm -f $(LIBDIR_LOCAL)/$(PROJECT).so
	@echo $(BRIGHT_RED)Removing $(LIBDIR_LOCAL)/$(PROJECT).so.$(SO_MAJOR)$(RESET)
	@rm -f $(LIBDIR_LOCAL)/$(PROJECT).so.$(SO_MAJOR)

	@echo $(BRIGHT_RED)Removing $(LIBDIR_LOCAL)$(RESET) \(if empty\)
	@rmdir --ignore-fail-on-non-empty $(LIBDIR_LOCAL)

	@echo $(YELLOW)Local uninstallation complete$(RESET)
	@echo Restart your terminal to apply changes

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
TESTDIR		:= tests
TESTOBJDIR	:= $(TESTDIR)/obj
TESTSRCDIR	:= $(TESTDIR)/src

TESTCFLAGS		:= $(CFLAGS) -fsanitize=address
TESTINCLUDES	:= $(INCLUDES) -I $(TESTDIR)/include

TESTSRCS :=	test_arena_build.c \
			test_arena_calloc.c \
			test_arena_destroy.c \
			test_arena_getnextline.c \
			test_arena_malloc.c \
			test_arena_merge.c \
			test_arena_strdup.c \
			test_arena_strjoin.c \
			test_arena_strndup.c \
			test_arena_strnjoin.c \
			test_arena_strreplace.c \
			test_arena_strsplit_collapse.c \
			test_arena_strsplit_preserve.c \
			test_arena_strtrim.c \
			test_arena_substr.c \

TESTPATH := $(addprefix $(TESTSRCDIR)/,$(TESTSRCS))
.SECONDARY: TESTOBJS := $(patsubst $(TESTSRCDIR)%,$(TESTOBJDIR)%,$(TESTPATH:.c=.o))
TESTDEPS := $(TESTOBJS:.o=.d)
TESTEXES := $(addprefix $(TESTDIR)/, $(TESTSRCS:.c=.test))

$(TESTOBJDIR)/%.o: $(TESTSRCDIR)/%.c Makefile | $(TESTOBJDIR)
	@echo $(BLUE)Compiling $@$(RESET)
	@$(CC) $(TESTCFLAGS) $(TESTINCLUDES) -c $< -o $@

$(TESTDIR)/%.test: $(TESTOBJDIR)/%.o $(STATIC_LIB)
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