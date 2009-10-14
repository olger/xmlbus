AC_DEFUN([XMLBUS_REQUIRE_DNSSD],[
dnl the with argument can give an optional location
AC_ARG_WITH(dnssd, [  --with-dnssd=DIR	specify where dsnsd library is found. It needs the bonjour (compatible) dns_sd.h api to work with. Without this option it will look in the default places])

if test "x$with_dnssd" = "x" ; then
	DNSSD_CONFIG_PREFIX=$with_dnssd
fi

for dir in $with_dnssd/include /usr/include /usr/local/include; do
	if test -f "$dir/dns_sd.h"; then
		DNSSD_INCLUDE="$dir"
		break;
	fi
done

for dir in $with_dnssd/lib $with_dnssd/lib64 /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64; do
	if test -f "$dir/dns_sd.so"; then
		DNSSD_LIB="$dir"
		break;
	fi
done

if test "x$DNSSD_INCLUDE" != "x"
then
 AC_MSG_RESULT(dnssd found at $DNSSD_LIB)
 DNSSD_LIBS="$DNSSD_LIBS -L$DNSSD_LIB -ldns_sd"
 DNSSD_CFLAGS="$DNSSD_CFLAGS -I $DNSSD_INCLUDE"
else
 AC_MSG_ERROR([Could not find dnssd library anywhere, check for avahi or bonjour package.])
fi

AC_SUBST(DNSSD_LIBS)
AC_SUBST(DNSSD_CFLAGS)
])
