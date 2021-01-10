#!/bin/bash

OUTPUT_DIRECTORY="docs/reports/coverage_html"

lcov --capture --no-external --exclude "*test*" --directory . --output-file coverage_report.info
genhtml coverage_report.info --output-directory "$OUTPUT_DIRECTORY"
