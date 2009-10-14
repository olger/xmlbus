#
#  Perl index of logfiles 
#  TBD - collapse with logs.xml and rollup.xml ..
#
#  $Header: /w3ccvs/WWW/2002/ws/addr/testsuite/report/logs.pm,v 1.24 2006/03/16 21:48:09 pdowney Exp $

package logs;

our %vendor = 
(
    Axis => 
    {
	# looks like a clone of other people's logs ..
	dir => 'http://webservices.sonicsw.com:8080/interop/logs/',
    },
    IBM => 
    {
	dir => 'http://wsaiop:IBML0GS@85.8.130.43/wsaiop/',
        format => 'wsi',
    },
    JBoss => 
    {
	dir => 'http://213.162.124.157:8080/interop/logs/',
    },
    Microsoft => 
    {
	dir => 'http://131.107.72.15/wsalogs/',
    },
    Sun =>
    {
	dir => 'http://soapinterop.java.sun.com:8080/wsalogs/',
        format => 'wsi',
    },
    WSO2 => 
    {
	# copy of logs available elsewhere, no WSO2 client, as yet?!
	dir => 'http://www-lk.wso2.com/~dims/wsalogs/',	
        format => 'wsi',
    },
);

our @files = 
(
    # IBM client
    {
	source => 'IBM',
	client => 'IBM',
	server => 'Axis',
	link => 'ibm-apache.xml',
    },
    {
	source => 'IBM',
	client => 'IBM',
	server => 'IBM',
 	link => 'ibm-ibm.xml',
    },
    {
	source => 'IBM',
	client => 'IBM',
	server => 'JBoss',
 	link => 'ibm-jboss.xml',
    },
    {
	source => 'IBM',
	client => 'IBM',
	server => 'Microsoft',
	link => 'ibm-ms.xml',
    },
    {
	source => 'IBM',
	client => 'IBM',
	server => 'Sun',
 	link => 'ibm-sun.xml',
    },
    {
	source => 'WSO2',	# WSO2 source!
	client => 'IBM',
	server => 'WSO2',
	link => 'ibm-wso2.xml',
    },


    # JBoss client
    {
	source => 'JBoss',
	client => 'JBoss',
	server => 'Axis',
 	link => 'jboss-apache.xml',
    },
    {
	source => 'JBoss',
	client => 'JBoss',
	server => 'IBM',
 	link => 'jboss-ibm.xml',
    },
    {
	source => 'JBoss',
	client => 'JBoss',
	server => 'JBoss',
 	link => 'jboss-jboss.xml',
    },
    {
	source => 'JBoss',
	client => 'JBoss',
	server => 'Microsoft',
 	link => 'jboss-msft.xml',
    },
    {
	source => 'JBoss',
	client => 'JBoss',
	server => 'Sun',
 	link => 'jboss-sun.xml',
    },
    {
	source => 'JBoss',
	client => 'JBoss',
	server => 'WSO2',
 	link => 'jboss-wso2.xml',
    },

    # Microsoft client
    {
	source => 'Microsoft',
	client => 'Microsoft',
	server => 'Axis',
 	link => 'wcf-client-axis-service-log.xml',
    },
    {
	source => 'Microsoft',
	client => 'Microsoft',
	server => 'IBM',
 	link => 'wcf-client-ibm-service-log.xml',
    },
    {
	source => 'Microsoft',
	client => 'Microsoft',
	server => 'JBoss',
 	link => 'wcf-client-jboss-service-log.xml',
    },
    {
	source => 'Microsoft',
	client => 'Microsoft',
	server => 'Microsoft',
 	link => 'wcf-client-wcf-service-log.xml',
    },
    {
	source => 'Microsoft',
	client => 'Microsoft',
	server => 'Sun',
 	link => 'wcf-client-sun-service-log.xml',
    },
    {
	source => 'Microsoft',
	client => 'Microsoft',
	server => 'WSO2',
	link => 'wcf-client-wso2-service-log.xml',
    },


    # Sun client
    {
	source => 'IBM',
	client => 'Sun',
	server => 'Axis',
 	#link => 'Sun-Axis.xml',
 	link => 'sun-apache.xml',
    },
    {
	source => 'IBM',
	client => 'Sun',
	server => 'IBM',
 	link => 'sun-ibm.xml',
    },
    {
	source => 'IBM',
	client => 'Sun',
	server => 'JBoss',
 	#link => 'Sun-JBoss.xml',
 	link => 'sun-jboss.xml',
	format => 'wsi',
    },
    {
	source => 'IBM',
	client => 'Sun',
	server => 'Microsoft',
 	#link => 'Sun-Microsoft.xml',
 	link => 'sun-ms.xml',
    },
    {
	source => 'Sun',
	client => 'Sun',
	server => 'Sun',
 	link => 'Sun-Sun.xml',
    },
    {
	source => 'WSO2',
	client => 'Sun',
	server => 'WSO2',
	link => 'sun-wso2.xml',
    },

    # WSO2 client
    {
	source => 'WSO2',
	client => 'WSO2',
	server => 'Axis',
	link => 'wso2-axis.xml',
    },
    {
	source => 'WSO2',
	client => 'WSO2',
	server => 'IBM',
	link => 'wso2-ibm.xml',
    },
    {
	source => 'WSO2',
	client => 'WSO2',
	server => 'JBoss',
	link => 'wso2-jboss.xml',
    },
    {
	source => 'WSO2',
	client => 'WSO2',
	server => 'Microsoft',
	link => 'wso2-msft.xml',
    },
    {
	source => 'WSO2',
	client => 'WSO2',
	server => 'Sun',
	link => 'wso2-sun.xml', 
    },
    {
	source => 'WSO2',
	client => 'WSO2',
	server => 'WSO2',
	link => 'wso2-wso2.xml', 
    },
);


#
#  munge global array, ugh!
#
foreach my $n (@files)
{
    my $source = $n->{source};
    my $client = $n->{client};
    my $server = $n->{server};
    my $opt = $n->{opt} || "";

    my $link = $logs::vendor{$source}->{dir} . $n->{link};
    my $name = "$source-$client-$server$opt";

    $n->{name} = $name;
    $n->{href} = $link;
    $n->{file} = "$name.xml";
    $n->{format} = $n->{format} || $logs::vendor{$source}->{format} || "";
    $n->{raw} = "$name-raw.xml";
    $n->{tmp} = "$name-tmp.xml";
    $n->{tmp0} = "$name-tmp0.xml";
    $n->{tmp1} = "$name-tmp1.xml";
    $n->{tmp1a} = "$name-tmp1a.xml";
    $n->{tmp2} = "$name-tmp2.xml";
    $n->{tmp3} = "$name-tmp3.xml";
    $n->{results} = "$name-results.xml";
}

1;
