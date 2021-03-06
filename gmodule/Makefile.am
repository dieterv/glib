## Process this file with automake to produce Makefile.in
include $(top_srcdir)/Makefile.decl

AM_CPPFLAGS = 				\
	$(glib_INCLUDES) 		\
	-DG_LOG_DOMAIN=\"GModule\" 	\
	@GLIB_DEBUG_FLAGS@ 		\
	-DG_DISABLE_DEPRECATED

if OS_WIN32
AM_CPPFLAGS += 					\
	-DWINVER=0x0501				\
	-D_WIN32_WINNT=0x0501			\
	-DSTRICT
endif

gmodule.def: gmodule.symbols
	$(AM_V_GEN) (echo EXPORTS; $(CPP) -P -DG_OS_WIN32 - <$(srcdir)/gmodule.symbols | sed -e '/^$$/d' -e 's/^/	/') > $(builddir)/gmodule.def

EXTRA_DIST +=				\
		makefile.msc.in 	\
		gmoduleconf.h.in 	\
		gmodule.symbols		\
		gmodule-dl.c		\
		gmodule-dld.c		\
		gmodule-dyld.c		\
		gmodule-os2.c		\
		gmodule-win32.c		\
		gmodule-beos.c		\
		gmodule-ar.c		\
		gmoduleconf.h.win32 	\
		gmodule.rc.in

BUILT_EXTRA_DIST = \
		makefile.msc	\
		gmodule.rc

BUILT_SOURCES = gmoduleconf.h
gmoduleconf.h:	gmoduleconf.h.in

glibincludedir=$(includedir)/glib-2.0
glibinclude_HEADERS = \
		gmodule.h

libglib = $(top_builddir)/glib/libglib-2.0.la

top_builddir_full=`cd \$(top_builddir); pwd`

lib_LTLIBRARIES = libgmodule-2.0.la

if OS_WIN32_AND_DLL_COMPILATION
if MS_LIB_AVAILABLE
noinst_DATA = gmodule-2.0.lib

install_ms_lib_cmd = $(INSTALL) gmodule-2.0.lib $(DESTDIR)$(libdir)
uninstall_ms_lib_cmd = -rm $(DESTDIR)$(libdir)/gmodule-2.0.lib
endif
endif

install-ms-lib:
	$(install_ms_lib_cmd)

uninstall-ms-lib:
	$(uninstall_ms_lib_cmd)

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

if OS_WIN32_AND_DLL_COMPILATION
export_symbols = -export-symbols $(builddir)/gmodule.def
gmodule_def = gmodule.def

gmodule_win32_res = gmodule-win32-res.o
gmodule_win32_res_ldflag = -Wl,$(gmodule_win32_res)

install-def-file:
	$(INSTALL) $(builddir)/gmodule.def $(DESTDIR)$(libdir)/gmodule-2.0.def

uninstall-def-file:
	-rm $(DESTDIR)$(libdir)/gmodule-2.0.def
else
install-def-file:
uninstall-def-file:
endif

libgmodule_2_0_la_SOURCES = gmodule.c
libgmodule_2_0_la_LDFLAGS = $(GLIB_LINK_FLAGS) \
	$(gmodule_win32_res_ldflag) \
	$(G_MODULE_LDFLAGS) \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
	-export-dynamic $(no_undefined) $(export_symbols)

libgmodule_2_0_la_LIBADD = $(G_MODULE_LIBS_EXTRA) $(G_MODULE_LIBS) $(libglib)

libgmodule_2_0_la_DEPENDENCIES = $(gmodule_win32_res) $(gmodule_def)

gmodule-win32-res.o: gmodule.rc
	$(AM_V_GEN) $(WINDRES) gmodule.rc $@

gmodule-2.0.lib: libgmodule-2.0.la gmodule.def
	lib -machine:@LIB_EXE_MACHINE_FLAG@ -name:libgmodule-2.0-$(LT_CURRENT_MINUS_AGE).dll -def:$(builddir)/gmodule.def -out:$@

.PHONY: files release

files:
	@files=`ls $(DISTFILES) 2> /dev/null `; for p in $$files; do \
	  echo $$p; \
	done

release:
	$(MAKE) dist distdir=$(PACKAGE)`date +"%y%m%d"`

dist-hook: $(BUILT_EXTRA_DIST)
	@files='$(BUILT_EXTRA_DIST)'; \
	for f in $$files; do \
	  if test -f $$f; then d=.; else d=$(srcdir); fi; \
	  cp $$d/$$f $(distdir) || exit 1; done


install-data-local: install-ms-lib install-def-file

uninstall-local: uninstall-ms-lib uninstall-def-file

if HAVE_GLIB_RUNTIME_LIBDIR
install-data-hook:
	mkdir -p $(DESTDIR)$(libdir)/$(GLIB_RUNTIME_LIBDIR)
	mv $(DESTDIR)$(libdir)/libgmodule-2.0.so.0 $(DESTDIR)$(libdir)/$(GLIB_RUNTIME_LIBDIR)
	mv $(DESTDIR)$(libdir)/libgmodule-2.0.so.0.$(LT_CURRENT).$(LT_REVISION) $(DESTDIR)$(libdir)/$(GLIB_RUNTIME_LIBDIR)
	rm -f $(DESTDIR)$(libdir)/libgmodule-2.0.so
	ln -s $(GLIB_RUNTIME_LIBDIR)/libgmodule-2.0.so.0.$(LT_CURRENT).$(LT_REVISION) $(DESTDIR)$(libdir)/libgmodule-2.0.so
endif
