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
include CMakeFiles/demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/examples/test.cpp.obj: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/examples/test.cpp.obj: CMakeFiles/demo.dir/includes_CXX.rsp
CMakeFiles/demo.dir/examples/test.cpp.obj: D:/projs/aaaakeshe/examples/test.cpp
CMakeFiles/demo.dir/examples/test.cpp.obj: CMakeFiles/demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\projs\aaaakeshe\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo.dir/examples/test.cpp.obj"
	C:\ProgramData\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo.dir/examples/test.cpp.obj -MF CMakeFiles\demo.dir\examples\test.cpp.obj.d -o CMakeFiles\demo.dir\examples\test.cpp.obj -c D:\projs\aaaakeshe\examples\test.cpp

CMakeFiles/demo.dir/examples/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/demo.dir/examples/test.cpp.i"
	C:\ProgramData\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\projs\aaaakeshe\examples\test.cpp > CMakeFiles\demo.dir\examples\test.cpp.i

CMakeFiles/demo.dir/examples/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/demo.dir/examples/test.cpp.s"
	C:\ProgramData\mingw64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\projs\aaaakeshe\examples\test.cpp -o CMakeFiles\demo.dir\examples\test.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/examples/test.cpp.obj"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

demo.exe: CMakeFiles/demo.dir/examples/test.cpp.obj
demo.exe: CMakeFiles/demo.dir/build.make
demo.exe: liblogger.a
demo.exe: D:/miniconda/Library/lib/fmt.lib
demo.exe: CMakeFiles/demo.dir/linkLibs.rsp
demo.exe: CMakeFiles/demo.dir/objects1.rsp
demo.exe: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\projs\aaaakeshe\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\demo.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: demo.exe
.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\demo.dir\cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\projs\aaaakeshe D:\projs\aaaakeshe D:\projs\aaaakeshe\build D:\projs\aaaakeshe\build D:\projs\aaaakeshe\build\CMakeFiles\demo.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/demo.dir/depend

