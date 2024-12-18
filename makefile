# Compilador e flags
CXX = g++
CXXFLAGS = -Iincludes -lsfml-graphics -lsfml-window -lsfml-system -g

# Caminhos
SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj

# Arquivos
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.h)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
OBJS_MAIN = $(patsubst %.cpp, $(OBJ_DIR)/%.o, main.cpp) # Para main.cpp
TARGET = game

# Regras principais
all: $(TARGET)

$(TARGET): $(OBJS) $(OBJ_DIR)/main.o
	$(CXX) $(OBJS) $(OBJ_DIR)/main.o -o $@ $(CXXFLAGS)

# Compilar cada .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR) # Garante que o diretório obj exista
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compilar o main.cpp
$(OBJ_DIR)/main.o: main.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR) # Garante que o diretório obj exista
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run:
	./$(TARGET)
