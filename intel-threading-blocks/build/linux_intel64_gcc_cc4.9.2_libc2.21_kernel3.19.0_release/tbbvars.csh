#!/bin/csh
setenv TBBROOT "/home/andrew/lockfree-bench/intel-threading-blocks" #
setenv tbb_bin "/home/andrew/lockfree-bench/intel-threading-blocks/build/linux_intel64_gcc_cc4.9.2_libc2.21_kernel3.19.0_release" #
if (! $?CPATH) then #
    setenv CPATH "${TBBROOT}/include" #
else #
    setenv CPATH "${TBBROOT}/include:$CPATH" #
endif #
if (! $?LIBRARY_PATH) then #
    setenv LIBRARY_PATH "${tbb_bin}" #
else #
    setenv LIBRARY_PATH "${tbb_bin}:$LIBRARY_PATH" #
endif #
if (! $?LD_LIBRARY_PATH) then #
    setenv LD_LIBRARY_PATH "${tbb_bin}" #
else #
    setenv LD_LIBRARY_PATH "${tbb_bin}:$LD_LIBRARY_PATH" #
endif #
 #
