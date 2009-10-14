#!/usr/bin/perl -w

#
#  generate logs.xml from logs.pm
#

use strict;

use logs;

{
    print <<EOF;
<?xml version="1.0"?>
<!-- 
    Web Services Addressing Logs
    \$Header\$
-->

<logs xmlns="http://www.w3.org/2002/ws/addr/testsuite/logs/">
    <participants>
EOF

    foreach my $vendor (sort keys %logs::vendor)
    {
	print "        <participant>$vendor</participant>\n";
    }

    print <<EOF;
    </participants>
EOF

    foreach my $n (@logs::files)
    {
	my $name = $n->{name};
	my $source = $n->{source};
	my $file = $n->{file};
	my $client = $n->{client};
	my $server = $n->{server};
	my $format = $n->{format};
	my $raw = $n->{raw};
	my $tmp = $n->{tmp};
	my $tmp1 = $n->{tmp1};
	my $results = $n->{results};


	print <<EOF;
        <log xml:id="$name" file="../report/$file" source="$source" client="$client" server="$server">
	    <title>$source capture from $client to $server.</title>
	</log>

EOF
    }

    print <<EOF;

  <log xml:id="example" file="example.xml">
    <title>log file generated from <a href="../testcases/">testcases</a> and example <a href="../documents/">documents</a>.</title>
  </log>

  <log xml:id="example-ws-i" file="example-ws-i.xml">
    <title>log file generated from an example WS-I Monitor log file using a <a href="ws-i/ws-i.xsl">stylesheet</a></title>
  </log>

</logs>
EOF

}

exit (0);
