BUILD_DIR := build
HOST_BUILD_DIR := $(BUILD_DIR)/host

HOST_CXX ?= clang++
HOST_CXXFLAGS := -std=c++17 -O2 -fPIC

DISCORD_SRC_DIR := discord
DISCORD_SDK_ROOT    := discord/discord_social_sdk
DISCORD_SDK_INC_DIR := $(DISCORD_SDK_ROOT)/include
DISCORD_SDK_LIB_DIR := $(DISCORD_SDK_ROOT)/lib/release
DISCORD_SDK_BIN_DIR := $(DISCORD_SDK_ROOT)/bin/release

ifeq ($(OS),Windows_NT)
    # Windows
    DISCORD_LINK_LIB   := $(DISCORD_SDK_LIB_DIR)/discord_partner_sdk.lib
    DISCORD_SHARED_BIN := $(DISCORD_SDK_BIN_DIR)/discord_partner_sdk.dll
    DISCORD_HOST_LIB   := $(HOST_BUILD_DIR)/discord_integration.dll
    HOST_LDFLAGS       := -shared $(DISCORD_LINK_LIB)
else ifneq ($(shell uname),Darwin)
    # Linux
    DISCORD_LINK_LIB   := $(DISCORD_SDK_LIB_DIR)/libdiscord_partner_sdk.so
    DISCORD_SHARED_BIN := $(DISCORD_SDK_LIB_DIR)/libdiscord_partner_sdk.so
    DISCORD_HOST_LIB   := $(HOST_BUILD_DIR)/libdiscord_integration.so
    HOST_LDFLAGS       := -shared $(DISCORD_LINK_LIB)
else
    # macOS
    DISCORD_LINK_LIB   := $(DISCORD_SDK_LIB_DIR)/libdiscord_partner_sdk.dylib
    DISCORD_SHARED_BIN := $(DISCORD_SDK_LIB_DIR)/libdiscord_partner_sdk.dylib
    DISCORD_HOST_LIB   := $(HOST_BUILD_DIR)/libdiscord_integration.dylib
    HOST_LDFLAGS       := -shared $(DISCORD_LINK_LIB)
endif

# Allow the user to specify the compiler and linker on macOS
# as Apple Clang does not support MIPS architecture
ifeq ($(OS),Windows_NT)
    CC      := clang
    LD      := ld.lld
else ifneq ($(shell uname),Darwin)
    CC      := clang
    LD      := ld.lld
else
    CC      ?= clang
    LD      ?= ld.lld
endif

TARGET  := $(BUILD_DIR)/mod.elf

LDSCRIPT := mod.ld
ARCHFLAGS := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
             -fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset
WARNFLAGS := -Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable \
             -Wno-missing-braces -Wno-unsupported-floating-point-opt -Werror=section
CFLAGS   := $(ARCHFLAGS) $(WARNFLAGS) -D_LANGUAGE_C -nostdinc -ffunction-sections
CPPFLAGS := -DMIPS -DF3DEX_GBI_2 -DF3DEX_GBI_PL -DGBI_DOWHILE -I include -I include/dummy_headers \
            -I mm-decomp/include -I mm-decomp/src -I mm-decomp/extracted/n64-us -idirafter include/libc -idirafter mm-decomp/include/libc
LDFLAGS  := -nostdlib -T $(LDSCRIPT) -Map $(BUILD_DIR)/mod.map --unresolved-symbols=ignore-all --emit-relocs -e 0 --no-nmagic -gc-sections

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
getdirs = $(sort $(dir $(1)))

C_SRCS := $(call rwildcard,src,*.c)
C_OBJS := $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.o))
C_DEPS := $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.d))

DISCORD_SRCS := $(call rwildcard,$(DISCORD_SRC_DIR),*.cpp)
DISCORD_OBJS := $(addprefix $(BUILD_DIR)/, $(DISCORD_SRCS:.cpp=.o))
DISCORD_DEPS := $(addprefix $(BUILD_DIR)/, $(DISCORD_SRCS:.cpp=.d))

ALL_OBJS := $(C_OBJS)
ALL_DEPS := $(C_DEPS)
BUILD_DIRS := $(call getdirs,$(ALL_OBJS) $(DISCORD_OBJS))

all: $(TARGET) $(DISCORD_HOST_LIB)

$(TARGET): $(ALL_OBJS) $(LDSCRIPT) | $(BUILD_DIR)
	$(LD) $(ALL_OBJS) $(LDFLAGS) -o $@


$(BUILD_DIR) $(BUILD_DIRS) $(HOST_BUILD_DIR):
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$@)" mkdir "$(subst /,\,$@)"
else
	mkdir -p $@
endif

$(C_OBJS): $(BUILD_DIR)/%.o : %.c | $(BUILD_DIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

$(DISCORD_OBJS): $(BUILD_DIR)/%.o : %.cpp | $(BUILD_DIRS)
	$(HOST_CXX) $(HOST_CXXFLAGS) -I $(DISCORD_SDK_INC_DIR) $< -MMD -MF $(@:.o=.d) -c -o $@

$(DISCORD_HOST_LIB): $(DISCORD_OBJS) | $(HOST_BUILD_DIR)
	$(HOST_CXX) $(HOST_CXXFLAGS) $(DISCORD_OBJS) $(HOST_LDFLAGS) -o $@

clean:
ifeq ($(OS),Windows_NT)
	if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR)
else
	rm -rf $(BUILD_DIR)
endif

-include $(ALL_DEPS) $(DISCORD_DEPS)

.PHONY: clean all

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true