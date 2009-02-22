all:
		@doxygen ./Doxyfile
install-exec-local:
		@echo Installing api documentation...
		@${SRC_DIR}/${BUILD_TOP}/mkinstalldirs ${DOC_DIR}/api
		@set -e; \
		for i in ${SRC_DIR}/html/*; do \
		  @INSTALL_DATA@ ${SRC_DIR}/$$i ${DOC_DIR}/api; \
		done

distclean:
		@rm -f Makefile Doxygen
