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
CMAKE_SOURCE_DIR = /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build

# Utility rule file for clean_test_results_serial.

# Include the progress variables for this target.
include tests/CMakeFiles/clean_test_results_serial.dir/progress.make

tests/CMakeFiles/clean_test_results_serial:
	cd /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build/tests && /usr/bin/python2 /opt/ros/melodic/share/catkin/cmake/test/remove_test_results.py /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build/test_results/serial

clean_test_results_serial: tests/CMakeFiles/clean_test_results_serial
clean_test_results_serial: tests/CMakeFiles/clean_test_results_serial.dir/build.make

.PHONY : clean_test_results_serial

# Rule to build all files generated by this target.
tests/CMakeFiles/clean_test_results_serial.dir/build: clean_test_results_serial

.PHONY : tests/CMakeFiles/clean_test_results_serial.dir/build

tests/CMakeFiles/clean_test_results_serial.dir/clean:
	cd /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/clean_test_results_serial.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/clean_test_results_serial.dir/clean

tests/CMakeFiles/clean_test_results_serial.dir/depend:
	cd /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/tests /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build/tests /home/skloe/Desktop/wjwwood-serial-1.2.1-32-g683e12d/wjwwood-serial-683e12d/build/tests/CMakeFiles/clean_test_results_serial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/clean_test_results_serial.dir/depend

