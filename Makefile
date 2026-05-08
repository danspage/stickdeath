COMPILER = clang++

SOURCE_LIBS = -Ilib/ -Isrc/ \
    -Ilib/SDL2/include \
    -Ilib/SDL2_image/include

CFILES := $(shell find src -name "*.cpp")

LOCAL_SDL_LIBS = -Llib/SDL2/lib -Llib/SDL2_image/lib -lSDL2_image -lSDL2
LOCAL_SDL_RPATH = -Wl,-rpath,@executable_path/../lib/SDL2/lib \
    -Wl,-rpath,@executable_path/../lib/SDL2_image/lib

OSX_OPT = -std=c++20 -Llib/ \
    -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL \
    $(LOCAL_SDL_LIBS) $(LOCAL_SDL_RPATH)

OSX_OUT = -o "bin/build_osx"

build_osx:
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT)