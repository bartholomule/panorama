SUBDIRS  =					\
	developers				\
        users

FILES =						\
	AUTHORS					\
	BUGS					\
        CREDITS					\
        EXPERIMENTAL				\
        FAQ.html				\
        INSTALL					\
        LICENSE					\
        NEWS					\
        README					\
        pluginrc				\
        config

EXTRA_DIST = $(FILES)

include $(top_builddir)/Makefile.vars

install-exec-local:
		$(INSTALL) -d $(DOC_DIR)
		$(INSTALL) -d $(CONFIG_DIR)
		$(INSTALL_DATA) $(FILES) $(DOC_DIR)
		$(INSTALL_DATA) $(srcdir)/config $(CONFIG_DIR)
		$(INSTALL_DATA) $(srcdir)/pluginrc $(CONFIG_DIR)
