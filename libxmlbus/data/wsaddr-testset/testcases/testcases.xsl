<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:s="http://www.w3.org/2002/ws/addr/testsuite/testcases/"
    version="1.0">
  <xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"
    indent="yes"/>
  <xsl:template match="/">
    <html>
      <head>
        <title>Web Services Addressing 1.0 - Test Cases</title>
        <link href="../testsuite.css" rel="stylesheet" type="text/css"/>
      </head>
      <body>
        <h1>Web Services Addressing 1.0 - Test Cases</h1>

	<p><xsl:value-of select="s:testcases/s:description"/></p>

	<ul>
        <xsl:for-each select="s:testcases/s:testcase">
	    <li><a href="#{@xml:id}"><xsl:value-of select="@xml:id"/></a>
		  - <xsl:value-of select="s:title"/></li>
	</xsl:for-each>
	</ul>

	<xsl:for-each select="s:testcases/s:note">
	    <p><i><xsl:value-of select="."/></i></p>
	</xsl:for-each>

        <xsl:for-each select="s:testcases/s:testcase">
          <div class="testcase cr-{@cr}">
            <a name="{@xml:id}"/>
            <a href="#{@xml:id}">
              <xsl:value-of select="@xml:id"/>
            </a> - <b><a href="{@origin}"><xsl:value-of select="s:title"/></a></b>
		(<b><xsl:value-of select="@cr"/></b>)
            <div class="features">
              <p>
		Features:
                <xsl:for-each select="s:features/s:feature">
		    <b><a href="../features/#{.}"><xsl:value-of select="."/></a></b>
			<xsl:text> </xsl:text>
		</xsl:for-each>
              </p>
            </div>
	    <div class="description">
	      <p class="test-description">
                  <xsl:value-of select="s:description"/>
	      </p>
	      <p class="message-exchange">
		  <a href="../exchanges/#{s:message-exchange/@type}"><xsl:value-of select="s:message-exchange/@type"/></a>
	      </p>

              <ol>
                <xsl:for-each select="s:message-exchange/s:message">
                  <li>
                    <xsl:value-of select="@from"/> 

			<xsl:choose>
			<xsl:when test="@name">
			    sends a <a href="../documents/{@document}"><xsl:value-of select="@name"/></a>
			</xsl:when>
			<xsl:otherwise>
			    sends an [empty] message 
			</xsl:otherwise>
			</xsl:choose>

			to <xsl:value-of select="@to"/>.

			<ul>
			<xsl:for-each select="s:assert">
			<li>
			    <span class="xpath"><xsl:value-of select="@test"/></span>
			    <xsl:if test="@optional = '1'">
				<span class="optional">  (<b>OPTIONAL</b>)</span>
			    </xsl:if>
			</li>
			</xsl:for-each>
			</ul>
                  </li>
                </xsl:for-each>
              </ol>
              <p>
                <i>
                  <xsl:value-of select="s:note"/>
                </i>
              </p>
            </div>
          </div>
        </xsl:for-each>
    <hr/>
    <p>
      Generated from <a href="testcases.xml">testcases.xml</a> using
      <a href="testcases.xsl">testcases.xsl</a>.<br/>
      $Date: 2006/02/21 17:53:59 $
    </p>
    <xsl:copy-of select="document('../address.xml')/suffix/*"/>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>
