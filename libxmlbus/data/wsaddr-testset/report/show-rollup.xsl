<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
 xmlns:log="http://www.w3.org/2002/ws/addressing/logs/" exclude-result-prefixes="log">
	<xsl:import href="xml-to-string.xsl"/>
	<xsl:output method="html" version="1.0" encoding="UTF-8" indent="yes"/>
	<xsl:param name="show-logs" select="'yes'"/>
	<xsl:variable name="summary" select="/summary"/>
	<xsl:variable name="overrides" select="document('overrides.xml')"/>
	<xsl:template match="/">
		<html>
			<head>
				<title>
					<xsl:value-of select="summary/title"/>
				</title>
				<style type="text/css">
					body {font-face:Ariel}
					.passed {background-color:#99cc99; text-align:center}
					.passed-override {background-color:#77aa77; text-align:center}
					.badlog {background-color:#ff9999; text-align:center}
					.failed {background-color:#ff9999; text-align:center}
					.failed-override {background-color:#dd7777; text-align:center}
					.na-override {background-color:#dddddd; text-align:center}
					pre {margin-before:.3em; margin-after:.3em; margin-left:1em}
				</style>
			</head>
			<body>
				<h1>
					<xsl:value-of select="summary/title"/>
				</h1>
				<xsl:apply-templates/>
				<p>Generated using <a href="show-rollup.xsl">show-rollup.xsl</a>.<br/>
				  $Date: 2006/03/17 01:12:03 $</p>
				<xsl:copy-of select="document('../address.xml')/suffix/*"/>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="summary">
		<h3>At a glance:</h3>
		<table>
			<thead>
				<tr>
					<th bgcolor="lightgrey">Required tests</th>
					<th bgcolor="lightgrey">Optional tests</th>
				</tr>
			</thead>
			<tbody>
				<tr>
					<td style="border:1px solid black">
						<xsl:variable name="done-required" select="document('cr-complete.xml')/vendors/required"/>
						<table cellpadding="0" cellspacing="2">
							<thead>
								<tr>
									<th>Client/Server</th>
									<xsl:for-each select="participants/vendor">
										<th>
											<xsl:value-of select="."/>
										</th>
									</xsl:for-each>
								</tr>
							</thead>
							<tbody>
								<xsl:for-each select="participants/vendor">
									<xsl:variable name="this-client" select="."/>
									<tr>
										<th align="right">
											<xsl:value-of select="."/>&#160; 
										</th>
										<xsl:for-each select="../vendor">
											<xsl:variable name="this-service" select="."/>
											<td style="border:2px solid white">
												<xsl:if test=". != $this-client and $done-required[vendor=$this-client][vendor=current()]">
													<xsl:attribute name="style">border:2px solid orange</xsl:attribute>
												</xsl:if>
												<xsl:variable name="index" select="/summary/vendors/vendor[@client=$this-client][@server=$this-service]/@index"/>
												<xsl:for-each select="$index">
													<xsl:variable name="numtests" select="count(/summary/required/testcase/result[@index=current()])"/>
													<xsl:variable name="adjust-required-passes" select="sum($overrides/overrides/testcase[@client=$this-client and @server=$this-service]/@adjust-required-passes)"/>
													<xsl:variable name="adjust-required-failures" select="sum($overrides/overrides/testcase[@client=$this-client and @server=$this-service]/@adjust-required-failures)"/>
													<xsl:variable name="percentage-passed" select="(count(/summary/required/testcase/result[@index=current()][.='passed']) + $adjust-required-passes) div $numtests"/>
													<xsl:variable name="percentage-failed" select="(count(/summary/required/testcase/result[@index=current()][.='failed' or .='badlog']) + $adjust-required-failures) div $numtests"/>
													<div style="width:80px; height:16px; font-size:0pt">
														<xsl:if test="$percentage-passed > .01">
															<img src="green.gif" height="16" width="{round(80*$percentage-passed)}" alt="{round($percentage-passed * 100)}% passed"/>
														</xsl:if>
														<xsl:if test="$percentage-failed > .01">
															<img src="red.gif" height="16" width="{round(80*$percentage-failed)}" alt="{round($percentage-failed * 100)}% failed"/>
														</xsl:if>
													</div>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</tr>
								</xsl:for-each>
							</tbody>
						</table>
					</td>
					<td style="border:1px solid black">
						<xsl:variable name="done-optional" select="document('cr-complete.xml')/vendors/optional"/>
						<table cellpadding="0" cellspacing="2">
							<thead>
								<tr>
									<th>Client/Server</th>
									<xsl:for-each select="participants/vendor">
										<th>
											<xsl:value-of select="."/>
										</th>
									</xsl:for-each>
								</tr>
							</thead>
							<tbody>
								<xsl:for-each select="participants/vendor">
									<xsl:variable name="this-client" select="."/>
									<tr>
										<th align="right">
											<xsl:value-of select="."/>&#160; 
										</th>
										<xsl:for-each select="../vendor">
											<xsl:variable name="this-service" select="."/>
											<td style="border:2px solid white">
												<xsl:if test="$this-client != $this-service and $done-optional[vendor=$this-service][vendor=$this-client]">
													<xsl:attribute name="style">border:2px solid orange</xsl:attribute>
												</xsl:if>
												<xsl:variable name="index" select="/summary/vendors/vendor[@client=$this-client][@server=$this-service]/@index"/>
												<xsl:for-each select="$index">
													<xsl:variable name="numtests" select="count(/summary/optional/testcase/result[@index=current()])"/>
													<xsl:variable name="adjust-optional-passes" select="sum($overrides/overrides/testcase[@client=$this-client and @server=$this-service]/@adjust-optional-passes)"/>
													<xsl:variable name="adjust-optional-failures" select="sum($overrides/overrides/testcase[@client=$this-client and @server=$this-service]/@adjust-optional-failures)"/>
													<xsl:variable name="percentage-passed" select="(count(/summary/optional/testcase/result[@index=current()][.='passed']) + $adjust-optional-passes) div $numtests"/>
													<xsl:variable name="percentage-failed" select="(count(/summary/optional/testcase/result[@index=current()][.='failed' or .='badlog']) + $adjust-optional-failures) div $numtests"/>
													<div style="width:80px; height:16px; font-size:0pt">
														<xsl:if test="$percentage-passed > .01">
															<img src="green.gif" height="16" width="{round(80*$percentage-passed)}" alt="{round($percentage-passed * 100)}% passed"/>
														</xsl:if>
														<xsl:if test="$percentage-failed > .01">
															<img src="red.gif" height="16" width="{round(80*$percentage-failed)}" alt="{round($percentage-failed * 100)}% failed"/>
														</xsl:if>
													</div>
												</xsl:for-each>
											</td>
										</xsl:for-each>
									</tr>
								</xsl:for-each>
							</tbody>
						</table>
					</td>
				</tr>
				<tr>
					<td style="background-color:orange; padding:.5em">Orange border represents minimum necessary to meet CR requirements (4 interoperable implementations of all required features).</td>
					<td style="background-color:orange; padding:.5em">Orange border represents minimum necessary to meet CR requirements (2 interoperable implementations of all optional features).</td>
				</tr>
			</tbody>
		</table>
		<h3>Complete results of tests of required features</h3>
		<table cellpadding="0" cellspacing="0">
			<thead>
				<xsl:call-template name="vendor-headings"/>
			</thead>
			<tbody>
				<xsl:call-template name="graph">
					<xsl:with-param name="testcases" select="required"/>
				</xsl:call-template>
				<xsl:apply-templates select="required/testcase"/>
			</tbody>
		</table>
		<h3>Complete results of tests of optional features</h3>
		<table cellpadding="0" cellspacing="0">
			<thead>
				<xsl:call-template name="vendor-headings"/>
			</thead>
			<tbody>
				<xsl:call-template name="graph">
					<xsl:with-param name="testcases" select="optional"/>
				</xsl:call-template>
				<xsl:apply-templates select="optional/testcase"/>
			</tbody>
		</table>
		<h3>Complete results of tests of informational features</h3>
		<table cellpadding="0" cellspacing="0">
			<thead>
				<xsl:call-template name="vendor-headings"/>
			</thead>
			<tbody>
				<xsl:call-template name="graph">
					<xsl:with-param name="testcases" select="informational"/>
				</xsl:call-template>
				<xsl:apply-templates select="informational/testcase"/>
			</tbody>
		</table>
		<h3>Notes on manual overrides of the results</h3>
		<xsl:for-each select="$overrides/overrides/testcase">
			<div>
				<b>
					<a name="{generate-id(.)}">
						<xsl:value-of select="position()"/>
					</a>
				</b>: <xsl:copy-of select="node()"/>
			</div>
		</xsl:for-each>
		<xsl:if test="$show-logs='yes'">
			<h3>Failure details</h3>
			<xsl:for-each select="*/testcase/result[.='failed']">
				<xsl:variable name="vendor" select="/summary/vendors/vendor[@index = current()/@index]"/>
				<xsl:variable name="assertion" select="document(@href)/results/assertion[@against=current()/../@id]"/>
				<xsl:variable name="message" select="$assertion/@message"/>
				<div id="{generate-id(.)}">
					<p>
						<b>
							<a href="{../@href}">
								<xsl:value-of select="../@id"/>
							</a>
						</b>
				(<xsl:value-of select="$vendor/@client"/> -> <xsl:value-of select="$vendor/@server"/>) <a href="{$vendor/@href}">full log</a>, <a href="{@href}">raw assertions</a>
					</p>
					<p>This assertion:</p>
					<pre>
						<xsl:value-of select="$assertion/@xpath"/>
					</pre>
					<p>Failed against message <span style="background-color:#ddddff">
							<xsl:value-of select="$message"/>
						</span>:</p>
					<xsl:for-each select="document($vendor/@href)/log:log/log:message[@testcase = current()/../@id]">
						<xsl:choose>
							<xsl:when test="@message = $message">
								<div style="background-color:#ddddff">
<pre>
								    <xsl:call-template name="xml-to-string" />
								  </pre>								</div>
							</xsl:when>
							<xsl:otherwise>
<pre>
								    <xsl:call-template name="xml-to-string" />
								  </pre>							</xsl:otherwise>
						</xsl:choose>
					</xsl:for-each>
				</div>
				<hr/>
			</xsl:for-each>
		</xsl:if>
	</xsl:template>
	<xsl:template match="testcase">
		<tr>
			<td style="font-weight:bold; padding:.25em">
				<a href="{@href}">
					<xsl:value-of select="@id"/>
				</a>
			</td>
			<xsl:variable name="testcase-id" select="@id"/>
			<xsl:for-each select="result">
				<xsl:variable name="client" select="$summary/vendors/vendor[@index = current()/@index]/@client"/>
				<xsl:variable name="server" select="$summary/vendors/vendor[@index = current()/@index]/@server"/>
				<xsl:variable name="override" select="$overrides/overrides/testcase[@id=$testcase-id and @client=$client and @server=$server]"/>
				<xsl:variable name="result">
					<xsl:choose>
						<xsl:when test="$override">
							<xsl:value-of select="$override/@result"/>
							<xsl:text>-override</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="text()"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:variable>
				<td style="border-right:1px solid black; border-top:1px solid black; padding:.25em" class="{$result}">
					<xsl:if test="starts-with($result,'passed')">X</xsl:if>
					<xsl:if test="starts-with($result,'badlog')">bad</xsl:if>
					<xsl:if test="starts-with($result,'failed')">
						<xsl:choose>
							<xsl:when test="$show-logs='yes'">
								<a href="#{generate-id(.)}">failed</a>
							</xsl:when>
							<xsl:otherwise>
								<a href="{@href}">failed</a>
							</xsl:otherwise>
						</xsl:choose>
					</xsl:if>
					<xsl:if test="$result='na-override'">N/A</xsl:if>
					<xsl:if test="$override">
						<xsl:text> [</xsl:text>
						<a href="#{generate-id($override)}">
							<xsl:value-of select="count($override/preceding-sibling::testcase)+1"/>
						</a>
						<xsl:text>]</xsl:text>
					</xsl:if>
				</td>
			</xsl:for-each>
		</tr>
	</xsl:template>
	<xsl:template name="graph">
		<xsl:param name="testcases"/>
		<tr>
			<td/>
			<xsl:for-each select="vendors/vendor">
				<td>
					<xsl:variable name="num-testcases" select="count($testcases/testcase)"/>
					<xsl:variable name="percentage-failed" select="count($testcases/testcase/result[@index=current()/@index and (.='failed' or .='badlog')]) div $num-testcases"/>
					<xsl:variable name="percentage-passed" select="count($testcases/testcase/result[@index=current()/@index and .='passed']) div $num-testcases"/>
					<div style="border-right:1px solid black; width:91px; height:16px; font-size:0pt">
						<xsl:if test="$percentage-passed > .01">
							<img src="green.gif" height="16" width="{90*$percentage-passed}" alt="{$percentage-passed * 100}% passed"/>
						</xsl:if>
						<xsl:if test="$percentage-failed > .01">
							<img src="red.gif" height="16" width="{90*$percentage-failed}" alt="{$percentage-failed * 100}% failed"/>
						</xsl:if>
					</div>
				</td>
			</xsl:for-each>
		</tr>
	</xsl:template>
	<xsl:template name="vendor-headings">
		<tr>
		<th/>
			<xsl:for-each select="vendors/vendor">
				<th style="border-right:1px solid black; padding-left:.2em; padding-right:.2em;">
					<a href="{@href}">
						<xsl:value-of select="@client"/>
						<xsl:text> -&gt; </xsl:text>
						<br/>
						<xsl:value-of select="@server"/>
					</a>
				</th>
			</xsl:for-each>
		</tr>
	</xsl:template>
</xsl:stylesheet>
