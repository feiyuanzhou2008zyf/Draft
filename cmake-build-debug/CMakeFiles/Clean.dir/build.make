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
CMAKE_COMMAND = /opt/CLion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/CLion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/c4droid/Source/Carbon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/c4droid/Source/Carbon/cmake-build-debug

# Utility rule file for Clean.

# Include the progress variables for this target.
include CMakeFiles/Clean.dir/progress.make

Clean: CMakeFiles/Clean.dir/build.make
	rm -rf /home/c4droid/Source/Carbon/Build
	exit
.PHONY : Clean

# Rule to build all files generated by this target.
CMakeFiles/Clean.dir/build: Clean

.PHONY : CMakeFiles/Clean.dir/build

CMakeFiles/Clean.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Clean.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Clean.dir/clean

CMakeFiles/Clean.dir/depend:
	cd /home/c4droid/Source/Carbon/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c4droid/Source/Carbon /home/c4droid/Source/Carbon /home/c4droid/Source/Carbon/cmake-build-debug /home/c4droid/Source/Carbon/cmake-build-debug /home/c4droid/Source/Carbon/cmake-build-debug/CMakeFiles/Clean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Clean.dir/depend
