#!/bin/bash

OUTPUT_DIRECTORY=$1

find bin -name '*Tests' | while read testModule; do
    ./"$testModule" --gtest_filter=* --gtest_color=yes --gtest_output="xml:$OUTPUT_DIRECTORY/xunit_report.xml"
done
