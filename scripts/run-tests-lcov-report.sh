#!/bin/bash

OUTPUT_DIRECTORY="docs/coverage_report"

lcov --capture --no-external --exclude "*test*" --directory . --output-file coverage_report.info
genhtml coverage_report.info --output-directory "$OUTPUT_DIRECTORY"
