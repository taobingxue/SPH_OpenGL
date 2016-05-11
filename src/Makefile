# $File: Makefile

OBJ_DIR = build
TARGET = OpenGL_SPH

OTHERFLAGS = -pthread -fopenmp
CXXFLAGS = $(DEFINES) -std=c++11 $(OTHERFLAGS)
CXXFLAGS += -lGL -lGLU -lglut
LDFLAGS = -lGL -lGLU -lglut

CC = g++
SHELL = bash
ccSOURCES = $(shell find -name "*.cpp" | sed 's/^\.\///g')
OBJS = $(addprefix $(OBJ_DIR)/,$(ccSOURCES:.cpp=.o))
DEPFILES = $(OBJS:.o=.dep)

.PHONY: all clean

all: $(TARGET)

sinclude $(DEPFILES)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "[cc] $< ..."
	@$(CC) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.dep: %.cpp Makefile
	@mkdir -p $(dir $@)
	@echo "[dep] $< ..."
	@$(CC) $(CXXFLAGS) -MM -MT "$(OBJ_DIR)/$(<:.cc=.o) $(OBJ_DIR)/$(<:.cc=.dep)" "$<"  > "$@"

$(TARGET): $(OBJS)
	@echo "Linking ..."
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "done."

clean:
	@rm -rf $(OBJ_DIR)

