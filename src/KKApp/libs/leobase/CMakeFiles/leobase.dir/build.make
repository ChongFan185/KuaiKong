# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/cmake

# The command to remove a file.
RM = /opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leoshih/workdir/working/leobase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leoshih/workdir/working/tdpano/libs/leobase

# Include any dependencies generated for this target.
include CMakeFiles/leobase.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/leobase.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/leobase.dir/flags.make

CMakeFiles/leobase.dir/Matrices.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/Matrices.cpp.o: /home/leoshih/workdir/working/leobase/Matrices.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/leobase.dir/Matrices.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/Matrices.cpp.o -c /home/leoshih/workdir/working/leobase/Matrices.cpp

CMakeFiles/leobase.dir/Matrices.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/Matrices.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/Matrices.cpp > CMakeFiles/leobase.dir/Matrices.cpp.i

CMakeFiles/leobase.dir/Matrices.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/Matrices.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/Matrices.cpp -o CMakeFiles/leobase.dir/Matrices.cpp.s

CMakeFiles/leobase.dir/gleo.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/gleo.cpp.o: /home/leoshih/workdir/working/leobase/gleo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/leobase.dir/gleo.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/gleo.cpp.o -c /home/leoshih/workdir/working/leobase/gleo.cpp

CMakeFiles/leobase.dir/gleo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/gleo.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/gleo.cpp > CMakeFiles/leobase.dir/gleo.cpp.i

CMakeFiles/leobase.dir/gleo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/gleo.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/gleo.cpp -o CMakeFiles/leobase.dir/gleo.cpp.s

CMakeFiles/leobase.dir/gleocamera.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/gleocamera.cpp.o: /home/leoshih/workdir/working/leobase/gleocamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/leobase.dir/gleocamera.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/gleocamera.cpp.o -c /home/leoshih/workdir/working/leobase/gleocamera.cpp

CMakeFiles/leobase.dir/gleocamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/gleocamera.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/gleocamera.cpp > CMakeFiles/leobase.dir/gleocamera.cpp.i

CMakeFiles/leobase.dir/gleocamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/gleocamera.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/gleocamera.cpp -o CMakeFiles/leobase.dir/gleocamera.cpp.s

CMakeFiles/leobase.dir/gleoshader.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/gleoshader.cpp.o: /home/leoshih/workdir/working/leobase/gleoshader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/leobase.dir/gleoshader.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/gleoshader.cpp.o -c /home/leoshih/workdir/working/leobase/gleoshader.cpp

CMakeFiles/leobase.dir/gleoshader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/gleoshader.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/gleoshader.cpp > CMakeFiles/leobase.dir/gleoshader.cpp.i

CMakeFiles/leobase.dir/gleoshader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/gleoshader.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/gleoshader.cpp -o CMakeFiles/leobase.dir/gleoshader.cpp.s

CMakeFiles/leobase.dir/gleu.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/gleu.cpp.o: /home/leoshih/workdir/working/leobase/gleu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/leobase.dir/gleu.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/gleu.cpp.o -c /home/leoshih/workdir/working/leobase/gleu.cpp

CMakeFiles/leobase.dir/gleu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/gleu.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/gleu.cpp > CMakeFiles/leobase.dir/gleu.cpp.i

CMakeFiles/leobase.dir/gleu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/gleu.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/gleu.cpp -o CMakeFiles/leobase.dir/gleu.cpp.s

CMakeFiles/leobase.dir/imgbarrel.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/imgbarrel.cpp.o: /home/leoshih/workdir/working/leobase/imgbarrel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/leobase.dir/imgbarrel.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/imgbarrel.cpp.o -c /home/leoshih/workdir/working/leobase/imgbarrel.cpp

CMakeFiles/leobase.dir/imgbarrel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/imgbarrel.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/imgbarrel.cpp > CMakeFiles/leobase.dir/imgbarrel.cpp.i

CMakeFiles/leobase.dir/imgbarrel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/imgbarrel.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/imgbarrel.cpp -o CMakeFiles/leobase.dir/imgbarrel.cpp.s

CMakeFiles/leobase.dir/imgbmp.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/imgbmp.cpp.o: /home/leoshih/workdir/working/leobase/imgbmp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/leobase.dir/imgbmp.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/imgbmp.cpp.o -c /home/leoshih/workdir/working/leobase/imgbmp.cpp

CMakeFiles/leobase.dir/imgbmp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/imgbmp.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/imgbmp.cpp > CMakeFiles/leobase.dir/imgbmp.cpp.i

CMakeFiles/leobase.dir/imgbmp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/imgbmp.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/imgbmp.cpp -o CMakeFiles/leobase.dir/imgbmp.cpp.s

CMakeFiles/leobase.dir/imgconvert.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/imgconvert.cpp.o: /home/leoshih/workdir/working/leobase/imgconvert.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/leobase.dir/imgconvert.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/imgconvert.cpp.o -c /home/leoshih/workdir/working/leobase/imgconvert.cpp

CMakeFiles/leobase.dir/imgconvert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/imgconvert.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/imgconvert.cpp > CMakeFiles/leobase.dir/imgconvert.cpp.i

CMakeFiles/leobase.dir/imgconvert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/imgconvert.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/imgconvert.cpp -o CMakeFiles/leobase.dir/imgconvert.cpp.s

CMakeFiles/leobase.dir/mdobject.cpp.o: CMakeFiles/leobase.dir/flags.make
CMakeFiles/leobase.dir/mdobject.cpp.o: /home/leoshih/workdir/working/leobase/mdobject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/leobase.dir/mdobject.cpp.o"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/leobase.dir/mdobject.cpp.o -c /home/leoshih/workdir/working/leobase/mdobject.cpp

CMakeFiles/leobase.dir/mdobject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/leobase.dir/mdobject.cpp.i"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoshih/workdir/working/leobase/mdobject.cpp > CMakeFiles/leobase.dir/mdobject.cpp.i

CMakeFiles/leobase.dir/mdobject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/leobase.dir/mdobject.cpp.s"
	/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++   -mcpu=cortex-a35+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux --sysroot=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoshih/workdir/working/leobase/mdobject.cpp -o CMakeFiles/leobase.dir/mdobject.cpp.s

# Object files for target leobase
leobase_OBJECTS = \
"CMakeFiles/leobase.dir/Matrices.cpp.o" \
"CMakeFiles/leobase.dir/gleo.cpp.o" \
"CMakeFiles/leobase.dir/gleocamera.cpp.o" \
"CMakeFiles/leobase.dir/gleoshader.cpp.o" \
"CMakeFiles/leobase.dir/gleu.cpp.o" \
"CMakeFiles/leobase.dir/imgbarrel.cpp.o" \
"CMakeFiles/leobase.dir/imgbmp.cpp.o" \
"CMakeFiles/leobase.dir/imgconvert.cpp.o" \
"CMakeFiles/leobase.dir/mdobject.cpp.o"

# External object files for target leobase
leobase_EXTERNAL_OBJECTS =

libleobase.a: CMakeFiles/leobase.dir/Matrices.cpp.o
libleobase.a: CMakeFiles/leobase.dir/gleo.cpp.o
libleobase.a: CMakeFiles/leobase.dir/gleocamera.cpp.o
libleobase.a: CMakeFiles/leobase.dir/gleoshader.cpp.o
libleobase.a: CMakeFiles/leobase.dir/gleu.cpp.o
libleobase.a: CMakeFiles/leobase.dir/imgbarrel.cpp.o
libleobase.a: CMakeFiles/leobase.dir/imgbmp.cpp.o
libleobase.a: CMakeFiles/leobase.dir/imgconvert.cpp.o
libleobase.a: CMakeFiles/leobase.dir/mdobject.cpp.o
libleobase.a: CMakeFiles/leobase.dir/build.make
libleobase.a: CMakeFiles/leobase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libleobase.a"
	$(CMAKE_COMMAND) -P CMakeFiles/leobase.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/leobase.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/leobase.dir/build: libleobase.a

.PHONY : CMakeFiles/leobase.dir/build

CMakeFiles/leobase.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/leobase.dir/cmake_clean.cmake
.PHONY : CMakeFiles/leobase.dir/clean

CMakeFiles/leobase.dir/depend:
	cd /home/leoshih/workdir/working/tdpano/libs/leobase && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leoshih/workdir/working/leobase /home/leoshih/workdir/working/leobase /home/leoshih/workdir/working/tdpano/libs/leobase /home/leoshih/workdir/working/tdpano/libs/leobase /home/leoshih/workdir/working/tdpano/libs/leobase/CMakeFiles/leobase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/leobase.dir/depend

