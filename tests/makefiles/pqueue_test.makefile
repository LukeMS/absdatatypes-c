#based on http://scottmcpeak.com/autodepend/autodepend.html
#if depencies are renamed a make clean will be required

_MAKEFILE_ABS = $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
_TARGET := $(basename $(notdir $(realpath $(lastword $(MAKEFILE_LIST)))))
_CWD = $(_MAKEFILE_ABS)..
.DEFAULT_GOAL = run
$(info $(_TARGET) makefile=$(_MAKEFILE_ABS))

BDIR = bin
ODIR = obj
IDIR = .
SDIR = .
$(info BDIR=$(BDIR))
$(info ODIR=$(ODIR))

INC = -I$(IDIR) -I/msys32/mingw32/include -I$(_CWD)/../inc
LIB = -L$(_CWD)/..

LIB_DEPS = (_CWD)/../libabsdatatypes.a
LIBS = -labsdatatypes
_OBJS := $(_TARGET).o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

#-pedantic
CFLAGS = -Wall -W -ggdb -std=c99 $(INC) $(LIB) $(LIBS)

mingw32:
	set PATH=\msys32\mingw32\bin;\msys32\mingw32\i686-w64-mingw32\bin;\msys32\usr\bin;%PATH%

# link
# gcc -v for verbose
all: mingw32 $(LIB_DEPS) $(OBJS)
	@IF NOT EXIST "$(BDIR)" (mkdir $(BDIR))
	gcc $(OBJS) $(LIB) $(LIBS) -o $(BDIR)/$(_TARGET)

(_CWD)/../libabsdatatypes.a:
	mingw32-make -C $(_CWD)/.. --file=$(_CWD)/../makefiles/absdatatypes.makefile

#start cmd /K "$(_MAKEFILE_DIR)../$(BDIR)/$(_TARGET).exe"
#./$(BDIR)/$(_TARGET).exe
run: all
	$(BDIR)/$(_TARGET).exe

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
$(ODIR)/%.o: $(SDIR)/%.c
	@IF NOT EXIST "$(ODIR)" (mkdir $(ODIR))
	gcc -c $(CFLAGS) $*.c -o $(ODIR)/$*.o
	gcc -MM $(CFLAGS) $*.c > $(ODIR)/$*.d

# remove compilation products
clean:
	IF EXIST "$(BDIR)\$(_TARGET).exe" (del $(BDIR)\$(_TARGET).exe)
	IF EXIST "$(ODIR)\*.o" (del $(ODIR)\*.o)
	IF EXIST "$(ODIR)\*.d" (del $(ODIR)\*.d)
