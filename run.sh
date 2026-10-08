#!/usr/bin/env bash
# Usage: ./run.sh <str>
# Try to run an executable named <str> from ./build if that directory exists.

str="$1"

if [ -z "$str" ]; then
    echo "usage: $0 <str> [args...]" >&2
    exit 2
fi
shift

cd_back=0

if [ -d build ]; then
    cd build || exit 1
    cd_back=1
fi

rc=0

if [ -x "./$str" ]; then
    "./$str" "$@"
    rc=$?
else
    echo "run.sh: '$str' not found or not executable here ($PWD)" >&2
    rc=1
fi

if [ "$cd_back" -eq 1 ]; then
    cd ..
fi

exit "$rc"
