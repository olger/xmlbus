# Tired to inserting MessageID and RelatesTo in the examples?
# Try running this

use strict;
use XML::Dom;

my $testcases = '../../testcases/testcases.xml';
my $parser = new XML::DOM::Parser;
my $doc = $parser->parsefile($testcases);
my $nodes = $doc->getElementsByTagName('message-exchange');

my $n = $nodes->getLength();

my @docs;

for (my $i = 0; $i < $n; $i++) {
    my $node = $nodes->item($i);
    my @messages;
    my $nc = $node->getChildNodes();
    my $nnc = $nc->getLength();
    for (my $j = 0; $j < $nnc; $j++) {
      my $m = $nc->item($j);
      if ($m->getNodeType() == 1 && $m->getNodeName() eq "message") {
	my $d = $m->getAttributeNode('document');
	push(@messages, $d->getValue());
      }
    }
    if ($#messages == 1) {
      push(@docs, @messages);
    }
}


# Check for duplicates
my $i = 0;
my $errors = 0;
my %responses;
while ($i < $#docs) {
  $i++;
  if (! $responses{$docs[$i]}) {
    $responses{$docs[$i]} = 1;
  } else {
    printf("Error: duplicate %s\n", $docs[$i]);
    $errors++;
  }
  $i++;
}

if ($errors > 0) {
  exit(1);
}

sub genUniqueHeader() {
  my ($filename, $name, $value) = @_;

  my $parser = new XML::DOM::Parser;
  my $doc = $parser->parsefile($filename);
  my $nodes = $doc->getElementsByTagName($name);
  my $l = $nodes->getLength();
  if ($l > 1) {
    # Skip duplicate MID message
    return '';
  }
  my $mid = $doc->createElement($name);
  my $textnode = $doc->createTextNode($value);
  my $l = $nodes->getLength();
  $mid->appendChild($textnode);
  my $hnodes = $doc->getElementsByTagName('env:Header');
  if ($hnodes->getLength() == 0) {
    $hnodes = $doc->getElementsByTagName('soap11:Header');
  }
  if ($hnodes->getLength() == 0) {
    $hnodes = $doc->getElementsByTagName('soap12:Header');
  }
  if ($hnodes->getLength() == 0) {
    print "Ouch, what were you thinking when you started using a DOM Level 1 module, Hugo?!\n";
    exit(2);
  }
  my $header = $hnodes->item(0);
  if ($l == 1) {
    my $oldmid = $nodes->item(0);
    $header->replaceChild($mid, $oldmid);
  } else {
    $header->appendChild($mid);
    my $textnode = $doc->createTextNode("\n");
    $header->appendChild($textnode);
  }
  return $doc->toString();
}

sub save() {
  my ($fn, $s) = @_;

  # Don't touch the mustUnderstand stuff!
  if ($fn eq '../notify/soap12/fault5.xml') {
    print "U-turn! Don't touch this one!\n";
    return;
  }

  open(F, "> $fn");
  print F $s;
  close(F);
}

# Generate message ids
my $i = 0;
while ($i < $#docs) {
  my $filename = "../$docs[$i++]";
  print "$filename\n";
  my $uuidgen = "urn:uuid:" . `uuidgen`;
  chomp($uuidgen);
  my $out = &genUniqueHeader($filename, "wsa:MessageID", $uuidgen);
  if ($out eq '') {
    # Skipping duplicate ID test
    $i++;
    next;
  }
  &save($filename, $out);
  $filename = "../$docs[$i]";
  print "$filename\n";
  &save($filename, &genUniqueHeader($filename, "wsa:RelatesTo", $uuidgen));
  $uuidgen = "urn:uuid:" . `uuidgen`;
  chomp($uuidgen);
  &save($filename, &genUniqueHeader($filename, "wsa:MessageID", $uuidgen));
  $i++;
}
