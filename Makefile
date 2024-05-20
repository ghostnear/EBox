.PHONY: all

build-windows: build-windows-debug
	@echo "[CMAKE]: Building done!"

build-windows-release:
	@echo "[CMAKE]: Building in Release mode on Windows..."
	@cmake -B build -S . --preset windows-release
	@cmake --build build

build-windows-debug:
	@echo "[CMAKE]: Building in Debug mode on Windows..."
	@cmake -B build -S . --preset windows-debug
	@cmake --build build

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

build-vita: build-vita-release
	@echo "[CMAKE]: Building done!"

build-vita-release:
	@echo "[CMAKE]: Building in Release mode on Vita..."
	@cmake -B build -S . --preset vita-release
	@cmake --build build

build-vita-debug:
	@echo "[CMAKE]: Building in Debug mode on Vita..."
	@cmake -B build -S . --preset vita-debug
	@cmake --build build

clean:
	@cmake -E remove_directory .cache
	@cmake -E remove_directory build
	@cmake -E remove_directory bin
	@echo "[CMAKE]: Cleaning done!"
	
run:
	@echo "[CMAKE]: Running app..."
	@cd bin && ./EBox
	
run-vita:
	@echo "[CMAKE]: Running app on Vita..."
	@vita3k ./build/EBox.vpk

unix-profile:
	@echo "[CMAKE]: Running gprof..."
	@gprof ./bin/EBox ./bin/gmon.out > ./bin/analysis.txt