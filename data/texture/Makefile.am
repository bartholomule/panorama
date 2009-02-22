FILES = f16.tga \
	supernova.tga

include $(top_builddir)/Makefile.vars

install-exec-local:
		@echo Installing texture files...
		$(INSTALL) -d $(TEXTURE_DIR)
		$(INSTALL_DATA) $(FILES) $(TEXTURE_DIR)
