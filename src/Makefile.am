bin_PROGRAMS = cmics
dist_bin_SCRIPTS = img
man1_MANS = cmics.1
cmics_SOURCES = coms.c coms.h constants.h dirs.c dirs.h imgs.c \
                imgs.h logic.c logic.h main.c \
                utils.c utils.h curses.h curses.c cmics.1
cmics_CPPFLAGS = $(CURL_CFLAGS) $(CURSES_CFLAGS) $(SQLITE_CFLAGS)
cmics_LDFLAGS = $(CURL_LIBS) $(CURSES_LIBS) $(SQLITE_LIBS)

