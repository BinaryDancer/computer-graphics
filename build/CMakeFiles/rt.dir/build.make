# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pavelmamaev/GIT/computer-graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pavelmamaev/GIT/computer-graphics/build

# Include any dependencies generated for this target.
include CMakeFiles/rt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rt.dir/flags.make

CMakeFiles/rt.dir/main.cpp.o: CMakeFiles/rt.dir/flags.make
CMakeFiles/rt.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pavelmamaev/GIT/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rt.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rt.dir/main.cpp.o -c /Users/pavelmamaev/GIT/computer-graphics/main.cpp

CMakeFiles/rt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rt.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pavelmamaev/GIT/computer-graphics/main.cpp > CMakeFiles/rt.dir/main.cpp.i

CMakeFiles/rt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rt.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pavelmamaev/GIT/computer-graphics/main.cpp -o CMakeFiles/rt.dir/main.cpp.s

CMakeFiles/rt.dir/Bitmap.cpp.o: CMakeFiles/rt.dir/flags.make
CMakeFiles/rt.dir/Bitmap.cpp.o: ../Bitmap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pavelmamaev/GIT/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/rt.dir/Bitmap.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rt.dir/Bitmap.cpp.o -c /Users/pavelmamaev/GIT/computer-graphics/Bitmap.cpp

CMakeFiles/rt.dir/Bitmap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rt.dir/Bitmap.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pavelmamaev/GIT/computer-graphics/Bitmap.cpp > CMakeFiles/rt.dir/Bitmap.cpp.i

CMakeFiles/rt.dir/Bitmap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rt.dir/Bitmap.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pavelmamaev/GIT/computer-graphics/Bitmap.cpp -o CMakeFiles/rt.dir/Bitmap.cpp.s

CMakeFiles/rt.dir/Scene.cpp.o: CMakeFiles/rt.dir/flags.make
CMakeFiles/rt.dir/Scene.cpp.o: ../Scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pavelmamaev/GIT/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/rt.dir/Scene.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rt.dir/Scene.cpp.o -c /Users/pavelmamaev/GIT/computer-graphics/Scene.cpp

CMakeFiles/rt.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rt.dir/Scene.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pavelmamaev/GIT/computer-graphics/Scene.cpp > CMakeFiles/rt.dir/Scene.cpp.i

CMakeFiles/rt.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rt.dir/Scene.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pavelmamaev/GIT/computer-graphics/Scene.cpp -o CMakeFiles/rt.dir/Scene.cpp.s

# Object files for target rt
rt_OBJECTS = \
"CMakeFiles/rt.dir/main.cpp.o" \
"CMakeFiles/rt.dir/Bitmap.cpp.o" \
"CMakeFiles/rt.dir/Scene.cpp.o"

# External object files for target rt
rt_EXTERNAL_OBJECTS =

rt: CMakeFiles/rt.dir/main.cpp.o
rt: CMakeFiles/rt.dir/Bitmap.cpp.o
rt: CMakeFiles/rt.dir/Scene.cpp.o
rt: CMakeFiles/rt.dir/build.make
rt: CMakeFiles/rt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pavelmamaev/GIT/computer-graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable rt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rt.dir/build: rt

.PHONY : CMakeFiles/rt.dir/build

CMakeFiles/rt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rt.dir/clean

CMakeFiles/rt.dir/depend:
	cd /Users/pavelmamaev/GIT/computer-graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pavelmamaev/GIT/computer-graphics /Users/pavelmamaev/GIT/computer-graphics /Users/pavelmamaev/GIT/computer-graphics/build /Users/pavelmamaev/GIT/computer-graphics/build /Users/pavelmamaev/GIT/computer-graphics/build/CMakeFiles/rt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rt.dir/depend

