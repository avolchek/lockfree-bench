# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/andrew/ClionProjects/lockfree-bench

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/ClionProjects/lockfree-bench

# Include any dependencies generated for this target.
include libcds/CMakeFiles/cds.dir/depend.make

# Include the progress variables for this target.
include libcds/CMakeFiles/cds.dir/progress.make

# Include the compile flags for this target's objects.
include libcds/CMakeFiles/cds.dir/flags.make

libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o: libcds/src/hp_gc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/hp_gc.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/hp_gc.cpp

libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/hp_gc.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/hp_gc.cpp > CMakeFiles/cds.dir/src/hp_gc.cpp.i

libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/hp_gc.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/hp_gc.cpp -o CMakeFiles/cds.dir/src/hp_gc.cpp.s

libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o

libcds/CMakeFiles/cds.dir/src/init.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/init.cpp.o: libcds/src/init.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/init.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/init.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/init.cpp

libcds/CMakeFiles/cds.dir/src/init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/init.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/init.cpp > CMakeFiles/cds.dir/src/init.cpp.i

libcds/CMakeFiles/cds.dir/src/init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/init.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/init.cpp -o CMakeFiles/cds.dir/src/init.cpp.s

libcds/CMakeFiles/cds.dir/src/init.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/init.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/init.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/init.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/init.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/init.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/init.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/init.cpp.o

libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o: libcds/src/dhp_gc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/dhp_gc.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/dhp_gc.cpp

libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/dhp_gc.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/dhp_gc.cpp > CMakeFiles/cds.dir/src/dhp_gc.cpp.i

libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/dhp_gc.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/dhp_gc.cpp -o CMakeFiles/cds.dir/src/dhp_gc.cpp.s

libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o

libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o: libcds/src/urcu_gp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/urcu_gp.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/urcu_gp.cpp

libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/urcu_gp.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/urcu_gp.cpp > CMakeFiles/cds.dir/src/urcu_gp.cpp.i

libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/urcu_gp.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/urcu_gp.cpp -o CMakeFiles/cds.dir/src/urcu_gp.cpp.s

libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o

libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o: libcds/src/urcu_sh.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/urcu_sh.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/urcu_sh.cpp

libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/urcu_sh.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/urcu_sh.cpp > CMakeFiles/cds.dir/src/urcu_sh.cpp.i

libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/urcu_sh.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/urcu_sh.cpp -o CMakeFiles/cds.dir/src/urcu_sh.cpp.s

libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o

libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o: libcds/src/michael_heap.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/michael_heap.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/michael_heap.cpp

libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/michael_heap.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/michael_heap.cpp > CMakeFiles/cds.dir/src/michael_heap.cpp.i

libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/michael_heap.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/michael_heap.cpp -o CMakeFiles/cds.dir/src/michael_heap.cpp.s

libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o

libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o: libcds/src/topology_hpux.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/topology_hpux.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_hpux.cpp

libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/topology_hpux.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_hpux.cpp > CMakeFiles/cds.dir/src/topology_hpux.cpp.i

libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/topology_hpux.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_hpux.cpp -o CMakeFiles/cds.dir/src/topology_hpux.cpp.s

libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o

libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o: libcds/src/topology_linux.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/topology_linux.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_linux.cpp

libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/topology_linux.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_linux.cpp > CMakeFiles/cds.dir/src/topology_linux.cpp.i

libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/topology_linux.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_linux.cpp -o CMakeFiles/cds.dir/src/topology_linux.cpp.s

libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o

libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o: libcds/src/topology_osx.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/topology_osx.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_osx.cpp

libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/topology_osx.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_osx.cpp > CMakeFiles/cds.dir/src/topology_osx.cpp.i

libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/topology_osx.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/topology_osx.cpp -o CMakeFiles/cds.dir/src/topology_osx.cpp.s

libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o

libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o: libcds/CMakeFiles/cds.dir/flags.make
libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o: libcds/src/dllmain.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/ClionProjects/lockfree-bench/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cds.dir/src/dllmain.cpp.o -c /home/andrew/ClionProjects/lockfree-bench/libcds/src/dllmain.cpp

libcds/CMakeFiles/cds.dir/src/dllmain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cds.dir/src/dllmain.cpp.i"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/ClionProjects/lockfree-bench/libcds/src/dllmain.cpp > CMakeFiles/cds.dir/src/dllmain.cpp.i

libcds/CMakeFiles/cds.dir/src/dllmain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cds.dir/src/dllmain.cpp.s"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/ClionProjects/lockfree-bench/libcds/src/dllmain.cpp -o CMakeFiles/cds.dir/src/dllmain.cpp.s

libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.requires:
.PHONY : libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.requires

libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.provides: libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.requires
	$(MAKE) -f libcds/CMakeFiles/cds.dir/build.make libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.provides.build
.PHONY : libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.provides

libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.provides.build: libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o

# Object files for target cds
cds_OBJECTS = \
"CMakeFiles/cds.dir/src/hp_gc.cpp.o" \
"CMakeFiles/cds.dir/src/init.cpp.o" \
"CMakeFiles/cds.dir/src/dhp_gc.cpp.o" \
"CMakeFiles/cds.dir/src/urcu_gp.cpp.o" \
"CMakeFiles/cds.dir/src/urcu_sh.cpp.o" \
"CMakeFiles/cds.dir/src/michael_heap.cpp.o" \
"CMakeFiles/cds.dir/src/topology_hpux.cpp.o" \
"CMakeFiles/cds.dir/src/topology_linux.cpp.o" \
"CMakeFiles/cds.dir/src/topology_osx.cpp.o" \
"CMakeFiles/cds.dir/src/dllmain.cpp.o"

# External object files for target cds
cds_EXTERNAL_OBJECTS =

libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/init.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/build.make
libcds/bin/libcds.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
libcds/bin/libcds.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
libcds/bin/libcds.so: /usr/lib/x86_64-linux-gnu/libpthread.so
libcds/bin/libcds.so: libcds/CMakeFiles/cds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library bin/libcds.so"
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libcds/CMakeFiles/cds.dir/build: libcds/bin/libcds.so
.PHONY : libcds/CMakeFiles/cds.dir/build

libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/hp_gc.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/init.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/dhp_gc.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/urcu_gp.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/urcu_sh.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/michael_heap.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/topology_hpux.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/topology_linux.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/topology_osx.cpp.o.requires
libcds/CMakeFiles/cds.dir/requires: libcds/CMakeFiles/cds.dir/src/dllmain.cpp.o.requires
.PHONY : libcds/CMakeFiles/cds.dir/requires

libcds/CMakeFiles/cds.dir/clean:
	cd /home/andrew/ClionProjects/lockfree-bench/libcds && $(CMAKE_COMMAND) -P CMakeFiles/cds.dir/cmake_clean.cmake
.PHONY : libcds/CMakeFiles/cds.dir/clean

libcds/CMakeFiles/cds.dir/depend:
	cd /home/andrew/ClionProjects/lockfree-bench && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/ClionProjects/lockfree-bench /home/andrew/ClionProjects/lockfree-bench/libcds /home/andrew/ClionProjects/lockfree-bench /home/andrew/ClionProjects/lockfree-bench/libcds /home/andrew/ClionProjects/lockfree-bench/libcds/CMakeFiles/cds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libcds/CMakeFiles/cds.dir/depend

