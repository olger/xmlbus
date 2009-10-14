<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:a="http://www.w3.org/2002/ws/addr/testsuite/features/"
    xmlns:tc="http://www.w3.org/2002/ws/addr/testsuite/testcases/"
    version="1.0">

  <xsl:output method="html"
       encoding="utf-8"
       doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"
       indent="no"/>

    <xsl:template match="/">
    <html>
	<head>
	   <title>Web Services Addressing 1.0 - Testable Features</title>
	    <link href="http://www.w3.org/StyleSheets/public" rel="stylesheet" type="text/css"/>
	    <link href="../../../../StyleSheets/public" rel="stylesheet" type="text/css"/>
	    <link rel="stylesheet" type="text/css" href="../../../wsa-style.css"/>
	    <link rel="stylesheet" type="text/css" href="../../public-style.css"/>
	    <link href="../testsuite.css" rel="stylesheet" type="text/css" />
	</head>
	<body>
       <h1>Web Services Addressing 1.0 - Testable Features</h1>

	 <p><xsl:value-of select="a:features/a:description"/></p>

	 <ul>
	 <xsl:for-each select="a:features/a:feature">
	    <li>
		<a name="{@xml:id}"></a>
		<a href="#{@xml:id}"><xsl:value-of select="@xml:id"/></a>

	        - <xsl:value-of select="a:title"/> 
	        (<a href="http://www.w3.org/TR/2005/CR-ws-addr-{@document}-20050817/#{@section}">
		<xsl:value-of select="@document"/>/#<xsl:value-of select="@section"/></a>) 
	        - <xsl:value-of select="@cr"/> 

		{ <xsl:call-template name="cross-ref">
		    <xsl:with-param name="feature" select="@xml:id" />
		  </xsl:call-template>}

	      </li>
	 </xsl:for-each>
	 </ul>

    <hr/>
    <p>
      Generated from <a href="features.xml">features.xml</a> using
      <a href="features.xsl">features.xsl</a>.<br/>
      $Date: 2005/10/18 19:01:08 $
    </p>
    <xsl:copy-of select="document('../address.xml')/suffix/*"/>

	</body>
    </html>
</xsl:template>

    <xsl:template name="cross-ref">
	<xsl:param name="feature" />
	     <xsl:for-each select='document("../testcases/testcases.xml")/tc:testcases/tc:testcase/tc:features[tc:feature=$feature]/../@xml:id'>
			    
		<a href="../testcases/#{.}">
		    <xsl:value-of select="."/>
		</a>

		<xsl:text> </xsl:text>

	     </xsl:for-each>
    </xsl:template>

</xsl:stylesheet>
