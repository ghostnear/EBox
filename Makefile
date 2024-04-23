.PHONY: build build-release build-debug clean test run

build-windows: build-windows-debug
	@echo "[CMAKE]: Building done!"

build-unix: build-unix-debug
	@echo "[CMAKE]: Building done!"

build-unix-release:
	@echo "[CMAKE]: Building in Release mode on Unix..."
	@cmake -B build -S . --preset unix-release
	@cmake --build build

build-unix-debug:
	@echo "[CMAKE]: Building in Debug mode on Unix..."
	@cmake -B build -S . --preset unix-debug
	@cmake --build build

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
	
run:
	@echo "[CMAKE]: Running app..."
	@./bin/EBox CHIP8 ./defaults/chip8.cfg

memcheck-windows:
	@echo "[CMAKE]: Running DrMemory..."
	@drmemory ./bin/EBox.exe --ignore_kernel

memcheck-unix:
	@echo "[CMAKE]: Running Valgrind..."
	@valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/EBox

unix-profile:
	@echo "[CMAKE]: Running gprof..."
	@gprof ./bin/EBox ./bin/gmon.out > ./bin/analysis.txt