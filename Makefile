OBJNAME  := colors
CC :=       gcc
CFLAGS :=   -Wall -Werror -O2
LD :=       gcc
LDFLAGS :=  -lSDL2 -lSDL2_ttf
INC :=      -Iinclude

SRC :=      $(wildcard src/*.c)
OBJS :=     $(subst src,obj,$(subst .c,.o,$(SRC)))
HFILES :=   $(wildcard include/*.h)

.PHONY : all
all : $(OBJNAME)

.PHONY : clean
clean :
	rm -rf obj/
	rm -rf $(OBJNAME)

obj/%.o : src/%.c $(HFILES)
	mkdir -p obj
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJNAME) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)
