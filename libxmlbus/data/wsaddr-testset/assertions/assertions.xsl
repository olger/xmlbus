<?xml version="1.0"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:a="http://www.w3.org/2005/08/addressing/test-cases/assertions"
    version="1.0">

  <xsl:output method="html"
       encoding="utf-8"
       doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"
       indent="no"/>

    <xsl:template match="/">
    <html>
	<head>
	   <title>Web Services Addressing 1.0 - Test Assertions</title>
	  <link href="../testsuite.css" rel="stylesheet" type="text/css" />
	</head>
	<body>
       <h1>Web Services Addressing 1.0 - Test Assertions</h1>

	  <xsl:for-each select="a:assertions/a:assertion">
	    <div class="assertion {@level}">
                <a name="{@xml:id}"/>
		<a href="{@xml:id}"><xsl:value-of select="@xml:id" /></a> 
		(<b><xsl:value-of select="@level"/></b>)
		<div class="description">
		<p>
		    <blockquote><xsl:value-of select="a:text" /></blockquote>
		</p>
		<p>
		    <a href="{@doc}#{@section}"><xsl:value-of select="@doc" />#<xsl:value-of select="@section" /></a> 
		</p>
		<p>
		    <i><xsl:value-of select="a:note" /></i>
		</p>
		</div>
		<div class="tests">
		   <p><!-- TBD: Tests extracted from test cases which proport to exhibit the assertion --></p>
		</div>
	    </div>
	  </xsl:for-each>

<address>
  <a href="mailto:paul.downey@bt.com">Paul Downey</a><br/>
  Generated from <a href="assertions.xml">assertions.xml</a> using
  <a href="assertions.xsl">assertions.xsl</a>.<br/>
  <small>$Date: 2005/09/29 18:09:01 $</small>
</address>

<p class="copyright"><a rel="Copyright"
href="/Consortium/Legal/ipr-notice#Copyright">Copyright</a> © 2004-2005 <a
href="/"><acronym
title="World Wide Web Consortium">W3C</acronym></a><sup>®</sup> (<a
href="http://www.csail.mit.edu/"><acronym
title="Massachusetts Institute of Technology">MIT</acronym></a>, <a
href="http://www.ercim.org/"><acronym
title="European Research Consortium for Informatics and Mathematics">ERCIM</acronym></a>,
<a href="http://www.keio.ac.jp/">Keio</a>), All Rights Reserved. W3C <a
href="/Consortium/Legal/ipr-notice#Legal_Disclaimer">liability</a>, <a
href="/Consortium/Legal/ipr-notice#W3C_Trademarks">trademark</a>, <a
rel="Copyright" href="/Consortium/Legal/copyright-documents">document use</a>
and <a rel="Copyright" href="/Consortium/Legal/copyright-software">software
licensing</a> rules apply. Your interactions with this site are in accordance
with our <a href="/Consortium/Legal/privacy-statement#Public">public</a> and
<a href="/Consortium/Legal/privacy-statement#Members">Member</a> privacy
statements.</p>
	</body>
    </html>
    </xsl:template>

</xsl:stylesheet>
