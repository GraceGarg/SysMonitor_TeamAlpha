# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vboxuser/SysMonitor_TeamAlpha/server_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/server_cmake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server_cmake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server_cmake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server_cmake.dir/flags.make

CMakeFiles/server_cmake.dir/src/main.cpp.o: CMakeFiles/server_cmake.dir/flags.make
CMakeFiles/server_cmake.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/server_cmake.dir/src/main.cpp.o: CMakeFiles/server_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server_cmake.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_cmake.dir/src/main.cpp.o -MF CMakeFiles/server_cmake.dir/src/main.cpp.o.d -o CMakeFiles/server_cmake.dir/src/main.cpp.o -c /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/main.cpp

CMakeFiles/server_cmake.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_cmake.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/main.cpp > CMakeFiles/server_cmake.dir/src/main.cpp.i

CMakeFiles/server_cmake.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_cmake.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/main.cpp -o CMakeFiles/server_cmake.dir/src/main.cpp.s

CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o: CMakeFiles/server_cmake.dir/flags.make
CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o: ../src/DatabaseConnector.cpp
CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o: CMakeFiles/server_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o -MF CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o.d -o CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o -c /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DatabaseConnector.cpp

CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DatabaseConnector.cpp > CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.i

CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DatabaseConnector.cpp -o CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.s

CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o: CMakeFiles/server_cmake.dir/flags.make
CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o: ../src/DbStructure.cpp
CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o: CMakeFiles/server_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o -MF CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o.d -o CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o -c /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DbStructure.cpp

CMakeFiles/server_cmake.dir/src/DbStructure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_cmake.dir/src/DbStructure.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DbStructure.cpp > CMakeFiles/server_cmake.dir/src/DbStructure.cpp.i

CMakeFiles/server_cmake.dir/src/DbStructure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_cmake.dir/src/DbStructure.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DbStructure.cpp -o CMakeFiles/server_cmake.dir/src/DbStructure.cpp.s

CMakeFiles/server_cmake.dir/src/handleclient.cpp.o: CMakeFiles/server_cmake.dir/flags.make
CMakeFiles/server_cmake.dir/src/handleclient.cpp.o: ../src/handleclient.cpp
CMakeFiles/server_cmake.dir/src/handleclient.cpp.o: CMakeFiles/server_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server_cmake.dir/src/handleclient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_cmake.dir/src/handleclient.cpp.o -MF CMakeFiles/server_cmake.dir/src/handleclient.cpp.o.d -o CMakeFiles/server_cmake.dir/src/handleclient.cpp.o -c /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/handleclient.cpp

CMakeFiles/server_cmake.dir/src/handleclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_cmake.dir/src/handleclient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/handleclient.cpp > CMakeFiles/server_cmake.dir/src/handleclient.cpp.i

CMakeFiles/server_cmake.dir/src/handleclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_cmake.dir/src/handleclient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/handleclient.cpp -o CMakeFiles/server_cmake.dir/src/handleclient.cpp.s

CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o: CMakeFiles/server_cmake.dir/flags.make
CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o: ../src/CSVWriter.cpp
CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o: CMakeFiles/server_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o -MF CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o.d -o CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o -c /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/CSVWriter.cpp

CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/CSVWriter.cpp > CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.i

CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/CSVWriter.cpp -o CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.s

CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o: CMakeFiles/server_cmake.dir/flags.make
CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o: ../src/DatabaseHandler.cpp
CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o: CMakeFiles/server_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o -MF CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o.d -o CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o -c /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DatabaseHandler.cpp

CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DatabaseHandler.cpp > CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.i

CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/src/DatabaseHandler.cpp -o CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.s

# Object files for target server_cmake
server_cmake_OBJECTS = \
"CMakeFiles/server_cmake.dir/src/main.cpp.o" \
"CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o" \
"CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o" \
"CMakeFiles/server_cmake.dir/src/handleclient.cpp.o" \
"CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o" \
"CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o"

# External object files for target server_cmake
server_cmake_EXTERNAL_OBJECTS =

server_cmake: CMakeFiles/server_cmake.dir/src/main.cpp.o
server_cmake: CMakeFiles/server_cmake.dir/src/DatabaseConnector.cpp.o
server_cmake: CMakeFiles/server_cmake.dir/src/DbStructure.cpp.o
server_cmake: CMakeFiles/server_cmake.dir/src/handleclient.cpp.o
server_cmake: CMakeFiles/server_cmake.dir/src/CSVWriter.cpp.o
server_cmake: CMakeFiles/server_cmake.dir/src/DatabaseHandler.cpp.o
server_cmake: CMakeFiles/server_cmake.dir/build.make
server_cmake: CMakeFiles/server_cmake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable server_cmake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_cmake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server_cmake.dir/build: server_cmake
.PHONY : CMakeFiles/server_cmake.dir/build

CMakeFiles/server_cmake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server_cmake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server_cmake.dir/clean

CMakeFiles/server_cmake.dir/depend:
	cd /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vboxuser/SysMonitor_TeamAlpha/server_cmake /home/vboxuser/SysMonitor_TeamAlpha/server_cmake /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build /home/vboxuser/SysMonitor_TeamAlpha/server_cmake/build/CMakeFiles/server_cmake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server_cmake.dir/depend

