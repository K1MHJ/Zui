.PHONY: all run
CC := clang
CXX := clang++
LD := clang++
AR := ar
RANLIB :=
CFLAGS := -g -O0 -Wall -MP -MMD -DGL_SILENCE_DEPRECATION
CXXFLAGS := $(CFLAGS) -std=c++20 -xc++
SRCDIR := ./src
OBJDIR := ./obj
BINDIR := ./bin
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/ 
INCLUDE := $(INCLUDE) -I./vendor/ -I./vendor/glad/include/
INCLUDE := $(INCLUDE) -I./vendor/spdlog/include/
INCLUDE := $(INCLUDE) -I./vendor/imgui/ -I./vendor/ImGuizmo/
INCLUDE := $(INCLUDE) -I/opt/homebrew/Cellar/glm/1.0.1/include/
INCLUDE := $(INCLUDE) -I./src -I./src/App -I./src/Core -I./src/Debug 
INCLUDE := $(INCLUDE) -I./src/OpenGL -I./src/Renderer -I./src/Utils -I./src/MacOs -I./src/Events -I./src/UI

LIBS := -lm
DEFINES := 
TARGET := ./bin/ZuiApp
FRAMEWORKS  := -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
OPENGLLIB := -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -L/opt/homebrew/Cellar/glfw/3.4/lib
LDFLAGS     := -L/usr/lib -L/usr/local/lib $(OPENGLLIB) -lGLEW.2.2 -lglfw.3.4
PCH_OUT := $(OBJDIR)/pch.gch
PCH_SRC := $(SRCDIR)/pch.cpp
PCH_HEADERS := $(SRCDIR)/pch.h

SRC := Core/Application.cpp App/MyApp.cpp pch.cpp 
SRC := $(SRC) ./Core/Window.cpp ./Core/Log.cpp ./Core/Log.cpp
SRC := $(SRC) ./OpenGL/OpenGLContext.cpp ./OpenGL/OpenGLRendererAPI.cpp
SRC := $(SRC) ./Renderer/GraphicsContext.cpp ./Renderer/RenderCommand.cpp ./Renderer/Renderer.cpp ./Renderer/RendererAPI.cpp
SRC := $(SRC) ./Windows/MacOsWindow.cpp
SRC := $(SRC)

OBJS  := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o)) 
OBJS  := $(OBJS) $(OBJDIR)/gl.o 
DEPS  := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.d))

all: $(TARGET)

run:
	$(TARGET)

$(TARGET): $(OBJS)
	@echo '$$'LDFLAGS is $(LDFLAGS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LDFLAGS) $(FRAMEWORKS)

$(PCH_OUT): $(PCH_SRC) $(PCH_HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -x c++-header

$(OBJDIR)/gl.o: ./vendor/glad/src/gl.c
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

debug : $(TARGET)
	@echo "debug $(TARGET)"
	lldb $(TARGET)

clean :
	rm -rf $(BINDIR) $(OBJDIR)

-include $(DEPS)
