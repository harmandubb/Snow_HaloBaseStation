@echo off
cd /D C:\Users\harma\Documents\Git_Projects\Snow_HaloBaseStation\XIAO_SENSE\Snow_HaloBaseStation\zephyr || (set FAIL_LINE=2& goto :ABORT)
C:\ncs\toolchains\b620d30767\opt\bin\cmake.exe -E make_directory edk/include/generated/zephyr || (set FAIL_LINE=3& goto :ABORT)
C:\ncs\toolchains\b620d30767\opt\bin\python.exe C:/ncs/v2.9.0/zephyr/scripts/build/gen_syscalls.py --json-file C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/misc/generated/syscalls.json --base-output edk/include/generated/zephyr/syscalls --syscall-dispatch edk/include/generated/zephyr/syscall_dispatch.c --syscall-list C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/edk/include/generated/zephyr/syscall_list.h --split-type k_timeout_t --split-type k_ticks_t || (set FAIL_LINE=4& goto :ABORT)
C:\ncs\toolchains\b620d30767\opt\bin\cmake.exe -DPROJECT_BINARY_DIR=C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr -DAPPLICATION_SOURCE_DIR=C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation -DINTERFACE_INCLUDE_DIRECTORIES="C:/ncs/v2.9.0/nrf/drivers/mpsl/clock_control C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/include/generated/zephyr C:/ncs/v2.9.0/zephyr/include C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/include/generated C:/ncs/v2.9.0/zephyr/soc/nordic C:/ncs/v2.9.0/zephyr/lib/libc/common/include C:/ncs/v2.9.0/zephyr/soc/nordic/nrf52/. C:/ncs/v2.9.0/zephyr/soc/nordic/common/. C:/ncs/v2.9.0/zephyr/subsys/usb/device C:/ncs/v2.9.0/zephyr/subsys/bluetooth C:/ncs/v2.9.0/zephyr/subsys/settings/include C:/ncs/v2.9.0/zephyr/drivers/usb/common/nrf_usbd_common/. C:/ncs/v2.9.0/nrf/include C:/ncs/v2.9.0/nrf/lib/multithreading_lock/. C:/ncs/v2.9.0/nrf/subsys/bluetooth/controller/. C:/ncs/v2.9.0/zephyr/drivers/flash C:/ncs/v2.9.0/nrf/tests/include C:/ncs/v2.9.0/modules/hal/cmsis/CMSIS/Core/Include C:/ncs/v2.9.0/zephyr/modules/cmsis/. C:/ncs/v2.9.0/modules/hal/nordic/nrfx C:/ncs/v2.9.0/modules/hal/nordic/nrfx/drivers/include C:/ncs/v2.9.0/modules/hal/nordic/nrfx/mdk C:/ncs/v2.9.0/zephyr/modules/hal_nordic/nrfx/. C:/ncs/v2.9.0/modules/crypto/tinycrypt/lib/include C:/ncs/v2.9.0/nrfxlib/softdevice_controller/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/common/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/nrf21540_gpio/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/nrf21540_gpio_spi/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/nrf2220/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/nrf2240/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/nrf22xx/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/simple_gpio/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/include C:/ncs/v2.9.0/nrfxlib/mpsl/fem/include/protocol C:/ncs/v2.9.0/nrfxlib/mpsl/include C:/ncs/v2.9.0/nrfxlib/mpsl/include/protocol C:/ncs/v2.9.0/nrfxlib/crypto/nrf_cc310_platform/include" -Dllext_edk_file=C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/llext-edk.tar.xz -Dllext_edk_cflags="-DKERNEL -D__ZEPHYR__=1 -D__LINUX_ERRNO_EXTENSIONS__ -DPICOLIBC_LONG_LONG_PRINTF_SCANF -DUSE_PARTITION_MANAGER=1 -D__PROGRAM_START -DNRF52840_XXAA -DK_HEAP_MEM_POOL_SIZE=8192 -DLL_EXTENSION_BUILD -fno-strict-aliasing -imacros C:/Users/harma/Documents/Git_Projects/Snow_HaloBaseStation/XIAO_SENSE/Snow_HaloBaseStation/zephyr/include/generated/zephyr/autoconf.h -fno-printf-return-value -fno-common -fdiagnostics-color=always -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfp16-format=ieee -mtp=soft -imacros C:/ncs/v2.9.0/zephyr/include/zephyr/toolchain/zephyr_stdint.h -Wall -Wformat -Wformat-security -Wformat -Wno-format-zero-length -Wdouble-promotion -Wno-pointer-sign -Wpointer-arith -Wexpansion-to-defined -Wno-unused-but-set-variable -Werror=implicit-int -fno-asynchronous-unwind-tables -ftls-model=local-exec -fno-reorder-functions --param=min-pagesize=0 -fno-defer-pop -specs=picolibc.specs -std=c99 -mlong-calls -mthumb -nodefaultlibs" -Dllext_edk_name=llext-edk -DWEST_TOPDIR=C:/ncs/v2.9.0 -DZEPHYR_BASE=C:/ncs/v2.9.0/zephyr -DCONFIG_LLEXT_EDK_USERSPACE_ONLY= -P C:/ncs/v2.9.0/zephyr/cmake/llext-edk.cmake || (set FAIL_LINE=5& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%