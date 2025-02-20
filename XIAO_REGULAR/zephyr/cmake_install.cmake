# Install script for directory: C:/ncs/v2.7.0/zephyr

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  set(CMAKE_OBJDUMP "C:/ncs/toolchains/ce3b5ff664/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/suit-processor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_REGULAR/zephyr/cmake/reports/cmake_install.cmake")
endif()

