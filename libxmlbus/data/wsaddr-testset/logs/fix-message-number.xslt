<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:log="http://www.w3.org/2002/ws/addressing/logs/" xmlns:soapenv="http://schemas.xmlsoap.org/soap/envelope/">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
	<xsl:template match="* | comment()">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	<xsl:template match="log:message">
				<xsl:copy>
					<xsl:apply-templates select="@*"/>
					<xsl:attribute name="message"><xsl:value-of select="count(preceding-sibling::log:message[@testcase=current()/@testcase])+1"/></xsl:attribute>
					<xsl:apply-templates/>
				</xsl:copy>
	</xsl:template>
	<xsl:template match="@*">
		<xsl:copy-of select="."/>
	</xsl:template>
</xsl:stylesheet>
