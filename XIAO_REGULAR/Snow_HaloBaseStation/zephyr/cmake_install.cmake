# Install script for directory: C:/ncs/v2.9.0/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "MinSizeRel")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/ncs/toolchains/b620d30767/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/suit-processor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_REGULAR/Snow_HaloBaseStation/zephyr/cmake/reports/cmake_install.cmake")
endif()
