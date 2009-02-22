include @top_builddir@/Makefile.vars
bin_PROGRAMS = panorama

static_flags = -L${BUILD_TOP}/llapi -L${BUILD_TOP}/hlapi -lllapi -lhlapi @LIBS@ ${ARCH_PROG_SETLIBPATH}

panorama_CXXFLAGS = $(GTKMM_CFLAGS) -O2 -fno-expensive-optimizations
panorama_LDADD  = $(GTKMM_LDFLAGS) -L${BUILD_TOP}/llapi -L${BUILD_TOP}/hlapi -lllapi -lhlapi $(static_flags)

panorama_SOURCES = \
	main.cpp   \
	scene_window.cpp \
	scene_callbacks.cpp \
	scene_tree.cpp \
	image_window.cpp \
	image_callbacks.cpp \
	message_dialog.cpp \
	render_dialog.cpp \
	object_properties_dialog.cpp \
	color_preview.cpp \
	plugin_window.cpp \
	material_window.cpp \
	material_graph.cpp
