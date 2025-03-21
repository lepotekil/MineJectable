# Variables
CC = x86_64-w64-mingw32-g++
CFLAGS = -std=c++17 -static -s -Wl,--exclude-all-symbols
INCLUDES = -Iinclude
LDFLAGS = -L"lib/openjdk-win64/jre/bin/server" -ljvm -lws2_32
SOURCES = $(shell find src -name '*.cpp')
OUTPUT = output/MineJectable.dll
ZIP_PASSWORD = "POTEKIL_STRONG_PASSWD_64"

# Rules
all: $(OUTPUT) zip

$(OUTPUT): $(SOURCES)
	@mkdir -p output
	$(CC) $(CFLAGS) $(INCLUDES) -shared $(SOURCES) -o $(OUTPUT) $(LDFLAGS)

zip: $(OUTPUT)
	zip -r -e -P $(ZIP_PASSWORD) output/MineJectable.zip $(OUTPUT)

clean:
	rm -rf output