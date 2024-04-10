.PHONY: build build-release build-debug clean test run

build: build-windows-debug
	@echo "[CMAKE]: Building done!"

build-windows-release:
	@echo "[CMAKE]: Building in Release mode on Windows..."
	@cmake -B build -S . --preset windows-release
	@cmake --build build

build-windows-debug:
	@echo "[CMAKE]: Building in Debug mode on Windows..."
	@cmake -B build -S . --preset windows-debug
	@cmake --build build

clean:
	@cmake -E remove_directory .cache
	@cmake -E remove_directory build
	@cmake -E remove_directory bin
	@echo "[CMAKE]: Cleaning done!"

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