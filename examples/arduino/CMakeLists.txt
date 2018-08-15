set(ARDUINO_IDE "${CMAKE_CURRENT_SOURCE_DIR}/../../../arduino-1.8.3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../../arduino-cmake-minimal/cmake/")

include(ArduinoMinimal)

file(GLOB SOURCE_FILES *.cpp ../../src/*.cpp)

arduino(alogging-example-arduino "${SOURCE_FILES}" "${LIBRARIES}")

target_include_directories(alogging-example-arduino PUBLIC ./ ../../src)
