# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v5.0.1/components/bootloader/subproject"
  "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader"
  "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix"
  "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix/tmp"
  "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix/src"
  "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Ahmadullah/esp/pipelined_sample_transmit/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
