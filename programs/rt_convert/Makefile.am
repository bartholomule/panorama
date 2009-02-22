bin_PROGRAMS = rt_convert

BISONFLAGS = --name-prefix='rt_conv_' -dv
LEXFLAGS   = -Prt_conv_
CXXFLAGS   = -O0 -DYYSTYPE=string

rt_convert_SOURCES =				\
	parser.cpp				\
	scanner.cpp				\
	rt_convert.cpp

rt_convert_LDADD = ${STATIC_HLAPI_LIB} ${STATIC_LLAPI_LIB}
