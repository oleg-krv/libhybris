lib_LTLIBRARIES = \
        libmxmnetsdk.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libmxmnetsdk.pc

libmxmnetsdk_la_SOURCES = mxmnetsdk.c
libmxmnetsdk_la_CFLAGS = -I$(top_srcdir)/include $(ANDROID_HEADERS_CFLAGS)
if WANT_TRACE
libmxmnetsdk_la_CFLAGS += -DDEBUG
endif
if WANT_DEBUG
libmxmnetsdk_la_CFLAGS += -ggdb -O0
endif
libmxmnetsdk_la_LDFLAGS = \
        -version-info "2":"0":"0"
