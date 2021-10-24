#!/bin/bash
echo "LTTNG_UST_ALLOW_BLOCKING " $LTTNG_UST_ALLOW_BLOCKING
lttng create lttngtest
lttng enable-channel --userspace --blocking-timeout=0 --subbuf-size=524288 --num-subbuf=4 mychannel
#lttng enable-channel --userspace --buffers-pid --subbuf-size=131072 --num-subbuf=4 mychannel
lttng enable-event -u 'lttng_ust_tracef:*' -c mychannel
lttng add-context -u -t vpid -t vtid -t procname
lttng start
START=$(date +%s.%N)
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
./build/lttngtest 1000000 0 &
wait
lttng stop
END=$(date +%s.%N)
echo $END-$START | bc
