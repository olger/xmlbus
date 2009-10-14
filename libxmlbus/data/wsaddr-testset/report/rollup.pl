#!/usr/bin/perl -w
#
#  build rollup.xml - an index of logfiles 
#

use Time::Local;
use File::stat;
use strict;
use logs;

{
    my $date = gmtime() . " UTC";

    open(FILE, "> rollup.xml");

    print FILE <<EOF;
<?xml version="1.0" encoding="UTF-8"?>
<?xml-stylesheet type="text/xsl" href="rollup.xslt"?>
<test-rollup>
    <name>WS-Addressing Test Results, $date</name>
    <participants>
EOF

    foreach my $vendor (sort keys %logs::vendor)
    {
	print FILE "        <vendor>$vendor</vendor>\n";
    }

    print FILE <<EOF;
    </participants>
EOF

    foreach my $n (@logs::files)
    {
	my $source = $n->{source};
	my $file = $n->{file};
	my $client = $n->{client};
	my $server = $n->{server};
	my $format = $n->{format};
	my $raw = $n->{raw};
	my $tmp = $n->{tmp};
	my $tmp0 = $n->{tmp0};
	my $tmp1 = $n->{tmp1};
	my $tmp1a = $n->{tmp1a};
	my $tmp2 = $n->{tmp2};
	my $tmp3 = $n->{tmp3};
	my $results = $n->{results};

	#  only build it raw is newer than results
	#
	    print  "$results :\n";
	if ((!-f $results) || (stat($raw)->mtime > stat($results)->mtime))
	{
	    `sed -e 's/xmlns:xml=.http:..www.w3.org.XML.1998.namespace.//g' < $raw > $tmp0`;

	    if ($format =~ /wsi/) 
	    {
		print  "  running ws-i.xsl on $raw ..\n";
		`xsltproc --stringparam file :w.xml ../logs/ws-i/ws-i.xsl $tmp0 > $tmp1`;

		print  "  running ws-i-sort.xsl on $tmp1 ..\n";
		`xsltproc --stringparam file :w.xml ../logs/ws-i/ws-i-sort.xsl $tmp1 > $tmp1a`;

		print  "  running add-testcase.xslt on $tmp1a ..\n";
		`xsltproc --stringparam file :w.xml ../logs/add-testcase.xslt $tmp1a > $tmp2`;

		print  "  running fix-message-number.xslt on $tmp2 ..\n";
		`xsltproc --stringparam file :w.xml ../logs/fix-message-number.xslt $tmp2 > $tmp`;

	    }
	    else
	    {
	       `cp $tmp0 $tmp`;
	    }

	    # munge logs
	    `sed -e 's/<?xml-stylesheet.*?>//'  -e 's/Application Server\\/7.0/WSAddressing Implementation/' -e 's/WebSphere/IBM/g' < $tmp > $file`;

	     print  "  processing $file to $results..\n";
	    `../observer/processor.sh $file > "$results"`;

	    `rm -f $tmp $tmp1 $tmp1a $tmp2 $tmp3`;
	 }

	print FILE <<EOF;
	<log href="$file" results="$results" source="$source" client="$client" server="$server"/>
EOF
    }

    print FILE <<EOF;
</test-rollup>
EOF

    close(FILE);
}

print "done\n";
exit (0);
