<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:log="http://www.w3.org/2002/ws/addressing/logs/" xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
	<xsl:template match="* | comment()">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	<xsl:template match="log:message[@type='request']">
		<xsl:copy>
			<xsl:call-template name="testcase-attribute"/>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	<xsl:template match="log:message[@type='response']">
		<xsl:copy>
			<xsl:for-each select="preceding-sibling::log:message[1][@type='request']">
				<xsl:call-template name="testcase-attribute"/>
			</xsl:for-each>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	<xsl:template name="testcase-attribute">
		<xsl:variable name="testname" select="translate(.//*[local-name()='Body'],'TESFAUL','tesfaul')"/>
		<xsl:attribute name="testcase"><xsl:choose><xsl:when test="starts-with($testname,'fault-')"><xsl:value-of select="substring-after($testname,'fault-')"/></xsl:when><xsl:when test="starts-with($testname,'fault')"><xsl:value-of select="substring-after($testname,'fault')"/></xsl:when><xsl:otherwise><xsl:value-of select="$testname"/></xsl:otherwise></xsl:choose></xsl:attribute>
	</xsl:template>
	<xsl:template match="@*">
		<xsl:copy-of select="."/>
	</xsl:template>
</xsl:stylesheet>
