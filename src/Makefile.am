bin_PROGRAMS = cmics
dist_bin_SCRIPTS = img
man1_MANS = cmics.1
cmics_SOURCES = com_reg.c com_reg.h coms.c coms.h constants.h dirs.c dirs.h imgs.c \
                imgs.h logic.c logic.h main.c menu.c menu.h rm.c rm.h url.c url.h \
                utils.c utils.h curses.h curses.c cli.c cli.h cmics.1
cmics_CPPFLAGS = $(CURL_CFLAGS) $(CURSES_CFLAGS) $(SQLITE_CFLAGS)
cmics_LDFLAGS = $(CURL_LIBS) $(CURSES_LIBS) $(SQLITE_LIBS)

