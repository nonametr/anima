# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nonametr/projects/anima

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nonametr/projects/anima/build

# Include any dependencies generated for this target.
include CMakeFiles/anima_login.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/anima_login.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/anima_login.dir/flags.make

CMakeFiles/anima_login.dir/main_login.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/main_login.cpp.o: ../main_login.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/main_login.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/main_login.cpp.o -c /home/nonametr/projects/anima/main_login.cpp

CMakeFiles/anima_login.dir/main_login.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/main_login.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/main_login.cpp > CMakeFiles/anima_login.dir/main_login.cpp.i

CMakeFiles/anima_login.dir/main_login.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/main_login.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/main_login.cpp -o CMakeFiles/anima_login.dir/main_login.cpp.s

CMakeFiles/anima_login.dir/main_login.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/main_login.cpp.o.requires

CMakeFiles/anima_login.dir/main_login.cpp.o.provides: CMakeFiles/anima_login.dir/main_login.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/main_login.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/main_login.cpp.o.provides

CMakeFiles/anima_login.dir/main_login.cpp.o.provides.build: CMakeFiles/anima_login.dir/main_login.cpp.o
.PHONY : CMakeFiles/anima_login.dir/main_login.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/common.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/common.cpp.o: ../shared/common.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/common.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/common.cpp.o -c /home/nonametr/projects/anima/shared/common.cpp

CMakeFiles/anima_login.dir/shared/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/common.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/common.cpp > CMakeFiles/anima_login.dir/shared/common.cpp.i

CMakeFiles/anima_login.dir/shared/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/common.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/common.cpp -o CMakeFiles/anima_login.dir/shared/common.cpp.s

CMakeFiles/anima_login.dir/shared/common.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/common.cpp.o.requires

CMakeFiles/anima_login.dir/shared/common.cpp.o.provides: CMakeFiles/anima_login.dir/shared/common.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/common.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/common.cpp.o.provides

CMakeFiles/anima_login.dir/shared/common.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/common.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/common.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/config.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/config.cpp.o: ../shared/config.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/config.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/config.cpp.o -c /home/nonametr/projects/anima/shared/config.cpp

CMakeFiles/anima_login.dir/shared/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/config.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/config.cpp > CMakeFiles/anima_login.dir/shared/config.cpp.i

CMakeFiles/anima_login.dir/shared/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/config.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/config.cpp -o CMakeFiles/anima_login.dir/shared/config.cpp.s

CMakeFiles/anima_login.dir/shared/config.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/config.cpp.o.requires

CMakeFiles/anima_login.dir/shared/config.cpp.o.provides: CMakeFiles/anima_login.dir/shared/config.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/config.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/config.cpp.o.provides

CMakeFiles/anima_login.dir/shared/config.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/config.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/config.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/socket.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/socket.cpp.o: ../shared/socket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/socket.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/socket.cpp.o -c /home/nonametr/projects/anima/shared/socket.cpp

CMakeFiles/anima_login.dir/shared/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/socket.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/socket.cpp > CMakeFiles/anima_login.dir/shared/socket.cpp.i

CMakeFiles/anima_login.dir/shared/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/socket.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/socket.cpp -o CMakeFiles/anima_login.dir/shared/socket.cpp.s

CMakeFiles/anima_login.dir/shared/socket.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/socket.cpp.o.requires

CMakeFiles/anima_login.dir/shared/socket.cpp.o.provides: CMakeFiles/anima_login.dir/shared/socket.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/socket.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/socket.cpp.o.provides

CMakeFiles/anima_login.dir/shared/socket.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/socket.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/socket.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/netcore.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/netcore.cpp.o: ../shared/netcore.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/netcore.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/netcore.cpp.o -c /home/nonametr/projects/anima/shared/netcore.cpp

CMakeFiles/anima_login.dir/shared/netcore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/netcore.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/netcore.cpp > CMakeFiles/anima_login.dir/shared/netcore.cpp.i

CMakeFiles/anima_login.dir/shared/netcore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/netcore.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/netcore.cpp -o CMakeFiles/anima_login.dir/shared/netcore.cpp.s

CMakeFiles/anima_login.dir/shared/netcore.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/netcore.cpp.o.requires

CMakeFiles/anima_login.dir/shared/netcore.cpp.o.provides: CMakeFiles/anima_login.dir/shared/netcore.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/netcore.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/netcore.cpp.o.provides

CMakeFiles/anima_login.dir/shared/netcore.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/netcore.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/netcore.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/thread.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/thread.cpp.o: ../shared/thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/thread.cpp.o -c /home/nonametr/projects/anima/shared/thread.cpp

CMakeFiles/anima_login.dir/shared/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/thread.cpp > CMakeFiles/anima_login.dir/shared/thread.cpp.i

CMakeFiles/anima_login.dir/shared/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/thread.cpp -o CMakeFiles/anima_login.dir/shared/thread.cpp.s

CMakeFiles/anima_login.dir/shared/thread.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/thread.cpp.o.requires

CMakeFiles/anima_login.dir/shared/thread.cpp.o.provides: CMakeFiles/anima_login.dir/shared/thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/thread.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/thread.cpp.o.provides

CMakeFiles/anima_login.dir/shared/thread.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/thread.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/thread.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/threadcore.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/threadcore.cpp.o: ../shared/threadcore.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/threadcore.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/threadcore.cpp.o -c /home/nonametr/projects/anima/shared/threadcore.cpp

CMakeFiles/anima_login.dir/shared/threadcore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/threadcore.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/threadcore.cpp > CMakeFiles/anima_login.dir/shared/threadcore.cpp.i

CMakeFiles/anima_login.dir/shared/threadcore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/threadcore.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/threadcore.cpp -o CMakeFiles/anima_login.dir/shared/threadcore.cpp.s

CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.requires

CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.provides: CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.provides

CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/threadcore.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o: ../shared/periodicthreadcaller.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o -c /home/nonametr/projects/anima/shared/periodicthreadcaller.cpp

CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/periodicthreadcaller.cpp > CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.i

CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/periodicthreadcaller.cpp -o CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.s

CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.requires

CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.provides: CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.provides

CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/json.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/json.cpp.o: ../shared/json.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/json.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/json.cpp.o -c /home/nonametr/projects/anima/shared/json.cpp

CMakeFiles/anima_login.dir/shared/json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/json.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/json.cpp > CMakeFiles/anima_login.dir/shared/json.cpp.i

CMakeFiles/anima_login.dir/shared/json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/json.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/json.cpp -o CMakeFiles/anima_login.dir/shared/json.cpp.s

CMakeFiles/anima_login.dir/shared/json.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/json.cpp.o.requires

CMakeFiles/anima_login.dir/shared/json.cpp.o.provides: CMakeFiles/anima_login.dir/shared/json.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/json.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/json.cpp.o.provides

CMakeFiles/anima_login.dir/shared/json.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/json.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/json.cpp.o.provides.build

CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o: CMakeFiles/anima_login.dir/flags.make
CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o: ../shared/jsonvalue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nonametr/projects/anima/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o -c /home/nonametr/projects/anima/shared/jsonvalue.cpp

CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nonametr/projects/anima/shared/jsonvalue.cpp > CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.i

CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nonametr/projects/anima/shared/jsonvalue.cpp -o CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.s

CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.requires:
.PHONY : CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.requires

CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.provides: CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.requires
	$(MAKE) -f CMakeFiles/anima_login.dir/build.make CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.provides.build
.PHONY : CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.provides

CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.provides.build: CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o
.PHONY : CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.provides.build

# Object files for target anima_login
anima_login_OBJECTS = \
"CMakeFiles/anima_login.dir/main_login.cpp.o" \
"CMakeFiles/anima_login.dir/shared/common.cpp.o" \
"CMakeFiles/anima_login.dir/shared/config.cpp.o" \
"CMakeFiles/anima_login.dir/shared/socket.cpp.o" \
"CMakeFiles/anima_login.dir/shared/netcore.cpp.o" \
"CMakeFiles/anima_login.dir/shared/thread.cpp.o" \
"CMakeFiles/anima_login.dir/shared/threadcore.cpp.o" \
"CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o" \
"CMakeFiles/anima_login.dir/shared/json.cpp.o" \
"CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o"

# External object files for target anima_login
anima_login_EXTERNAL_OBJECTS =

anima_login: CMakeFiles/anima_login.dir/main_login.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/common.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/config.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/socket.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/netcore.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/thread.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/threadcore.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/json.cpp.o
anima_login: CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o
anima_login: CMakeFiles/anima_login.dir/build.make
anima_login: CMakeFiles/anima_login.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable anima_login"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/anima_login.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/anima_login.dir/build: anima_login
.PHONY : CMakeFiles/anima_login.dir/build

CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/main_login.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/common.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/config.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/socket.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/netcore.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/thread.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/threadcore.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/periodicthreadcaller.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/json.cpp.o.requires
CMakeFiles/anima_login.dir/requires: CMakeFiles/anima_login.dir/shared/jsonvalue.cpp.o.requires
.PHONY : CMakeFiles/anima_login.dir/requires

CMakeFiles/anima_login.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/anima_login.dir/cmake_clean.cmake
.PHONY : CMakeFiles/anima_login.dir/clean

CMakeFiles/anima_login.dir/depend:
	cd /home/nonametr/projects/anima/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nonametr/projects/anima /home/nonametr/projects/anima /home/nonametr/projects/anima/build /home/nonametr/projects/anima/build /home/nonametr/projects/anima/build/CMakeFiles/anima_login.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/anima_login.dir/depend

