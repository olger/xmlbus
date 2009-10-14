<?xml version="1.0" encoding="UTF-8"?>
<!--
    Generate a Schematron Schema to check a log from testcases

    $Header: /w3ccvs/WWW/2002/ws/addr/testsuite/observer/mkschema.xsl,v 1.10 2006/03/02 16:57:39 jonathanMarsh Exp $
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:s="http://www.w3.org/2002/ws/addr/testsuite/testcases/" version="1.0">
	<xsl:output method="xml" encoding="utf-8" indent="yes"/>
	<xsl:template match="/">
		<sch:schema xmlns:sch="http://www.ascc.net/xml/schematron">
			<xsl:for-each select="//s:ns">
				<sch:ns prefix="{@prefix}" uri="{@uri}"/>
			</xsl:for-each>
			<sch:pattern name="message">
				<sch:rule context="log:message">
					<sch:assert test="@testcase">message missing testcase attribute</sch:assert>
					<sch:assert test="@message">message missing message attribute</sch:assert>
				</sch:rule>
			</sch:pattern>
			<xsl:for-each select="s:testcases/s:testcase">
				<xsl:variable name="testcase">
					<xsl:value-of select="@xml:id"/>
				</xsl:variable>
				<sch:pattern name="{$testcase}">
					<xsl:for-each select="s:message-exchange/s:message">
						<xsl:variable name="num" select="position()"/>
						<xsl:if test="$num!=1 and count(s:assert)>0">
							<sch:rule context="log:message[@testcase='{$testcase}'][@message='1']">
								<sch:assert test="following-sibling::log:message[@testcase='{$testcase}'][@message='{$num}']">assertion "all required messages present" against <xsl:value-of select="$testcase"/> message <xsl:value-of select="$num"/> failed</sch:assert>
							</sch:rule>
						</xsl:if>
						<xsl:if test="s:assert">
							<sch:rule context="log:message[@testcase='{$testcase}'][@message='{$num}']/log:content">
								<xsl:for-each select="s:assert">
									<xsl:variable name="test">
										<xsl:choose>
											<xsl:when test="@qname">resolve-QName(<xsl:value-of select="@test"/>, <xsl:value-of select="@test"/>) = <xsl:value-of select="@qname"/>
											</xsl:when>
											<xsl:otherwise>
												<xsl:value-of select="@test"/>
											</xsl:otherwise>
										</xsl:choose>
									</xsl:variable>
									<sch:assert test="{$test}">assertion "<xsl:value-of select="$test"/>" against <xsl:value-of select="$testcase"/> message <xsl:value-of select="$num"/> failed</sch:assert>
								</xsl:for-each>
							</sch:rule>
						</xsl:if>
					</xsl:for-each>
				</sch:pattern>
			</xsl:for-each>
		</sch:schema>
	</xsl:template>
</xsl:stylesheet>
