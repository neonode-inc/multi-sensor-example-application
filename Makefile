#CC = clang
CC = gcc

# Remove the hash before the architecture you are building on.
# Other ARM architectures can try using the ARMv6+VFPv2 setting.

#ARCHITECTURE=x86-64
ARCHITECTURE=ARMv6+VFPv2

SOURCEDIR = Source
INCLUDEDIR = Include
OBJECTDIR = Object
DEPENDENCYDIR = Dependency
ZFORCESDKDIR = zForceSDK

vpath %.c $(SOURCEDIR)
vpath %.h $(INCLUDEDIR)
vpath %.d $(DEPENDENCYDIR)

CFLAGS = -Os -Wall -Wextra -std=c99 -D_DEFAULT_SOURCE -Wstrict-prototypes -Wmissing-prototypes -fms-extensions 
ifeq ($(CC),clang)
	CFLAGS += -Wno-microsoft-anon-tag
endif
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPENDENCYDIR)/$*.d

EXE = app
SRCS = Main.c ErrorString.c DumpMessage.c Merger.c Utility.c
INCLUDES = -I$(INCLUDEDIR) -I$(ZFORCESDKDIR)
LIBS = -L./zForceSDK/Linux/$(ARCHITECTURE) -lzForce -pthread -ludev -Wl,-rpath='$$ORIGIN/zForceSDK/Linux/$(ARCHITECTURE)'
OBJS = $(patsubst %.c,$(OBJECTDIR)/%.o,$(SRCS))
DEPS = $(patsubst %.c,$(DEPENDENCYDIR)/%.d,$(SRCS))

$(OBJECTDIR)/%.o: %.c
$(OBJECTDIR)/%.o: %.c $(DEPENDENCYDIR)/%.d
	$(CC) $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

.PHONY: all default clean depend directories

default: $(EXE)

$(EXE): directories $(OBJS)
	$(CC) -o $@ $(INCLUDES) $(OBJS) $(LIBS) -lm

clean:
	@rm -rf $(DEPS) $(OBJS) $(EXE) $(DEPENDENCYDIR) $(OBJECTDIR)

directories: $(DEPENDENCYDIR) $(OBJECTDIR)

$(DEPENDENCYDIR):
	-@mkdir -p $(DEPENDENCYDIR)

$(OBJECTDIR):
	-@mkdir -p $(OBJECTDIR)

$(DEPENDENCYDIR)/%.d: ;
.PRECIOUS: $(DEPENDENCYDIR)/%.d

-include $(DEPS)

