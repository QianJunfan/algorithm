CC          = gcc
CFLAGS      = -Wall -Wextra -std=c99
LDFLAGS     =
TARGET      = alfred
SOURCES     = alfred.c
LOG_FILE    = progress.log

.PHONY: all run clean tidy

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
	# Clean up macOS Finder cruft
	find . -type f -name '.DS_Store' -delete
