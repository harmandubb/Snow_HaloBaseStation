# Install script for directory: C:/ncs/v2.9.0/zephyr/drivers

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
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/disk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/firmware/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/interrupt_controller/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/misc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/pcie/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/usb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/usb_c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/adc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/bluetooth/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/clock_control/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/console/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/entropy/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/gnss/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/gpio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/hwinfo/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/i2c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/pinctrl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/pwm/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/regulator/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/sensor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/serial/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/drivers/timer/cmake_install.cmake")
endif()
