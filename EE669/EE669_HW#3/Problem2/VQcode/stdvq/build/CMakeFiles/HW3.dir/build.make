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
include CMakeFiles/HW3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW3.dir/flags.make

CMakeFiles/HW3.dir/lloyd0.c.o: CMakeFiles/HW3.dir/flags.make
CMakeFiles/HW3.dir/lloyd0.c.o: ../lloyd0.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HW3.dir/lloyd0.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HW3.dir/lloyd0.c.o   -c /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd0.c

CMakeFiles/HW3.dir/lloyd0.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW3.dir/lloyd0.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd0.c > CMakeFiles/HW3.dir/lloyd0.c.i

CMakeFiles/HW3.dir/lloyd0.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW3.dir/lloyd0.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd0.c -o CMakeFiles/HW3.dir/lloyd0.c.s

CMakeFiles/HW3.dir/lloyd0.c.o.requires:

.PHONY : CMakeFiles/HW3.dir/lloyd0.c.o.requires

CMakeFiles/HW3.dir/lloyd0.c.o.provides: CMakeFiles/HW3.dir/lloyd0.c.o.requires
	$(MAKE) -f CMakeFiles/HW3.dir/build.make CMakeFiles/HW3.dir/lloyd0.c.o.provides.build
.PHONY : CMakeFiles/HW3.dir/lloyd0.c.o.provides

CMakeFiles/HW3.dir/lloyd0.c.o.provides.build: CMakeFiles/HW3.dir/lloyd0.c.o


CMakeFiles/HW3.dir/lloyd1.c.o: CMakeFiles/HW3.dir/flags.make
CMakeFiles/HW3.dir/lloyd1.c.o: ../lloyd1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/HW3.dir/lloyd1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HW3.dir/lloyd1.c.o   -c /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd1.c

CMakeFiles/HW3.dir/lloyd1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW3.dir/lloyd1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd1.c > CMakeFiles/HW3.dir/lloyd1.c.i

CMakeFiles/HW3.dir/lloyd1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW3.dir/lloyd1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd1.c -o CMakeFiles/HW3.dir/lloyd1.c.s

CMakeFiles/HW3.dir/lloyd1.c.o.requires:

.PHONY : CMakeFiles/HW3.dir/lloyd1.c.o.requires

CMakeFiles/HW3.dir/lloyd1.c.o.provides: CMakeFiles/HW3.dir/lloyd1.c.o.requires
	$(MAKE) -f CMakeFiles/HW3.dir/build.make CMakeFiles/HW3.dir/lloyd1.c.o.provides.build
.PHONY : CMakeFiles/HW3.dir/lloyd1.c.o.provides

CMakeFiles/HW3.dir/lloyd1.c.o.provides.build: CMakeFiles/HW3.dir/lloyd1.c.o


CMakeFiles/HW3.dir/lloyd2.c.o: CMakeFiles/HW3.dir/flags.make
CMakeFiles/HW3.dir/lloyd2.c.o: ../lloyd2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/HW3.dir/lloyd2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HW3.dir/lloyd2.c.o   -c /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd2.c

CMakeFiles/HW3.dir/lloyd2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW3.dir/lloyd2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd2.c > CMakeFiles/HW3.dir/lloyd2.c.i

CMakeFiles/HW3.dir/lloyd2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW3.dir/lloyd2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/lloyd2.c -o CMakeFiles/HW3.dir/lloyd2.c.s

CMakeFiles/HW3.dir/lloyd2.c.o.requires:

.PHONY : CMakeFiles/HW3.dir/lloyd2.c.o.requires

CMakeFiles/HW3.dir/lloyd2.c.o.provides: CMakeFiles/HW3.dir/lloyd2.c.o.requires
	$(MAKE) -f CMakeFiles/HW3.dir/build.make CMakeFiles/HW3.dir/lloyd2.c.o.provides.build
.PHONY : CMakeFiles/HW3.dir/lloyd2.c.o.provides

CMakeFiles/HW3.dir/lloyd2.c.o.provides.build: CMakeFiles/HW3.dir/lloyd2.c.o


CMakeFiles/HW3.dir/stdvq_util.c.o: CMakeFiles/HW3.dir/flags.make
CMakeFiles/HW3.dir/stdvq_util.c.o: ../stdvq_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/HW3.dir/stdvq_util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HW3.dir/stdvq_util.c.o   -c /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/stdvq_util.c

CMakeFiles/HW3.dir/stdvq_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW3.dir/stdvq_util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/stdvq_util.c > CMakeFiles/HW3.dir/stdvq_util.c.i

CMakeFiles/HW3.dir/stdvq_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW3.dir/stdvq_util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/stdvq_util.c -o CMakeFiles/HW3.dir/stdvq_util.c.s

CMakeFiles/HW3.dir/stdvq_util.c.o.requires:

.PHONY : CMakeFiles/HW3.dir/stdvq_util.c.o.requires

CMakeFiles/HW3.dir/stdvq_util.c.o.provides: CMakeFiles/HW3.dir/stdvq_util.c.o.requires
	$(MAKE) -f CMakeFiles/HW3.dir/build.make CMakeFiles/HW3.dir/stdvq_util.c.o.provides.build
.PHONY : CMakeFiles/HW3.dir/stdvq_util.c.o.provides

CMakeFiles/HW3.dir/stdvq_util.c.o.provides.build: CMakeFiles/HW3.dir/stdvq_util.c.o


# Object files for target HW3
HW3_OBJECTS = \
"CMakeFiles/HW3.dir/lloyd0.c.o" \
"CMakeFiles/HW3.dir/lloyd1.c.o" \
"CMakeFiles/HW3.dir/lloyd2.c.o" \
"CMakeFiles/HW3.dir/stdvq_util.c.o"

# External object files for target HW3
HW3_EXTERNAL_OBJECTS =

../lib/libHW3.so: CMakeFiles/HW3.dir/lloyd0.c.o
../lib/libHW3.so: CMakeFiles/HW3.dir/lloyd1.c.o
../lib/libHW3.so: CMakeFiles/HW3.dir/lloyd2.c.o
../lib/libHW3.so: CMakeFiles/HW3.dir/stdvq_util.c.o
../lib/libHW3.so: CMakeFiles/HW3.dir/build.make
../lib/libHW3.so: CMakeFiles/HW3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C shared library ../lib/libHW3.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HW3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW3.dir/build: ../lib/libHW3.so

.PHONY : CMakeFiles/HW3.dir/build

CMakeFiles/HW3.dir/requires: CMakeFiles/HW3.dir/lloyd0.c.o.requires
CMakeFiles/HW3.dir/requires: CMakeFiles/HW3.dir/lloyd1.c.o.requires
CMakeFiles/HW3.dir/requires: CMakeFiles/HW3.dir/lloyd2.c.o.requires
CMakeFiles/HW3.dir/requires: CMakeFiles/HW3.dir/stdvq_util.c.o.requires

.PHONY : CMakeFiles/HW3.dir/requires

CMakeFiles/HW3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HW3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HW3.dir/clean

CMakeFiles/HW3.dir/depend:
	cd /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build /home/luchengyu/EE669/HW3/EE669_Fall_2022_HW3_Materials/Problem2/VQcode/stdvq/build/CMakeFiles/HW3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW3.dir/depend
