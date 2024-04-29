CFLAGS := -Wall -Wextra -Wno-missing-field-initializers -ggdb -DPLATFORM_DESKTOP -std=c++17 -I/usr/local/include/raylib #-O3
LDFLAGS := -L/usr/local/lib/raylib -l:libraylib.a

raycuboid: src/*.cpp
	g++ $(CFLAGS) -o raycuboid src/*.cpp $(LDFLAGS)

demo: raycuboid
	./raycuboid

clean:
	rm -f raycuboid
