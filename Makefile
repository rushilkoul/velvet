BUILD_DIR := build
GENERATOR := Ninja

.PHONY: configure build run docs clean rebuild

configure:
	cmake -S . -B $(BUILD_DIR) -G $(GENERATOR)

build:
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/velvet_app

docs:
	cmake -S . -B $(BUILD_DIR) -G $(GENERATOR) -DVELVET_BUILD_DOCS=ON
	cmake --build $(BUILD_DIR) --target docs

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean configure build
