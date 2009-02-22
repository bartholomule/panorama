#!/bin/sh

#BLOCXX_BRANCH=branches/2.0
BLOCXX_BRANCH=trunk
EXPORT_DIR=blocxx_export

svn export https://blocxx.svn.sourceforge.net/svnroot/blocxx/${BLOCXX_BRANCH} ${EXPORT_DIR}

sed -i .old 's?\[blocxx/BLOCXX_config.h\]?[src/blocxx/BLOCXX_config.h]?g' ${EXPORT_DIR}/configure.in
