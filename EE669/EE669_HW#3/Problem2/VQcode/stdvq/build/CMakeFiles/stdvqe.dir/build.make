# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build

# Include any dependencies generated for this target.
include CMakeFiles/stdvqe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stdvqe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stdvqe.dir/flags.make

CMakeFiles/stdvqe.dir/stdvqe.c.o: CMakeFiles/stdvqe.dir/flags.make
CMakeFiles/stdvqe.dir/stdvqe.c.o: ../stdvqe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/stdvqe.dir/stdvqe.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/stdvqe.dir/stdvqe.c.o   -c /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/stdvqe.c

CMakeFiles/stdvqe.dir/stdvqe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/stdvqe.dir/stdvqe.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/stdvqe.c > CMakeFiles/stdvqe.dir/stdvqe.c.i

CMakeFiles/stdvqe.dir/stdvqe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/stdvqe.dir/stdvqe.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/stdvqe.c -o CMakeFiles/stdvqe.dir/stdvqe.c.s

CMakeFiles/stdvqe.dir/stdvqe.c.o.requires:

.PHONY : CMakeFiles/stdvqe.dir/stdvqe.c.o.requires

CMakeFiles/stdvqe.dir/stdvqe.c.o.provides: CMakeFiles/stdvqe.dir/stdvqe.c.o.requires
	$(MAKE) -f CMakeFiles/stdvqe.dir/build.make CMakeFiles/stdvqe.dir/stdvqe.c.o.provides.build
.PHONY : CMakeFiles/stdvqe.dir/stdvqe.c.o.provides

CMakeFiles/stdvqe.dir/stdvqe.c.o.provides.build: CMakeFiles/stdvqe.dir/stdvqe.c.o


# Object files for target stdvqe
stdvqe_OBJECTS = \
"CMakeFiles/stdvqe.dir/stdvqe.c.o"

# External object files for target stdvqe
stdvqe_EXTERNAL_OBJECTS =

../stdvqe: CMakeFiles/stdvqe.dir/stdvqe.c.o
../stdvqe: CMakeFiles/stdvqe.dir/build.make
../stdvqe: ../lib/libHW3.so
../stdvqe: CMakeFiles/stdvqe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../stdvqe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stdvqe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stdvqe.dir/build: ../stdvqe

.PHONY : CMakeFiles/stdvqe.dir/build

CMakeFiles/stdvqe.dir/requires: CMakeFiles/stdvqe.dir/stdvqe.c.o.requires

.PHONY : CMakeFiles/stdvqe.dir/requires

CMakeFiles/stdvqe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stdvqe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stdvqe.dir/clean

CMakeFiles/stdvqe.dir/depend:
	cd /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles/stdvqe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stdvqe.dir/depend

