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
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/suit-processor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bhupi/Git_Projects/SnowHalo/Snow_HaloBaseStation/XIAO_SENSE/zephyr/cmake/reports/cmake_install.cmake")
endif()

