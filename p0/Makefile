CC = gcc
AR = ar
#LDFLAGS = -static (see "-static" below)

# -O0 is needed so that gcc doesn't "helpfully" optimize the
#  # calling convention for static functions.
CFLAGS = -Wall -Werror -gdwarf-2 -O0 -m32 -fno-stack-protector -fno-omit-frame-pointer -Itraceback/

# If you don't do this, GCC4 will emit code which causes main() to align its
# # stack to a 16-byte boundary. This will cause the base pointer for that
# # function to point into the middle of some padding space allocated to align the
# # stack. GCC4 accesses the arguments to main through an offset stored in %ecx
# # instead of %ebp.
# # n.b.: -mpreferred-stack-boundary=n aligns the stack to 2^n bytes in all
# # functions.
# CFLAGS += -mpreferred-stack-boundary=2

%.o: %.c
	@expand -t $(TABSTOP) $< | awk 'length > 80 \
      { err++; \
        errs[err] = "Warning: line " NR " in $< is longer than 80 characters"; \
      } END { \
        if (err > 2 && err < 1000) {for (i = 1; i <= err; i++) print errs[i]; system("sleep 5");}\
        exit(err > 10 && err < 1000) }'
	$(CC) -c -o $@ $(CFLAGS) $(LDFLAGS) $^

%.o: %.S
	$(CC) -c -o $@ -DASSEMBLER $(CFLAGS) $(LDFLAGS) $^

.PHONY: get_started update

get_started:
	./update.sh
	$(MAKE)

update: get_started

tests/add_one_test: tests/add_one.o tests/add_one_test.o
	    $(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
