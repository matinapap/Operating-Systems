CFLAGS ?= -Wall -Wextra -O2
BIN    := bin

.PHONY: all run-process-tree run-threads clean

all: $(BIN)/process_tree $(BIN)/threads_posix

$(BIN)/process_tree: src/process_tree.c | $(BIN)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN)/threads_posix: src/threads_posix.c | $(BIN)
	$(CC) $(CFLAGS) -pthread -o $@ $<

$(BIN):
	mkdir -p $@

run-process-tree: $(BIN)/process_tree
	./$<

run-threads: $(BIN)/threads_posix
	./$<

clean:
	rm -rf $(BIN)
