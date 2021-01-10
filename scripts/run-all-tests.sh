#!/bin/bash

find bin -name '*Tests' | while read testModule; do
    ./"$testModule" --gtest_filter=* --gtest_color=yes
done
