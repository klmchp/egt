AUTOMAKE_OPTIONS = subdir-objects

CUSTOM_CXXFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_builddir)/include \
	$(cairo_CFLAGS) \
	$(CODE_COVERAGE_CXXFLAGS)

CUSTOM_LDADD = $(cairo_LIBS) $(CODE_COVERAGE_LDFLAGS)

check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = ../external/googletest/googletest/src/gtest-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/external/googletest/googletest/include \
	-I$(top_srcdir)/external/googletest/googletest
libgtest_la_LDFLAGS = -pthread

check_PROGRAMS = \
unittests

if ENABLE_UNITTESTS
bin_PROGRAMS = $(check_PROGRAMS)
endif

unittests_SOURCES = \
main.cpp \
widgets/button.cpp \
widgets/combobox.cpp \
widgets/form.cpp \
widgets/frame.cpp \
widgets/grid.cpp \
widgets/layout.cpp  \
widgets/listbox.cpp  \
widgets/notebook.cpp \
widgets/scrollwheel.cpp \
widgets/sizer.cpp \
widgets/slider.cpp \
widgets/valuerange.cpp \
widgets/view.cpp \
widgets/window.cpp

if HAVE_GSTREAMER
unittests_SOURCES += \
audio/audio.cpp \
video/camera.cpp \
video/video.cpp
endif

unittests_CPPFLAGS = -I$(top_srcdir)/external/googletest/googletest/include \
	-I$(top_srcdir)/external/googletest/googletest -pthread
unittests_CXXFLAGS = $(CUSTOM_CXXFLAGS) $(AM_CXXFLAGS)
unittests_LDADD = libgtest.la $(top_builddir)/src/libegt.la $(CUSTOM_LDADD)
unittests_LDFLAGS = $(AM_LDFLAGS)

TESTS = $(check_PROGRAMS)
