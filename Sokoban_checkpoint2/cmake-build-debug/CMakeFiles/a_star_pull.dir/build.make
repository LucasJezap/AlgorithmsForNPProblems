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
CMAKE_SOURCE_DIR = "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/a_star_pull.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a_star_pull.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a_star_pull.dir/flags.make

CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.obj: CMakeFiles/a_star_pull.dir/flags.make
CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.obj: ../src/a_star_pull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a_star_pull.dir\src\a_star_pull.cpp.obj -c "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\src\a_star_pull.cpp"

CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\src\a_star_pull.cpp" > CMakeFiles\a_star_pull.dir\src\a_star_pull.cpp.i

CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\src\a_star_pull.cpp" -o CMakeFiles\a_star_pull.dir\src\a_star_pull.cpp.s

# Object files for target a_star_pull
a_star_pull_OBJECTS = \
"CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.obj"

# External object files for target a_star_pull
a_star_pull_EXTERNAL_OBJECTS =

a_star_pull.exe: CMakeFiles/a_star_pull.dir/src/a_star_pull.cpp.obj
a_star_pull.exe: CMakeFiles/a_star_pull.dir/build.make
a_star_pull.exe: CMakeFiles/a_star_pull.dir/linklibs.rsp
a_star_pull.exe: CMakeFiles/a_star_pull.dir/objects1.rsp
a_star_pull.exe: CMakeFiles/a_star_pull.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable a_star_pull.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\a_star_pull.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a_star_pull.dir/build: a_star_pull.exe

.PHONY : CMakeFiles/a_star_pull.dir/build

CMakeFiles/a_star_pull.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\a_star_pull.dir\cmake_clean.cmake
.PHONY : CMakeFiles/a_star_pull.dir/clean

CMakeFiles/a_star_pull.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2" "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2" "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\cmake-build-debug" "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\cmake-build-debug" "C:\Users\yyy\OneDrive\Pulpit\AGH Semestr 6\APTO\Sokoban_checkpoint2\cmake-build-debug\CMakeFiles\a_star_pull.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/a_star_pull.dir/depend
