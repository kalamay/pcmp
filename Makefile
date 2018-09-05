CFLAGS := -std=c99 -Wall -Wextra -pedantic -Werror -O2 -g
BUILD := build
BIN := $(BUILD)/bin
OBJ := $(BUILD)/obj
TESTS := $(patsubst test/%.c,%,$(wildcard test/*.c))
PERFS := $(patsubst test/perf/%.c,%,$(wildcard test/perf/*.c))

all: test

test: test-basic test-sse test-avx

test-basic: $(TESTS:%=$(BIN)/%-basic)
	@echo "*** default tests ***"
	@for name in $^; do ./$$name || exit; done

test-sse: $(TESTS:%=$(BIN)/%-sse)
	@echo "*** sse4.2 tests ***"
	@for name in $^; do ./$$name || exit; done

test-avx: $(BIN)/eq-avx $(BIN)/leq-avx #$(TESTS:%=$(BIN)/%-avx)
	@echo "*** avx2 tests ***"
	@for name in $^; do ./$$name || exit; done

perf: $(PERFS:%=$(BIN)/%-perf)
	@for name in $^; do ./$$name || exit; done

-include $(wildcard $(OBJ)/*.d)

$(BIN)/%-basic: test/%.c | $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -MMD -MT $@ -MF $(OBJ)/$*-basic.d $< -o $@

$(BIN)/%-sse: test/%.c | $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -msse4 -MMD -MT $@ -MF $(OBJ)/$*-sse.d $< -o $@

$(BIN)/%-avx: test/%.c | $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -mavx2 -MMD -MT $@ -MF $(OBJ)/$*-avx.d $< -o $@

$(BIN)/%-perf: test/perf/%.c | $(OBJ) $(BIN)
	$(CC) $(CFLAGS) -march=native -MMD -MT $@ -MF $(OBJ)/$*-perf.d $< -o $@

$(BIN) $(OBJ):
	@mkdir -p $@

clean:
	rm -rf build

.PHONY: clean test test-basic test-sse perf

