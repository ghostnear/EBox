.PHONY: build build-release build-debug clean test run

build: build-debug
	@echo "[CMAKE]: Building done!"

build-release:
	@echo "[CMAKE]: Building in Release mode..."
	@cmake -B build -S . -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G "Unix Makefiles"
	@cmake --build build --config Release

build-debug:
	@echo "[CMAKE]: Building in Debug mode..."
	@cmake -B build -S . -DCMAKE_BUILD_TYPE=DEBUG -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G "Unix Makefiles"
	@cmake --build build --config Debug

clean:
	@cmake -E remove_directory .cache
	@cmake -E remove_directory build
	@cmake -E remove_directory bin
	@echo "[CMAKE]: Cleaning done!"

test:
	@echo "[CMAKE]: Running tests..."
	@cd build && ctest

run-debug:
	@echo "[CMAKE]: Running Debug build..."
	@./bin/EBox

run-release:
	@echo "[CMAKE]: Running Release build..."
	@./bin/EBox

run: run-debug

# This fucker is absolute trash.
drmemory:
	@echo "[CMAKE]: Running DrMemory..."
	@drmemory ./bin/EBox.exe --ignore_kernel

# This fucker is amazing.
valgrind:
	@echo "[CMAKE]: Running Valgrind..."
	@valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/EBox