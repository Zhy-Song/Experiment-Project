# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "D:\Program Files (x86)\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files (x86)\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\Experiment-Project\Compilation principle"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\Experiment-Project\Compilation principle\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/wan.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/wan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wan.dir/flags.make

CMakeFiles/wan.dir/exp2/wan.cpp.obj: CMakeFiles/wan.dir/flags.make
CMakeFiles/wan.dir/exp2/wan.cpp.obj: ../exp2/wan.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\Experiment-Project\Compilation principle\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wan.dir/exp2/wan.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\wan.dir\exp2\wan.cpp.obj -c "E:\Experiment-Project\Compilation principle\exp2\wan.cpp"

CMakeFiles/wan.dir/exp2/wan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wan.dir/exp2/wan.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\Experiment-Project\Compilation principle\exp2\wan.cpp" > CMakeFiles\wan.dir\exp2\wan.cpp.i

CMakeFiles/wan.dir/exp2/wan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wan.dir/exp2/wan.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "E:\Experiment-Project\Compilation principle\exp2\wan.cpp" -o CMakeFiles\wan.dir\exp2\wan.cpp.s

# Object files for target wan
wan_OBJECTS = \
"CMakeFiles/wan.dir/exp2/wan.cpp.obj"

# External object files for target wan
wan_EXTERNAL_OBJECTS =

wan.exe: CMakeFiles/wan.dir/exp2/wan.cpp.obj
wan.exe: CMakeFiles/wan.dir/build.make
wan.exe: CMakeFiles/wan.dir/linklibs.rsp
wan.exe: CMakeFiles/wan.dir/objects1.rsp
wan.exe: CMakeFiles/wan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\Experiment-Project\Compilation principle\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wan.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\wan.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wan.dir/build: wan.exe
.PHONY : CMakeFiles/wan.dir/build

CMakeFiles/wan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\wan.dir\cmake_clean.cmake
.PHONY : CMakeFiles/wan.dir/clean

CMakeFiles/wan.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "E:\Experiment-Project\Compilation principle" "E:\Experiment-Project\Compilation principle" "E:\Experiment-Project\Compilation principle\cmake-build-debug" "E:\Experiment-Project\Compilation principle\cmake-build-debug" "E:\Experiment-Project\Compilation principle\cmake-build-debug\CMakeFiles\wan.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/wan.dir/depend

