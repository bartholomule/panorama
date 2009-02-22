lib_LTLIBRARIES = \
	libplugin_rt_io.la

PARSER_PREFIX=rt_

AM_YFLAGS = -v -d --name-prefix=$(PARSER_PREFIX)
AM_LFLAGS = -P$(PARSER_PREFIX) -Cfe

parser.cpp: parser.y
	$(YACC) $(YFLAGS) $(AM_YFLAGS) -o$@ $^

scanner.cpp: scanner.l
	$(LEX) $(AM_LFLAGS) -o$@ $^

BUILT_SOURCES = parser.cpp scanner.cpp

libplugin_rt_io_la_SOURCES = \
	parser.cpp \
	scanner.cpp \
	attribute_math.cpp \
	attrib_tweak.cpp \
	rt_io.cpp \
	language_functions.cpp

extra_DIST =  \
	scanner.l \
	parser.y

#M_YFLAGS = -d -powmof                                                          
#AM_LFLAGS = -i -Cfe -Powmof -olex.yy.c        

