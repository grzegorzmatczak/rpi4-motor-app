 cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(rpi-motor-app
  VERSION 0.0.1
  DESCRIPTION "rpi-motor-app"
  LANGUAGES C CXX)
  
enable_testing()

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON} -std=c++17 -pthread ")
	set(I2C_ARDUINO FALSE)
endif (WIN32)

if (UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON} -std=c++17 -pthread -lwiringPi ")
	set(I2C_ARDUINO TRUE)
endif (UNIX)

set(DEFAULT_BUILD_TYPE "Debug")
set(CMAKE_BUILD_TYPE "Debug")
set(TARGET_NAME "rpi-motor-app")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


IF(NOT TARGET_PROCESSOR)
    SET(TARGET_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})
ENDIF()

if(${TARGET_PROCESSOR} MATCHES armv7l) # In ARM_COrtex8 with neon, enalble vectorized operations
    set(GENERAL_FLAGS "${GENERAL_FLAGS} -mcpu=cortex-a8 -mfpu=neon -mfloat-abi=hard ")
endif()
if(${TARGET_PROCESSOR} MATCHES armv6l) # In PiZero with neon, enalble vectorized operations
    set(GENERAL_FLAGS "${GENERAL_FLAGS}  -mabi=aapcs-linux -marm  -march=armv6 -mfloat-abi=hard  -mfp16-format=none -mfpu=vfp -mlittle-endian -mpic-data-is-text-relative -mrestrict-it -msched-prolog -mstructure-size-boundary=0x20 -mtp=auto -mtls-dialect=gnu -munaligned-access -mvectorize-with-neon-quad")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (WIN32)
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\opencvBuild")
	set(QT5_PATH "E:\\Qt\\5.12.8\\msvc2017_64")
	list(APPEND CMAKE_PREFIX_PATH "E:\\Qt\\5.12.8\\msvc2017_64")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\spdlog\\build\\install")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\spdlog\\build\\install//lib//cmake//spdlog")
	include("E:\\repo\\spdlog\\cmake\\utils.cmake")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\IncludeSpdlog\\build\\install")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\ConfigReader\\build\\install")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\QtCommunicator\\build\\install")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\QtCommunicatorPlugin\\build\\install")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\Broadcaster\\build\\install")
endif (WIN32)

configure_file(config.json ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config.json)
configure_file(config.json ${CMAKE_BINARY_DIR}/config.json)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5SerialPort REQUIRED)
find_package(Qt5Network REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


find_package(spdlog REQUIRED)
find_package(IncludeSpdlog REQUIRED)
find_package(ConfigReader REQUIRED)
find_package(QtCommunicatorPlugin REQUIRED)
find_package(Broadcaster REQUIRED)

if (UNIX)
	add_subdirectory(raspicam-0.1.8)
endif (UNIX)

set(SRC	src/main.cc)

file(GLOB_RECURSE SRC_GLOB src/*.cc src/*.c src/*.cpp)
file(GLOB_RECURSE HEADERS_GLOB src/*.h src/*.hpp)

if (WIN32)
	set(SRC_IMAGE_PROCESSING ImageProcessing/acquisition.cc ImageProcessing/bounds.cc)
	set(HEADERS_IMAGE_PROCESSING ImageProcessing/acquisition.h ImageProcessing/bounds.h)
endif (WIN32)



if (UNIX)
	INCLUDE_DIRECTORIES(raspicam-0.1.8/src)
	LINK_LIBRARIES(raspicam_cv)

	set(SRC_IMAGE_PROCESSING
		ImageProcessing/acquisitionraspi.cc
		ImageProcessing/bounds.cc
		ImageProcessing/capture.cc)

	set(HEADERS_IMAGE_PROCESSING
		ImageProcessing/acquisitionraspi.h
		ImageProcessing/bounds.h
		ImageProcessing/capture.h)
endif (UNIX)

add_executable(${TARGET_NAME}
	config.json
    ${SRC} ${HEADERS}
	${SRC_GLOB} ${HEADERS_GLOB}
	${SRC_IMAGE_PROCESSING} ${HEADERS_IMAGE_PROCESSING}
)

add_executable(testModules 
	config.json
	${SRC} ${HEADERS}
	${SRC_GLOB} ${HEADERS_GLOB}
	${SRC_IMAGE_PROCESSING} ${HEADERS_IMAGE_PROCESSING}
)
	
add_test(testModules testModules)

target_link_libraries(testModules Broadcaster)
target_link_libraries(testModules ${OpenCV_LIBS} Threads::Threads)
target_link_libraries(testModules Qt5::Test Qt5::Network Qt5::Widgets Qt5::SerialPort)


if (UNIX)
	target_link_libraries(${PROJECT_NAME} Broadcaster)
	target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} Threads::Threads)
	target_link_libraries(${PROJECT_NAME} Qt5::Test Qt5::Network Qt5::Widgets Qt5::SerialPort)
endif (UNIX)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} Broadcaster)
	target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} Threads::Threads)
	target_link_libraries(${PROJECT_NAME} Qt5::Test Qt5::Network Qt5::Widgets Qt5::SerialPort)
endif (WIN32)

if (UNIX)
	target_link_libraries(${PROJECT_NAME} raspicam_cv ${raspicam_CV_LIBS})
	include_directories("raspicam-0.1.8/dependencies/interface/vcos" "raspicam-0.1.8/../dependencies/interface" "raspicam-0.1.8/../dependencies")
	
endif (UNIX)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} ")

if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

if (WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
       COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif(WIN32)

if (WIN32)
	macro(qt5_copy_dll APP DLL)
		# find the release *.dll file
		get_target_property(Qt5_${DLL}Location Qt5::${DLL} LOCATION)
		# find the debug *d.dll file
		get_target_property(Qt5_${DLL}LocationDebug Qt5::${DLL} IMPORTED_LOCATION_DEBUG)
		add_custom_command(TARGET ${APP} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Debug>:${Qt5_${DLL}LocationDebug}> $<$<NOT:$<CONFIG:Debug>>:${Qt5_${DLL}Location}> $<TARGET_FILE_DIR:${APP}>)
	endmacro()
	qt5_copy_dll( ${PROJECT_NAME} Core)

	message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}/bin/Release ")


	set(OPENCV_PREFIX_BUILD_TYPE "")
	message("Copy OpenCV file:" )
	if(${CMAKE_BUILD_TYPE} STREQUAL  "Release")
		set(OPENCV_PREFIX_BUILD_TYPE "")
	endif()
	if(${CMAKE_BUILD_TYPE} STREQUAL  "Debug")
		set(OPENCV_PREFIX_BUILD_TYPE "d")

	endif()
	message("Copy OpenCV file:" )
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_stitching450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_bgsegm450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_tracking450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_videoio450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_video450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_imgcodecs450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_imgproc450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_core450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_calib3d450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_features2d450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_flann450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_dnn450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_highgui450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_gapi450${OPENCV_PREFIX_BUILD_TYPE}.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/opencv_videoio_ffmpeg450_64.dll   ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}/
	)
endif(WIN32)