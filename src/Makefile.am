SUBDIRS = \
	.  \
	blocxx_export \
	common

# $(1) = symlink name
# $(2) = relative directory (relative to $(top_builddir)/src)
define SYMLINK_TEMPLATE
$(1): Makefile
	rm -f $(top_builddir)/src/$(1)
	ln -s $(top_builddir)/src/$(2) $(top_builddir)/src/$(1)
	if [ "x$(top_srcdir)" != "x$(top_builddir)" ]; then \
		rm -f $(top_srcdir)/src/$(1); \
		ln -s $(top_srcdir)/src/$(2) $(top_srcdir)/src/$(1); \
	fi
endef

# Create rules for symlink creation.
SYMLINKS = blocxx panorama blocxx_test
$(eval $(call SYMLINK_TEMPLATE,panorama,.))
$(eval $(call SYMLINK_TEMPLATE,blocxx,blocxx_export/src/blocxx))
$(eval $(call SYMLINK_TEMPLATE,blocxx_test,blocxx_export/src/blocxx_test))

all-local: $(SYMLINKS)
