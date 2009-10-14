<?xml version="1.0" encoding="UTF-8"?>
<!--

    $Header: /w3ccvs/WWW/2002/ws/addr/testsuite/logs/ws-i/ws-i.xsl,v 1.6 2006/02/21 19:42:55 pdowney Exp $

    Convert WS-I Monitor file into WS-Addressing Log file

-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:wsi-log303="http://www.ws-i.org/testing/2003/03/log/" xmlns:wsi-log407="http://www.ws-i.org/testing/2004/07/log/">
	<xsl:output method="xml" indent="yes"/>
	<xsl:variable name="bom">&lt;?xml</xsl:variable>
	<xsl:variable name="gone">&lt;?_xml</xsl:variable>
	<xsl:template match="wsi-log303:log">
		<l:log xmlns:l="http://www.w3.org/2002/ws/addressing/logs/">
			<xsl:for-each select="//wsi-log303:messageEntry">
				<xsl:variable name="content">
					<xsl:call-template name="replace">
						<xsl:with-param name="text" select="wsi-log303:messageContent"/>
						<xsl:with-param name="replace" select="$bom"/>
						<xsl:with-param name="with" select="$gone"/>
						<xsl:with-param name="disable-output-escaping" select="yes"/>
					</xsl:call-template>
				</xsl:variable>
				<l:message timestamp="{@timestamp}" conversation="{@conversationID}" wsi-log303:ID="{@ID}" type="{@type}">
					<l:content>
						<xsl:value-of select="$content" disable-output-escaping="yes"/>
					</l:content>
					<xsl:copy-of select="wsi-log303:senderHostAndPort"/>
					<xsl:copy-of select="wsi-log303:receiverHostAndPort"/>
					<xsl:copy-of select="wsi-log303:httpHeaders"/>
				</l:message>
			</xsl:for-each>
		</l:log>
	</xsl:template>
	<xsl:template match="wsi-log407:log">
		<l:log xmlns:l="http://www.w3.org/2002/ws/addressing/logs/">
			<xsl:for-each select="//wsi-log407:messageEntry">
				<xsl:variable name="content">
					<xsl:call-template name="replace">
						<xsl:with-param name="text" select="wsi-log407:messageContent"/>
						<xsl:with-param name="replace" select="$bom"/>
						<xsl:with-param name="with" select="$gone"/>
						<xsl:with-param name="disable-output-escaping" select="yes"/>
					</xsl:call-template>
				</xsl:variable>
				<l:message timestamp="{@timestamp}" conversation="{@conversationID}" wsi-log407:ID="{@ID}" type="{@type}">
					<l:content>
						<xsl:value-of select="$content" disable-output-escaping="yes"/>
					</l:content>
					<xsl:copy-of select="wsi-log407:senderHostAndPort"/>
					<xsl:copy-of select="wsi-log407:receiverHostAndPort"/>
					<xsl:copy-of select="wsi-log407:httpHeaders"/>
				</l:message>
			</xsl:for-each>
		</l:log>
	</xsl:template>
	<!-- http://xsltsl.sourceforge.net/ -->
	<xsl:template name="replace">
		<xsl:param name="text"/>
		<xsl:param name="replace"/>
		<xsl:param name="with"/>
		<xsl:param name="disable-output-escaping">no</xsl:param>
		<xsl:choose>
			<xsl:when test="string-length($replace) = 0 and $disable-output-escaping = 'yes'">
				<xsl:value-of select="$text" disable-output-escaping="yes"/>
			</xsl:when>
			<xsl:when test="string-length($replace) = 0">
				<xsl:value-of select="$text"/>
			</xsl:when>
			<xsl:when test="contains($text, $replace)">
				<xsl:variable name="before" select="substring-before($text, $replace)"/>
				<xsl:variable name="after" select="substring-after($text, $replace)"/>
				<xsl:choose>
					<xsl:when test='$disable-output-escaping = "yes"'>
						<xsl:value-of select="$before" disable-output-escaping="yes"/>
						<xsl:value-of select="$with" disable-output-escaping="yes"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="$before"/>
						<xsl:value-of select="$with"/>
					</xsl:otherwise>
				</xsl:choose>
				<xsl:call-template name="replace">
					<xsl:with-param name="text" select="$after"/>
					<xsl:with-param name="replace" select="$replace"/>
					<xsl:with-param name="with" select="$with"/>
					<xsl:with-param name="disable-output-escaping" select="$disable-output-escaping"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:when test='$disable-output-escaping = "yes"'>
				<xsl:value-of select="$text" disable-output-escaping="yes"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$text"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
</xsl:stylesheet>
