<?xml version="1.0"?>
<!--
    Generate example log file format from testcases

    $Header: /w3ccvs/WWW/2002/ws/addr/testsuite/logs/example.xsl,v 1.2 2006/02/21 18:07:53 pdowney Exp $
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:s="http://www.w3.org/2002/ws/addr/testsuite/testcases/"
  version="1.0">

  <xsl:output method="xml" encoding="utf-8" indent="yes"/>

  <xsl:template match="/">
<log xmlns="http://www.w3.org/2002/ws/addressing/logs/">
    <xsl:for-each select="s:testcases/s:testcase">

      <xsl:variable name="context">
        <xsl:number count="*" format="1"/>
      </xsl:variable>

      <xsl:for-each select="s:message-exchange/s:message">

	<xsl:variable name="number">
	    <xsl:number count="*" format="1"/>
	</xsl:variable>

	<xsl:choose>
	<xsl:when test="@name">

	<message testcase="{../../@xml:id}" message="{$number}" context="{$context}">
	   <xsl:variable name="file">../documents/<xsl:value-of select="./@document"/></xsl:variable>
           <!-- http://www.xml.com/pub/a/2003/08/20/embedded.html -->
	   <content href="{$file}" ><xsl:copy-of select="document($file)"/></content>
	</message>
	</xsl:when>

	</xsl:choose>
	
      </xsl:for-each>
    </xsl:for-each>

</log>
  </xsl:template>
</xsl:stylesheet>
