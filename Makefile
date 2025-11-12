# Makefile for CPU Scheduling Visualizer

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = scheduler
OBJS = main.o algorithms.o utils.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "✅ Build successful! Run with: ./$(TARGET)"

# Compile main.c
main.o: main.c process.h
	$(CC) $(CFLAGS) -c main.c

# Compile algorithms.c
algorithms.o: algorithms.c process.h
	$(CC) $(CFLAGS) -c algorithms.c

# Compile utils.c
utils.o: utils.c process.h
	$(CC) $(CFLAGS) -c utils.c

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "🧹 Cleaned build files"

# Run the program
run: $(TARGET)
	./$(TARGET)

# Create sample input file
sample:
	@echo "5" > processes.txt
	@echo "P1 0 5 2" >> processes.txt
	@echo "P2 1 3 1" >> processes.txt
	@echo "P3 2 8 3" >> processes.txt
	@echo "P4 3 6 2" >> processes.txt
	@echo "P5 4 4 1" >> processes.txt
	@echo "✅ Created sample processes.txt"

.PHONY: all clean run sample