# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/scar1et/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/scar1et/catkin_ws/build

# Include any dependencies generated for this target.
include sensor/CMakeFiles/sensor.dir/depend.make

# Include the progress variables for this target.
include sensor/CMakeFiles/sensor.dir/progress.make

# Include the compile flags for this target's objects.
include sensor/CMakeFiles/sensor.dir/flags.make

sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.o: sensor/CMakeFiles/sensor.dir/flags.make
sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.o: /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scar1et/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.o"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.o -c /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_client.cpp

sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.i"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_client.cpp > CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.i

sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.s"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_client.cpp -o CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.s

sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.o: sensor/CMakeFiles/sensor.dir/flags.make
sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.o: /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scar1et/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.o"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.o -c /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_server.cpp

sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.i"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_server.cpp > CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.i

sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.s"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scar1et/catkin_ws/src/sensor/src/tcp_server/tcp_server.cpp -o CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.s

sensor/CMakeFiles/sensor.dir/src/tcp_server/client.cpp.o: sensor/CMakeFiles/sensor.dir/flags.make
sensor/CMakeFiles/sensor.dir/src/tcp_server/client.cpp.o: /home/scar1et/catkin_ws/src/sensor/src/tcp_server/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/scar1et/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object sensor/CMakeFiles/sensor.dir/src/tcp_server/client.cpp.o"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sensor.dir/src/tcp_server/client.cpp.o -c /home/scar1et/catkin_ws/src/sensor/src/tcp_server/client.cpp

sensor/CMakeFiles/sensor.dir/src/tcp_server/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sensor.dir/src/tcp_server/client.cpp.i"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/scar1et/catkin_ws/src/sensor/src/tcp_server/client.cpp > CMakeFiles/sensor.dir/src/tcp_server/client.cpp.i

sensor/CMakeFiles/sensor.dir/src/tcp_server/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sensor.dir/src/tcp_server/client.cpp.s"
	cd /home/scar1et/catkin_ws/build/sensor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/scar1et/catkin_ws/src/sensor/src/tcp_server/client.cpp -o CMakeFiles/sensor.dir/src/tcp_server/client.cpp.s

# Object files for target sensor
sensor_OBJECTS = \
"CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.o" \
"CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.o" \
"CMakeFiles/sensor.dir/src/tcp_server/client.cpp.o"

# External object files for target sensor
sensor_EXTERNAL_OBJECTS =

/home/scar1et/catkin_ws/devel/lib/libsensor.so: sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_client.cpp.o
/home/scar1et/catkin_ws/devel/lib/libsensor.so: sensor/CMakeFiles/sensor.dir/src/tcp_server/tcp_server.cpp.o
/home/scar1et/catkin_ws/devel/lib/libsensor.so: sensor/CMakeFiles/sensor.dir/src/tcp_server/client.cpp.o
/home/scar1et/catkin_ws/devel/lib/libsensor.so: sensor/CMakeFiles/sensor.dir/build.make
/home/scar1et/catkin_ws/devel/lib/libsensor.so: sensor/CMakeFiles/sensor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/scar1et/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library /home/scar1et/catkin_ws/devel/lib/libsensor.so"
	cd /home/scar1et/catkin_ws/build/sensor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sensor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sensor/CMakeFiles/sensor.dir/build: /home/scar1et/catkin_ws/devel/lib/libsensor.so

.PHONY : sensor/CMakeFiles/sensor.dir/build

sensor/CMakeFiles/sensor.dir/clean:
	cd /home/scar1et/catkin_ws/build/sensor && $(CMAKE_COMMAND) -P CMakeFiles/sensor.dir/cmake_clean.cmake
.PHONY : sensor/CMakeFiles/sensor.dir/clean

sensor/CMakeFiles/sensor.dir/depend:
	cd /home/scar1et/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/scar1et/catkin_ws/src /home/scar1et/catkin_ws/src/sensor /home/scar1et/catkin_ws/build /home/scar1et/catkin_ws/build/sensor /home/scar1et/catkin_ws/build/sensor/CMakeFiles/sensor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sensor/CMakeFiles/sensor.dir/depend

