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
CMAKE_COMMAND = /opt/cmake-3.22.0-rc3-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.22.0-rc3-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules

# Include any dependencies generated for this target.
include rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/compiler_depend.make

# Include the progress variables for this target.
include rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/progress.make

# Include the compile flags for this target's objects.
include rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/flags.make

rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o: rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/flags.make
rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o: rules/cuda/CudaBranchDivergenceRule.cpp
rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o: rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o"
	cd /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o -MF CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o.d -o CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o -c /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda/CudaBranchDivergenceRule.cpp

rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.i"
	cd /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda/CudaBranchDivergenceRule.cpp > CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.i

rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.s"
	cd /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda/CudaBranchDivergenceRule.cpp -o CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.s

# Object files for target CudaBranchDivergenceRule
CudaBranchDivergenceRule_OBJECTS = \
"CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o"

# External object files for target CudaBranchDivergenceRule
CudaBranchDivergenceRule_EXTERNAL_OBJECTS =

rules.dl/libCudaBranchDivergenceRule.so: rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/CudaBranchDivergenceRule.cpp.o
rules.dl/libCudaBranchDivergenceRule.so: rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/build.make
rules.dl/libCudaBranchDivergenceRule.so: lib/libOCLintAbstractRule.a
rules.dl/libCudaBranchDivergenceRule.so: lib/helper/libOCLintHelper.a
rules.dl/libCudaBranchDivergenceRule.so: lib/util/libOCLintUtil.a
rules.dl/libCudaBranchDivergenceRule.so: rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../rules.dl/libCudaBranchDivergenceRule.so"
	cd /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CudaBranchDivergenceRule.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/build: rules.dl/libCudaBranchDivergenceRule.so
.PHONY : rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/build

rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/clean:
	cd /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda && $(CMAKE_COMMAND) -P CMakeFiles/CudaBranchDivergenceRule.dir/cmake_clean.cmake
.PHONY : rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/clean

rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/depend:
	cd /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda /home/tommas/robo-smells/image-files/oclint-repo/oclint-rules/rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : rules/cuda/CMakeFiles/CudaBranchDivergenceRule.dir/depend
