# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = D:\qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\projs\aaaakeshe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\projs\aaaakeshe\build

# Include any dependencies generated for this target.
include CMakeFiles/analyser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/analyser.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/analyser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/analyser.dir/flags.make

CMakeFiles/analyser.dir/examples/analyser.cpp.obj: CMakeFiles/analyser.dir/flags.make
CMakeFiles/analyser.dir/examples/analyser.cpp.obj: CMakeFiles/analyser.dir/includes_CXX.rsp
CMakeFiles/analyser.dir/examples/analyser.cpp.obj: D:/projs/aaaakeshe/examples/analyser.cpp
CMakeFiles/analyser.dir/examples/analyser.cpp.obj: CMakeFiles/analyser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\projs\aaaakeshe\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/analyser.dir/examples/analyser.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/analyser.dir/examples/analyser.cpp.obj -MF CMakeFiles\analyser.dir\examples\analyser.cpp.obj.d -o CMakeFiles\analyser.dir\examples\analyser.cpp.obj -c D:\projs\aaaakeshe\examples\analyser.cpp

CMakeFiles/analyser.dir/examples/analyser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/analyser.dir/examples/analyser.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\projs\aaaakeshe\examples\analyser.cpp > CMakeFiles\analyser.dir\examples\analyser.cpp.i

CMakeFiles/analyser.dir/examples/analyser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/analyser.dir/examples/analyser.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\projs\aaaakeshe\examples\analyser.cpp -o CMakeFiles\analyser.dir\examples\analyser.cpp.s

# Object files for target analyser
analyser_OBJECTS = \
"CMakeFiles/analyser.dir/examples/analyser.cpp.obj"

# External object files for target analyser
analyser_EXTERNAL_OBJECTS =

analyser.exe: CMakeFiles/analyser.dir/examples/analyser.cpp.obj
analyser.exe: CMakeFiles/analyser.dir/build.make
analyser.exe: liblogger.a
analyser.exe: D:/miniconda/Library/lib/fmt.lib
analyser.exe: CMakeFiles/analyser.dir/linkLibs.rsp
analyser.exe: CMakeFiles/analyser.dir/objects1.rsp
analyser.exe: CMakeFiles/analyser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\projs\aaaakeshe\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable analyser.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\analyser.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/analyser.dir/build: analyser.exe
.PHONY : CMakeFiles/analyser.dir/build

CMakeFiles/analyser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\analyser.dir\cmake_clean.cmake
.PHONY : CMakeFiles/analyser.dir/clean

CMakeFiles/analyser.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\projs\aaaakeshe D:\projs\aaaakeshe D:\projs\aaaakeshe\build D:\projs\aaaakeshe\build D:\projs\aaaakeshe\build\CMakeFiles\analyser.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/analyser.dir/depend

