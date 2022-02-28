#!/bin/bash

set -e

mkdir -p build; cd build; cmake ..; make; ./service_locator_tests; ./example
