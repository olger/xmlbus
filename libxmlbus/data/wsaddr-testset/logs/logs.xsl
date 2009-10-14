<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:l="http://www.w3.org/2002/ws/addr/testsuite/logs/"
    xmlns:tc="http://www.w3.org/2002/ws/addr/testsuite/testcases/"
    version="1.0">

  <xsl:output method="html"
       encoding="utf-8"
       doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"
       indent="no"/>

    <xsl:template match="/">
    <html>
	<head>
	   <title>Web Services Addressing 1.0 - Captured Log Files</title>
	    <link href="http://www.w3.org/StyleSheets/public" rel="stylesheet" type="text/css"/>
	    <link href="../../../../StyleSheets/public" rel="stylesheet" type="text/css"/>
	    <link rel="stylesheet" type="text/css" href="../../../wsa-style.css"/>
	    <link rel="stylesheet" type="text/css" href="../../public-style.css"/>
	    <link href="../testsuite.css" rel="stylesheet" type="text/css" />
	</head>
	<body>
       <h1>Web Services Addressing 1.0 - Captured Log Files</h1>

	 <ul>
	 <xsl:for-each select="l:logs/l:log">
	    <li>
		<a name="{@xml:id}"></a>
		<a href="{@file}"><xsl:value-of select="@file"/></a>
	        - <xsl:copy-of select="l:title/node()"/> 
	      </li>
	 </xsl:for-each>
	 </ul>

    <hr/>
    <p>
      Generated from <a href="../report/logs.xml">logs.xml</a> using
      <a href="logs.xsl">logs.xsl</a>.<br/>
      $Date: 2006/01/27 17:12:41 $
    </p>
    <xsl:copy-of select="document('../address.xml')/suffix/*"/>

	</body>
    </html>
</xsl:template>
</xsl:stylesheet>
