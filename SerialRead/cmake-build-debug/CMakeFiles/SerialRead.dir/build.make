# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\rugge\Documents\development\SerialRead

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SerialRead.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SerialRead.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SerialRead.dir/flags.make

CMakeFiles/SerialRead.dir/main.cpp.obj: CMakeFiles/SerialRead.dir/flags.make
CMakeFiles/SerialRead.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SerialRead.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SerialRead.dir\main.cpp.obj -c C:\Users\rugge\Documents\development\SerialRead\main.cpp

CMakeFiles/SerialRead.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SerialRead.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\rugge\Documents\development\SerialRead\main.cpp > CMakeFiles\SerialRead.dir\main.cpp.i

CMakeFiles/SerialRead.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SerialRead.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\rugge\Documents\development\SerialRead\main.cpp -o CMakeFiles\SerialRead.dir\main.cpp.s

CMakeFiles/SerialRead.dir/SerialPort.cpp.obj: CMakeFiles/SerialRead.dir/flags.make
CMakeFiles/SerialRead.dir/SerialPort.cpp.obj: ../SerialPort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SerialRead.dir/SerialPort.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SerialRead.dir\SerialPort.cpp.obj -c C:\Users\rugge\Documents\development\SerialRead\SerialPort.cpp

CMakeFiles/SerialRead.dir/SerialPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SerialRead.dir/SerialPort.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\rugge\Documents\development\SerialRead\SerialPort.cpp > CMakeFiles\SerialRead.dir\SerialPort.cpp.i

CMakeFiles/SerialRead.dir/SerialPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SerialRead.dir/SerialPort.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\rugge\Documents\development\SerialRead\SerialPort.cpp -o CMakeFiles\SerialRead.dir\SerialPort.cpp.s

# Object files for target SerialRead
SerialRead_OBJECTS = \
"CMakeFiles/SerialRead.dir/main.cpp.obj" \
"CMakeFiles/SerialRead.dir/SerialPort.cpp.obj"

# External object files for target SerialRead
SerialRead_EXTERNAL_OBJECTS =

SerialRead.exe: CMakeFiles/SerialRead.dir/main.cpp.obj
SerialRead.exe: CMakeFiles/SerialRead.dir/SerialPort.cpp.obj
SerialRead.exe: CMakeFiles/SerialRead.dir/build.make
SerialRead.exe: CMakeFiles/SerialRead.dir/linklibs.rsp
SerialRead.exe: CMakeFiles/SerialRead.dir/objects1.rsp
SerialRead.exe: CMakeFiles/SerialRead.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SerialRead.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SerialRead.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SerialRead.dir/build: SerialRead.exe

.PHONY : CMakeFiles/SerialRead.dir/build

CMakeFiles/SerialRead.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SerialRead.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SerialRead.dir/clean

CMakeFiles/SerialRead.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\rugge\Documents\development\SerialRead C:\Users\rugge\Documents\development\SerialRead C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug C:\Users\rugge\Documents\development\SerialRead\cmake-build-debug\CMakeFiles\SerialRead.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SerialRead.dir/depend

