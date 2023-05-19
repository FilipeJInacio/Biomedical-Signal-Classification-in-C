
CC= gcc
CFLAGS= -Wall -O3 -g 
LDFLAGS= -lm

SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

SRCS = $(wildcard $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
TARGET = exe

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) $(TARGET)
clear:
	$(RM) -r $(OBJDIR) $(TARGET)

run:
	./$(TARGET)