AC_DEFUN([XMLBUS_REQUIRE_LIBXML2],[
dnl the with argument can give an optional location
AC_ARG_WITH(libxml2, [  --with-libxml2=DIR	specify where libxml2 library is found. Without this option it will look in the default places])

if test "x$with_libxml2" = "x" ; then
	XML2_CONFIG_PREFIX=$with_libxml2
fi

for dir in $with_libxml2/bin64 /usr/bin64 /usr/local/bin64 $with_libxml2/bin /usr/bin /usr/local/bin; do
	if test -f "$dir/xml2-config"; then
		XML_CONFIG="$dir/xml2-config"
		break;
	fi
done

dnl not found in the given paths, try to see if it is in the user environment
if test "x$XML2_CONFIG" = "x"
then
  XML_CONFIG=xml2-config
fi

XMLVERS=`$XML_CONFIG --version`
if test x"${XMLVERS}" != "x"
then
 AC_MSG_RESULT(libxml2 $XMLVERS found)
 XML2_LIBS="$XML2_LIBS `$XML_CONFIG --libs`"
 XML2_CFLAGS="$XML2_CFLAGS `$XML_CONFIG --cflags`"
else
 AC_MSG_ERROR([Could not find libxml2 anywhere, check ftp://xmlsoft.org/.])
fi

AC_SUBST(XML2_LIBS)
AC_SUBST(XML2_CFLAGS)
])
