absdt = libabsdt.a

IDIR = -Iinc
ODIR = obj
SDIR = .
CFLAGS = -Wall -W -ggdb -std=c99 $(IDIR) $(LIBS)

_OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

_dummy := $(shell mkdir -p "$(ODIR)")

$(absdt): $(OBJS)
	$(AR) rcs $@ $^

.PHONY: install
install: $(absdt)
	mkdir -p /usr/lib
	mkdir -p /usr/include/absdt
	cp $(absdt) /usr/lib/$(absdt)
	cp inc/*.h /usr/include/absdt

.PHONY: uninstall
uninstall:
	rm -f /usr/lib/$(absdt)
	rm -f /usr/include/absdt/*.h

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
$(ODIR)/%.o: $(SDIR)/%.c
	gcc -c $(CFLAGS) $*.c -o $(ODIR)/$*.o
	gcc -MM $(CFLAGS) $*.c > $(ODIR)/$*.d