# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
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
CMAKE_SOURCE_DIR = "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/greedy_best_pull.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/greedy_best_pull.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/greedy_best_pull.dir/flags.make

CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.obj: CMakeFiles/greedy_best_pull.dir/flags.make
CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.obj: ../src/greedy_best_first_pull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\greedy_best_pull.dir\src\greedy_best_first_pull.cpp.obj -c "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\src\greedy_best_first_pull.cpp"

CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\src\greedy_best_first_pull.cpp" > CMakeFiles\greedy_best_pull.dir\src\greedy_best_first_pull.cpp.i

CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\src\greedy_best_first_pull.cpp" -o CMakeFiles\greedy_best_pull.dir\src\greedy_best_first_pull.cpp.s

# Object files for target greedy_best_pull
greedy_best_pull_OBJECTS = \
"CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.obj"

# External object files for target greedy_best_pull
greedy_best_pull_EXTERNAL_OBJECTS =

greedy_best_pull.exe: CMakeFiles/greedy_best_pull.dir/src/greedy_best_first_pull.cpp.obj
greedy_best_pull.exe: CMakeFiles/greedy_best_pull.dir/build.make
greedy_best_pull.exe: CMakeFiles/greedy_best_pull.dir/linklibs.rsp
greedy_best_pull.exe: CMakeFiles/greedy_best_pull.dir/objects1.rsp
greedy_best_pull.exe: CMakeFiles/greedy_best_pull.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable greedy_best_pull.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\greedy_best_pull.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/greedy_best_pull.dir/build: greedy_best_pull.exe

.PHONY : CMakeFiles/greedy_best_pull.dir/build

CMakeFiles/greedy_best_pull.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\greedy_best_pull.dir\cmake_clean.cmake
.PHONY : CMakeFiles/greedy_best_pull.dir/clean

CMakeFiles/greedy_best_pull.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug\CMakeFiles\greedy_best_pull.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/greedy_best_pull.dir/depend

