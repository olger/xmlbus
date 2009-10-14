<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:log="http://www.w3.org/2002/ws/addressing/logs/" xmlns:testcases="http://www.w3.org/2002/ws/addr/testsuite/testcases/">
	<xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes"/>
	<xsl:variable name="testcases" select="document('../testcases/testcases.xml')"/>
	<xsl:template match="/">
		<xsl:processing-instruction name="xml-stylesheet">type="text/xsl" href="show-rollup.xsl"</xsl:processing-instruction>
		<summary>
			<title>
				<xsl:value-of select="test-rollup/name"/>
			</title>
			<xsl:apply-templates/>
		</summary>
	</xsl:template>
	<xsl:template match="test-rollup">
		<xsl:variable name="rollup" select="."/>
		<xsl:copy-of select="participants"/>
		<vendors>
			<xsl:for-each select="$rollup/log">
				<xsl:sort select="@server" order="ascending"/>
				<xsl:sort select="@client" order="ascending"/>
				<vendor index="{position()}" client="{@client}" server="{@server}" href="{@href}"/>
			</xsl:for-each>
		</vendors>
		<required>
			<xsl:apply-templates select="$testcases/testcases:testcases/testcases:testcase[@cr='REQUIRED']">
				<xsl:with-param name="rollup" select="$rollup"/>
			</xsl:apply-templates>
		</required>
		<optional>
			<xsl:apply-templates select="$testcases/testcases:testcases/testcases:testcase[@cr='OPTIONAL']">
				<xsl:with-param name="rollup" select="$rollup"/>
			</xsl:apply-templates>
		</optional>
		<informational>
			<xsl:apply-templates select="$testcases/testcases:testcases/testcases:testcase[@cr='INFORMATIONAL']">
				<xsl:with-param name="rollup" select="$rollup"/>
			</xsl:apply-templates>
		</informational>
	</xsl:template>
	<xsl:template match="testcases:testcase">
		<testcase id="{@xml:id}" href="http://www.w3.org/2002/ws/addr/testsuite/testcases/#{@xml:id}" type="{@cr}">
			<xsl:variable name="testcase-id" select="@xml:id"/>
			<xsl:for-each select="$rollup/log">
				<xsl:sort select="@server" order="ascending"/>
				<xsl:sort select="@client" order="ascending"/>
				<result index="{position()}" href="{@results}">
					<xsl:choose>
						<xsl:when test="document(@results)">
							<xsl:if test="document(@href)/log:log/log:message[@testcase=$testcase-id]">
								<xsl:variable name="assertion" select="document(@results)/results/assertion[@against=$testcase-id]"/>
								<xsl:choose>
									<xsl:when test="$assertion">failed</xsl:when>
									<xsl:otherwise>passed</xsl:otherwise>
								</xsl:choose>
							</xsl:if>
						</xsl:when>
						<xsl:otherwise>badlog</xsl:otherwise>
					</xsl:choose>
				</result>
			</xsl:for-each>
		</testcase>
	</xsl:template>
</xsl:stylesheet>
