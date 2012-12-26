

PHP_ARG_ENABLE(webkitgtk, whether to enable JavaScript Object Serialization support,

[  --disable-webkitgtk          Disable WebKitGTK], yes)

if test "$PHP_webkitgtk" != "no"; then
    AC_MSG_CHECKING(for pkg-config)
	if test ! -f "$PKG_CONFIG"; then
    	PKG_CONFIG=`which pkg-config`
  	fi

	if test -f "$PKG_CONFIG"; then
    	AC_MSG_RESULT(found)	
		AC_MSG_CHECKING(for webkitgtk-3.0)

		if $PKG_CONFIG --exists webkitgtk-3.0; then
        	webkitgtk_version_full=`$PKG_CONFIG --modversion webkitgtk-3.0`
        	AC_MSG_RESULT([found $webkitgtk_version_full])
        	WEBKITGTK_LIBS="$LDFLAGS `$PKG_CONFIG --libs webkitgtk-3.0`"
        	WEBKITGTK_INCS="$CFLAGS `$PKG_CONFIG --cflags-only-I webkitgtk-3.0`"
        	PHP_EVAL_INCLINE($WEBKITGTK_INCS)
        	PHP_EVAL_LIBLINE($WEBKITGTK_LIBS, WEBKITGTK_SHARED_LIBADD)
        	AC_DEFINE(HAVE_WEBKITGTK, 1, [whther webkitgtk-3.0 exists in the system])
    	else
        	AC_MSG_RESULT(not found)
        	AC_MSG_ERROR(Ooops ! no webkitgtk-3.0 detected in the system)
    	fi
	else
		AC_MSG_RESULT(not found)
    	AC_MSG_ERROR(Ooops ! no pkg-config found .... )
	fi

	AC_DEFINE([HAVE_WEBKITGTK],1 ,[whether to enable WebKitGTK])
	PHP_NEW_EXTENSION(webkitgtk, webkitgtk.c webview.c webframe.c, $ext_shared)
	PHP_SUBST(WEBKITGTK_SHARED_LIBADD)
fi
