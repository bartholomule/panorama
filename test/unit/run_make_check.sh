#!/bin/sh

# The current directory needs to be in the path so dlopen() can find the test library for the LazyGlobal test.
LD_LIBRARY_PATH="`pwd`:`pwd`/../../src/blocxx:$LD_LIBRARY_PATH"

# AIX
LIBPATH="$LD_LIBRARY_PATH:$LIBPATH"

# HP-UX
SHLIB_PATH="$LD_LIBRARY_PATH:$SHLIB_PATH"

# DARWIN (OSX)
DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:$LD_LIBRARY_PATH"

export LD_LIBRARY_PATH LIBPATH SHLIB_PATH DYLD_LIBRARY_PATH

MAKE=${MAKE:-make}

if [ $# -eq 0 ] || [ x$1 = xall ]; then
	${MAKE} check
	exit $?
fi

for testname in "$@"; do
	if [ -f ${testname}TestCases ]; then
		# Rebuild it to ensure we're current.
		${MAKE} ${testname}TestCases || exit $?
		echo "Running tests in ${testname}TestCases"
		./${testname}TestCases || exit $?
	elif [ -f ${testname} ]; then
		# Rebuild it to ensure we're current.
		${MAKE} ${testname} || exit $?
		echo "Running tests in ${testname}"
		./${testname} || exit $?
	elif [ -f ./${testname}TestCases.cpp ] || [ -f ./${testname}Test.cpp ]; then
		if grep ${testname}TestCases.hpp UnitMain.cpp >/dev/null 2>&1; then
			make unitMain
			echo "Running tests for ${testname} (inside unitMain)"
			./unitMain ${testname}
		else
			# Build and rerun...
			${MAKE} || exit $?
			exec "$0" "$@"
		fi
	else
		echo "No test for ${testname}" >&2
		exit 1
	fi
done


