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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gmatczak/raspicam-0.1.8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gmatczak/raspicam-0.1.8/build

# Include any dependencies generated for this target.
include src/CMakeFiles/raspicam_cv.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/raspicam_cv.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/raspicam_cv.dir/flags.make

src/CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.o: src/CMakeFiles/raspicam_cv.dir/flags.make
src/CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.o: ../src/raspicam_cv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gmatczak/raspicam-0.1.8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.o"
	cd /home/gmatczak/raspicam-0.1.8/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.o -c /home/gmatczak/raspicam-0.1.8/src/raspicam_cv.cpp

src/CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.i"
	cd /home/gmatczak/raspicam-0.1.8/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmatczak/raspicam-0.1.8/src/raspicam_cv.cpp > CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.i

src/CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.s"
	cd /home/gmatczak/raspicam-0.1.8/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmatczak/raspicam-0.1.8/src/raspicam_cv.cpp -o CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.s

src/CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.o: src/CMakeFiles/raspicam_cv.dir/flags.make
src/CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.o: ../src/raspicam_still_cv.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gmatczak/raspicam-0.1.8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.o"
	cd /home/gmatczak/raspicam-0.1.8/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.o -c /home/gmatczak/raspicam-0.1.8/src/raspicam_still_cv.cpp

src/CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.i"
	cd /home/gmatczak/raspicam-0.1.8/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gmatczak/raspicam-0.1.8/src/raspicam_still_cv.cpp > CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.i

src/CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.s"
	cd /home/gmatczak/raspicam-0.1.8/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gmatczak/raspicam-0.1.8/src/raspicam_still_cv.cpp -o CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.s

# Object files for target raspicam_cv
raspicam_cv_OBJECTS = \
"CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.o" \
"CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.o"

# External object files for target raspicam_cv
raspicam_cv_EXTERNAL_OBJECTS =

src/libraspicam_cv.so.0.1.8: src/CMakeFiles/raspicam_cv.dir/raspicam_cv.cpp.o
src/libraspicam_cv.so.0.1.8: src/CMakeFiles/raspicam_cv.dir/raspicam_still_cv.cpp.o
src/libraspicam_cv.so.0.1.8: src/CMakeFiles/raspicam_cv.dir/build.make
src/libraspicam_cv.so.0.1.8: src/libraspicam.so.0.1.8
src/libraspicam_cv.so.0.1.8: /opt/vc/lib/libmmal_core.so
src/libraspicam_cv.so.0.1.8: /opt/vc/lib/libmmal_util.so
src/libraspicam_cv.so.0.1.8: /opt/vc/lib/libmmal.so
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_gapi.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_stitching.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_aruco.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_bgsegm.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_bioinspired.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_ccalib.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_dnn_objdetect.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_dpm.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_face.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_freetype.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_fuzzy.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_hdf.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_hfs.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_img_hash.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_line_descriptor.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_quality.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_reg.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_rgbd.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_saliency.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_stereo.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_structured_light.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_superres.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_surface_matching.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_tracking.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_videostab.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_viz.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_xfeatures2d.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_xobjdetect.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_xphoto.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_shape.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_datasets.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_plot.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_text.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_dnn.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_highgui.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_ml.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_phase_unwrapping.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_optflow.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_ximgproc.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_video.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_videoio.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_imgcodecs.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_objdetect.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_calib3d.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_features2d.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_flann.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_photo.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_imgproc.so.4.1.1
src/libraspicam_cv.so.0.1.8: /usr/lib/libopencv_core.so.4.1.1
src/libraspicam_cv.so.0.1.8: src/CMakeFiles/raspicam_cv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gmatczak/raspicam-0.1.8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libraspicam_cv.so"
	cd /home/gmatczak/raspicam-0.1.8/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raspicam_cv.dir/link.txt --verbose=$(VERBOSE)
	cd /home/gmatczak/raspicam-0.1.8/build/src && $(CMAKE_COMMAND) -E cmake_symlink_library libraspicam_cv.so.0.1.8 libraspicam_cv.so.0.1 libraspicam_cv.so

src/libraspicam_cv.so.0.1: src/libraspicam_cv.so.0.1.8
	@$(CMAKE_COMMAND) -E touch_nocreate src/libraspicam_cv.so.0.1

src/libraspicam_cv.so: src/libraspicam_cv.so.0.1.8
	@$(CMAKE_COMMAND) -E touch_nocreate src/libraspicam_cv.so

# Rule to build all files generated by this target.
src/CMakeFiles/raspicam_cv.dir/build: src/libraspicam_cv.so

.PHONY : src/CMakeFiles/raspicam_cv.dir/build

src/CMakeFiles/raspicam_cv.dir/clean:
	cd /home/gmatczak/raspicam-0.1.8/build/src && $(CMAKE_COMMAND) -P CMakeFiles/raspicam_cv.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/raspicam_cv.dir/clean

src/CMakeFiles/raspicam_cv.dir/depend:
	cd /home/gmatczak/raspicam-0.1.8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gmatczak/raspicam-0.1.8 /home/gmatczak/raspicam-0.1.8/src /home/gmatczak/raspicam-0.1.8/build /home/gmatczak/raspicam-0.1.8/build/src /home/gmatczak/raspicam-0.1.8/build/src/CMakeFiles/raspicam_cv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/raspicam_cv.dir/depend

