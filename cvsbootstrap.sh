#! /bin/sh

set -e

rm -rf config.cache config.guess config.sub depcomp missing mkinstalldirs autom4te.cache

run_autocmd()
{
  echo "Running $1..."
  "$@"
}

run_autocmd aclocal
run_autocmd autoconf
run_autocmd autoheader
run_autocmd automake --foreign --add-missing 
