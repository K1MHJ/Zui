.PHONY: all run
CC := clang
CXX := clang++
LD := clang++
AR := ar
RANLIB :=
CFLAGS := -g -O0 -Wall -MP -MMD -DGL_SILENCE_DEPRECATION
CXXFLAGS := $(CFLAGS) -std=c++20 -xc++ -arch arm64
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

SRC :=
SRC := $(SRC) vendor/stb_image/stb_image.cpp 
SRC := $(SRC) vendor/imgui/imgui.cpp 
SRC := $(SRC) vendor/imgui/imgui_draw.cpp 
SRC := $(SRC) vendor/imgui/imgui_tables.cpp vendor/imgui/imgui_widgets.cpp 
# SRC := $(SRC) vendor/imgui/backends/imgui_impl_glfw.cpp 
# SRC := $(SRC) vendor/imgui/backends/imgui_impl_opengl3.cpp
SRC := $(SRC) vendor/ImGuizmo/ImGuizmo.cpp vendor/ImGuizmo/GraphEditor.cpp vendor/ImGuizmo/ImCurveEdit.cpp vendor/ImGuizmo/ImGradient.cpp vendor/ImGuizmo/ImSequencer.cpp

SRC := $(SRC) App/MyApp.cpp App/MyLayer.cpp
SRC := $(SRC) ./Core/Application.cpp ./Core/Layer.cpp ./Core/LayerStack.cpp ./Core/Log.cpp ./Core/Window.cpp
SRC := $(SRC) ./ImGui/ImGuiBuild.cpp ./ImGui/ImGuiLayer.cpp
SRC := $(SRC) ./MacOs/MacOsWindow.cpp ./MacOs/MacOsInput.cpp ./MacOs/MacOsPlatformUtils.cpp
SRC := $(SRC) ./OpenGL/OpenGLContext.cpp ./OpenGL/OpenGLRendererAPI.cpp
SRC := $(SRC) ./Renderer/GraphicsContext.cpp ./Renderer/RenderCommand.cpp ./Renderer/Renderer.cpp ./Renderer/RendererAPI.cpp
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

$(OBJDIR)/%.o: %.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

debug : $(TARGET)
	@echo "debug $(TARGET)"
	lldb $(TARGET)

clean :
	rm -rf $(BINDIR) $(OBJDIR)

-include $(DEPS)
