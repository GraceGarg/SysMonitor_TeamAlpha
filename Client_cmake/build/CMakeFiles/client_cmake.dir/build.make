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
CMAKE_SOURCE_DIR = /home/harshit/Client_cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/harshit/Client_cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/client_cmake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client_cmake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client_cmake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client_cmake.dir/flags.make

CMakeFiles/client_cmake.dir/src/main.cpp.o: CMakeFiles/client_cmake.dir/flags.make
CMakeFiles/client_cmake.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/client_cmake.dir/src/main.cpp.o: CMakeFiles/client_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harshit/Client_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client_cmake.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_cmake.dir/src/main.cpp.o -MF CMakeFiles/client_cmake.dir/src/main.cpp.o.d -o CMakeFiles/client_cmake.dir/src/main.cpp.o -c /home/harshit/Client_cmake/src/main.cpp

CMakeFiles/client_cmake.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_cmake.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harshit/Client_cmake/src/main.cpp > CMakeFiles/client_cmake.dir/src/main.cpp.i

CMakeFiles/client_cmake.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_cmake.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harshit/Client_cmake/src/main.cpp -o CMakeFiles/client_cmake.dir/src/main.cpp.s

CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o: CMakeFiles/client_cmake.dir/flags.make
CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o: ../src/socketHandler.cpp
CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o: CMakeFiles/client_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harshit/Client_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o -MF CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o.d -o CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o -c /home/harshit/Client_cmake/src/socketHandler.cpp

CMakeFiles/client_cmake.dir/src/socketHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_cmake.dir/src/socketHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harshit/Client_cmake/src/socketHandler.cpp > CMakeFiles/client_cmake.dir/src/socketHandler.cpp.i

CMakeFiles/client_cmake.dir/src/socketHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_cmake.dir/src/socketHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harshit/Client_cmake/src/socketHandler.cpp -o CMakeFiles/client_cmake.dir/src/socketHandler.cpp.s

CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o: CMakeFiles/client_cmake.dir/flags.make
CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o: ../src/dataHandler.cpp
CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o: CMakeFiles/client_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harshit/Client_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o -MF CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o.d -o CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o -c /home/harshit/Client_cmake/src/dataHandler.cpp

CMakeFiles/client_cmake.dir/src/dataHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_cmake.dir/src/dataHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harshit/Client_cmake/src/dataHandler.cpp > CMakeFiles/client_cmake.dir/src/dataHandler.cpp.i

CMakeFiles/client_cmake.dir/src/dataHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_cmake.dir/src/dataHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harshit/Client_cmake/src/dataHandler.cpp -o CMakeFiles/client_cmake.dir/src/dataHandler.cpp.s

CMakeFiles/client_cmake.dir/src/Logger.cpp.o: CMakeFiles/client_cmake.dir/flags.make
CMakeFiles/client_cmake.dir/src/Logger.cpp.o: ../src/Logger.cpp
CMakeFiles/client_cmake.dir/src/Logger.cpp.o: CMakeFiles/client_cmake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/harshit/Client_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client_cmake.dir/src/Logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client_cmake.dir/src/Logger.cpp.o -MF CMakeFiles/client_cmake.dir/src/Logger.cpp.o.d -o CMakeFiles/client_cmake.dir/src/Logger.cpp.o -c /home/harshit/Client_cmake/src/Logger.cpp

CMakeFiles/client_cmake.dir/src/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client_cmake.dir/src/Logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/harshit/Client_cmake/src/Logger.cpp > CMakeFiles/client_cmake.dir/src/Logger.cpp.i

CMakeFiles/client_cmake.dir/src/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client_cmake.dir/src/Logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/harshit/Client_cmake/src/Logger.cpp -o CMakeFiles/client_cmake.dir/src/Logger.cpp.s

# Object files for target client_cmake
client_cmake_OBJECTS = \
"CMakeFiles/client_cmake.dir/src/main.cpp.o" \
"CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o" \
"CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o" \
"CMakeFiles/client_cmake.dir/src/Logger.cpp.o"

# External object files for target client_cmake
client_cmake_EXTERNAL_OBJECTS =

client_cmake: CMakeFiles/client_cmake.dir/src/main.cpp.o
client_cmake: CMakeFiles/client_cmake.dir/src/socketHandler.cpp.o
client_cmake: CMakeFiles/client_cmake.dir/src/dataHandler.cpp.o
client_cmake: CMakeFiles/client_cmake.dir/src/Logger.cpp.o
client_cmake: CMakeFiles/client_cmake.dir/build.make
client_cmake: CMakeFiles/client_cmake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/harshit/Client_cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable client_cmake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_cmake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client_cmake.dir/build: client_cmake
.PHONY : CMakeFiles/client_cmake.dir/build

CMakeFiles/client_cmake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_cmake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_cmake.dir/clean

CMakeFiles/client_cmake.dir/depend:
	cd /home/harshit/Client_cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/harshit/Client_cmake /home/harshit/Client_cmake /home/harshit/Client_cmake/build /home/harshit/Client_cmake/build /home/harshit/Client_cmake/build/CMakeFiles/client_cmake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client_cmake.dir/depend

