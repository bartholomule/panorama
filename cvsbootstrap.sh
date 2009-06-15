#! /bin/sh

set -e

run_autocmd()
{
	echo "Running $@ ..."
	"$@"
}

original_dir=$PWD

for configure_dir in "$PWD" "$PWD/src/blocxx_export"; do
	cd "${configure_dir}"
	echo "Doing bootstrap in ${configure_dir}"

	rm -rf config.cache ltmain.sh config.guess config.sub depcomp missing mkinstalldirs autom4te.cache


	CONFIGURE_SCRIPT=
	for configure_script in configure.in configure.ac; do
		if [ -f "${configure_dir}/${configure_script}" ]; then
			CONFIGURE_SCRIPT="${configure_dir}/${configure_script}"
			break
		fi
	done

	if [ x${CONFIGURE_SCRIPT:+set} != xset ]; then
		echo "ERROR: Could not locate configure script in ${configure_dir}" >&2
		exit 1
	fi

	run_autocmd aclocal-1.9
	run_autocmd autoconf
	run_autocmd autoheader

	if grep AC_PROG_LIBTOOL "${CONFIGURE_SCRIPT}" >/dev/null 2>&1; then
		run_autocmd libtoolize
	fi
	run_autocmd automake-1.9 --foreign --add-missing

  # Remove default optimizations
	#sed 's/-O2//g' < configure > configure.fixed && mv configure.fixed configure && chmod +x configure
done

cd "${original_dir}"

if [ $# -gt 0 ]; then
	./configure --config-cache "$@"
fi