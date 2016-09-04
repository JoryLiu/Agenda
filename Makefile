CC := g++
FLAGES := -std=c++0x -w -g
IN_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(IN_DIR)


$(BIN_DIR)/Agenda: $(BUILD_DIR)/Agenda.o $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGES) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGES) $(INCLUDE) $^ -c -o $@


clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
