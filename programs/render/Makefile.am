bin_PROGRAMS = render
render_LDADD = -L${top_builddir}/llapi -L${top_builddir}/hlapi -lllapi -lhlapi @LIBS@ ${ARCH_PROG_SETLIBPATH}
render_CXXFLAGS = -DTOPDIR=\"$(prefix)\"
render_SOURCES = render.cpp
