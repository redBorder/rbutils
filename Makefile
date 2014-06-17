
LIBNAME=librbutils
LIBVER=0
LIBVER_FULL=$(LIBVER).0.0

DESTDIR?=/opt/rb

SRCS=	rbstring.c

HDRS=	rbstring.h

OBJS=	$(SRCS:.c=.o)
DEPS=	${OBJS:%.o=%.d}

CFLAGS+=-I/opt/rb/include -L/opt/rb/lib -Wformat -fno-stack-protector
CFLAGS+=-O2 -Wall -Werror -Wfloat-equal -Wformat-security -Wpointer-arith -fPIC -I.
CFLAGS+=-g

# Profiling
#CFLAGS+=-O0
#CFLAGS += -pg
#LDFLAGS += -pg

LDFLAGS+=-g

.PHONY: libs test install clean

all: libs test

libs: $(LIBNAME).so.$(LIBVER) $(LIBNAME).a

%.o: %.c
	$(CC) -MD -MP $(CFLAGS) -c $<

$(LIBNAME).so.$(LIBVER): $(OBJS)
	$(LD) -fPIC -shared -soname,$@ \
		$(LDFLAGS) $(OBJS) -o $@
	ln -fs $(LIBNAME).so.$(LIBVER) $(LIBNAME).so 

$(LIBNAME).a:	$(OBJS)
	$(AR) rcs $@ $(OBJS)

install:
	install -d $(DESTDIR)/include/$(LIBNAME)
	install -d $(DESTDIR)/lib
	install -t $(DESTDIR)/include/$(LIBNAME) $(HDRS)
	install -t $(DESTDIR)/lib $(LIBNAME).so
	install -t $(DESTDIR)/lib $(LIBNAME).so.$(LIBVER)
	install -t $(DESTDIR)/lib $(LIBNAME).a

clean:
	rm -f $(OBJS) $(DEPS) $(LIBNAME).a $(LIBNAME).so $(LIBNAME).so.$(LIBVER)


test:
	make -C tests $@

-include $(DEPS)
