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
include CMakeFiles/a_star.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a_star.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a_star.dir/flags.make

CMakeFiles/a_star.dir/src/a_star.cpp.obj: CMakeFiles/a_star.dir/flags.make
CMakeFiles/a_star.dir/src/a_star.cpp.obj: ../src/a_star.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a_star.dir/src/a_star.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\a_star.dir\src\a_star.cpp.obj -c "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\src\a_star.cpp"

CMakeFiles/a_star.dir/src/a_star.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a_star.dir/src/a_star.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\src\a_star.cpp" > CMakeFiles\a_star.dir\src\a_star.cpp.i

CMakeFiles/a_star.dir/src/a_star.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a_star.dir/src/a_star.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\src\a_star.cpp" -o CMakeFiles\a_star.dir\src\a_star.cpp.s

# Object files for target a_star
a_star_OBJECTS = \
"CMakeFiles/a_star.dir/src/a_star.cpp.obj"

# External object files for target a_star
a_star_EXTERNAL_OBJECTS =

a_star.exe: CMakeFiles/a_star.dir/src/a_star.cpp.obj
a_star.exe: CMakeFiles/a_star.dir/build.make
a_star.exe: CMakeFiles/a_star.dir/linklibs.rsp
a_star.exe: CMakeFiles/a_star.dir/objects1.rsp
a_star.exe: CMakeFiles/a_star.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable a_star.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\a_star.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a_star.dir/build: a_star.exe

.PHONY : CMakeFiles/a_star.dir/build

CMakeFiles/a_star.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\a_star.dir\cmake_clean.cmake
.PHONY : CMakeFiles/a_star.dir/clean

CMakeFiles/a_star.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug" "C:\Users\Bossg\Desktop\AGH Semestr 6\APTO\Sokoban\cmake-build-debug\CMakeFiles\a_star.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/a_star.dir/depend

