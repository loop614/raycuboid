CFLAGS := -Wall -Wextra -Wno-missing-field-initializers -ggdb -DPLATFORM_DESKTOP -std=c++17 -I/usr/local/include/raylib #-O3
LDFLAGS := -L/usr/local/lib/raylib -l:libraylib.a

gamehtml:
	emcc -Os -Wall -o docs/index.html src/*.cpp -I/usr/local/include/raylib/webassembly -L/usr/local/lib/raylib/webassembly -l:libraylib.a -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB

raycuboid: src/*.cpp
	g++ $(CFLAGS) -o raycuboid src/*.cpp $(LDFLAGS)

demo: raycuboid
	./raycuboid

clean:
	rm -f raycuboid
	rm -f docs/*
