cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(Mark_1)

# NORDIC SDK APP START
target_sources(app PRIVATE
  src/main.c
  src/led_control.c
  src/led_control.h
  src/bluetooth_control.c
  src/bluetooth_control.h
  src/adc_control.c
  src/adc_control.h
  src/button_control.c
  src/button_control.h
  src/UART_bt_control.c
  src/UART_bt_control.h
  src/boot_bt_connect.c
  src/boot_bt_connect.h
  src/GPS.c
  src/GPS.h
  src/IMU.c
  src/IMU.h
  src/iphone_bt_connect.c
  src/iphone_bt_connect.h
  src/left_boot_operation.c
  src/left_boot_operation.h
  src/right_boot_operation.c
  src/right_boot_operation.h
)

# NORDIC SDK APP END
zephyr_library_include_directories(.)