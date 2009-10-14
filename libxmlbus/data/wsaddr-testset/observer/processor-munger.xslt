<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
	<xsl:template match="@*">
		<xsl:copy-of select="."/>
	</xsl:template>
	<xsl:template match="*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates select="node()"/>
		</xsl:copy>
	</xsl:template>
	<xsl:template match="xsl:stylesheet">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:element name="xsl:output" namespace="http://www.w3.org/1999/XSL/Transform">
			  <xsl:attribute name="indent">yes</xsl:attribute>
			</xsl:element>
			<xsl:apply-templates select="node()"/>
		</xsl:copy>
	</xsl:template>
	<xsl:template match="xsl:template[@match='/']">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<results>
				<xsl:apply-templates select="node()"/>
			</results>
		</xsl:copy>
	</xsl:template>
	<xsl:template match="xsl:otherwise[starts-with(.,'assertion')]">
		<xsl:element name="xsl:otherwise" namespace="http://www.w3.org/1999/XSL/Transform">
			<xsl:apply-templates select="@*"/>
			<assertion xpath="{substring-before(substring-after(.,'assertion &quot;'),'&quot;')}" against="{substring-before(substring-after(.,'against '),' ')}" message="{substring-before(substring-after(.,'message '),' ')}" result="failed"/>
		</xsl:element>
	</xsl:template>
</xsl:stylesheet>
