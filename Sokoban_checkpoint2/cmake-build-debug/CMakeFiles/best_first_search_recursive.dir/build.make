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
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/best_first_search_recursive.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/best_first_search_recursive.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/best_first_search_recursive.dir/flags.make

CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.obj: CMakeFiles/best_first_search_recursive.dir/flags.make
CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.obj: ../best_first_search_recursive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\best_first_search_recursive.dir\best_first_search_recursive.cpp.obj -c C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\best_first_search_recursive.cpp

CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\best_first_search_recursive.cpp > CMakeFiles\best_first_search_recursive.dir\best_first_search_recursive.cpp.i

CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\best_first_search_recursive.cpp -o CMakeFiles\best_first_search_recursive.dir\best_first_search_recursive.cpp.s

# Object files for target best_first_search_recursive
best_first_search_recursive_OBJECTS = \
"CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.obj"

# External object files for target best_first_search_recursive
best_first_search_recursive_EXTERNAL_OBJECTS =

best_first_search_recursive.exe: CMakeFiles/best_first_search_recursive.dir/best_first_search_recursive.cpp.obj
best_first_search_recursive.exe: CMakeFiles/best_first_search_recursive.dir/build.make
best_first_search_recursive.exe: CMakeFiles/best_first_search_recursive.dir/linklibs.rsp
best_first_search_recursive.exe: CMakeFiles/best_first_search_recursive.dir/objects1.rsp
best_first_search_recursive.exe: CMakeFiles/best_first_search_recursive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable best_first_search_recursive.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\best_first_search_recursive.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/best_first_search_recursive.dir/build: best_first_search_recursive.exe

.PHONY : CMakeFiles/best_first_search_recursive.dir/build

CMakeFiles/best_first_search_recursive.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\best_first_search_recursive.dir\cmake_clean.cmake
.PHONY : CMakeFiles/best_first_search_recursive.dir/clean

CMakeFiles/best_first_search_recursive.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2 C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2 C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\cmake-build-debug C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\cmake-build-debug C:\Users\yyy\OneDrive\Pulpit\AGHSemestr6\APTO\Sokoban_checkpoint2\cmake-build-debug\CMakeFiles\best_first_search_recursive.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/best_first_search_recursive.dir/depend

