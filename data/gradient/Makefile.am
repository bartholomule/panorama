FILES = crackle1 \
	lrgold \
	marble1 \
	marble2 \
	tropical \
	wood1 \
	wood2 \
	wood3 \
	wood4 \
	wood5

include $(top_builddir)/Makefile.vars

install-exec-local:
		@echo Installing gradient files...
		$(INSTALL) -d $(GRADIENT_DIR)
		$(INSTALL_DATA) $(FILES) $(GRADIENT_DIR)
