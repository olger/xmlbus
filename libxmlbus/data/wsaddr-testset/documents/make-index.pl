#! /usr/bin/env perl

use strict;

print <<EOF;
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html xmlns:s=
"http://www.w3.org/2002/ws/addr/testsuite/testcases/">
<head>
<meta name="generator" content=
"HTML Tidy for Mac OS X (vers 12 April 2005), see www.w3.org">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Web Services Addressing 1.0 - Test Documents</title>
<link href="../testsuite.css" rel="stylesheet" type="text/css">
</head>
<body>
<h1>Web Services Addressing 1.0 - Test Documents</h1>
EOF

my @files = ();

print "<ul>";
foreach my $file (`find . -name \*xml -o -name \*wsdl`)
{
    chomp($file);
    $file =~ s/^\.\///;
    push(@files, $file);
    print "<li><a href='#$file'>$file</a></li>\n";
}
print "</ul>";

print "<ul>";
foreach my $file (@files)
{
    chomp($file);
    $file =~ s/^\.\///;
    print "<li><a name='$file'/><a href='$file'>$file</a></p>\n";
    print "<pre>";

    my $text = do { local(@ARGV, $/) = $file; <> };

    $text =~ s/&/&amp;/g;
    $text =~ s/</&lt;/g;
    $text =~ s/>/&gt;/g;
    $text =~ s/\$/&#36;/g;

    print $text;

    print "</pre></li>\n";
}

my $address = do { local(@ARGV, $/) = '../address.xml'; <> };
$address =~ s/<\/?suffix>//g;

print <<EOF;
</ul>
<hr>
<p>Generated using <a href="make-index.pl">make-index.pl</a>.<br>
\$Date: 2005/11/01 17:35:28 $</p>
$address
</body>
</html>
EOF

exit(0);
