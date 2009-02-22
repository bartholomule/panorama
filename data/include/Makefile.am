FILES = colors.inc \
        materials.inc \
        cameras.inc \
        math.inc \
        shapes.inc
include $(top_builddir)/Makefile.vars

install-exec-local:
		@echo Installing include files...
		$(INSTALL) -d ${INCLUDE_DIR}
		$(INSTALL_DATA) $(FILES) ${INCLUDE_DIR}

