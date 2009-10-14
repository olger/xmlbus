<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:s="http://www.w3.org/2005/08/addressing/test-cases/message-exchanges"
  xmlns:tc="http://www.w3.org/2002/ws/addr/testsuite/testcases/" 
  version="1.0">
  <xsl:output method="html" encoding="utf-8" doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"
    indent="yes"/>
  <xsl:template match="/">
    <html>
      <head>
        <title>Web Services Addressing 1.0 - Test Message Exchanges</title>
        <link href="../testsuite.css" rel="stylesheet" type="text/css"/>
      </head>
      <body>
        <h1>Web Services Addressing 1.0 - Test Message Exchanges</h1>

	<p><xsl:value-of select="s:message-exchanges/s:description"/></p>

	<ul>
        <xsl:for-each select="s:message-exchanges/s:message-exchange">
	    <li><a href="#{@xml:id}"><xsl:value-of select="@xml:id"/></a>
		{ <xsl:call-template name="cross-ref">
		    <xsl:with-param name="exchange" select="@xml:id" />
		  </xsl:call-template>}
	    </li>
	</xsl:for-each>
	</ul>

	<xsl:for-each select="s:message-exchanges/s:note">
	    <p><i><xsl:value-of select="."/></i></p>
	</xsl:for-each>


        <xsl:for-each select="s:message-exchanges/s:message-exchange">
          <div class="message-exchange {@addr-binding}">
            <a name="{@xml:id}"/>
            <a href="#{@xml:id}">
              <xsl:value-of select="@xml:id"/>
            </a> (<b><xsl:value-of select="@addr-binding"/></b>) 
	        <p>
		<img alt="{@addr-mep}" src="../diagrams/{@addr-mep}.png"/>
		</p>
	    <div class="description">
              <ol>
                <xsl:for-each select="s:messages/s:message">
                  <li>
                    <xsl:value-of select="@from"/> sends <xsl:value-of select="@to"/>
		    a <xsl:value-of select="@method"/>
		    with <xsl:value-of select="@content"/>
                  </li>
                </xsl:for-each>
              </ol>
              <p>
                <i>
                  <xsl:value-of select="s:note"/>
                </i>
              </p>
            </div>
            <div class="tests">
              <p>
		{ <xsl:call-template name="cross-ref">
		    <xsl:with-param name="exchange" select="@xml:id" />
		  </xsl:call-template>}
              </p>
            </div>
          </div>
        </xsl:for-each>

    <hr/>
    <p>
      Generated from <a href="exchanges.xml">exchanges.xml</a> using
      <a href="exchanges.xsl">exchanges.xsl</a>.<br/>
      $Date: 2005/10/26 22:45:13 $
    </p>
    <xsl:copy-of select="document('../address.xml')/suffix/*"/>

      </body>
    </html>
  </xsl:template>

    <xsl:template name="cross-ref">
	<xsl:param name="exchange" />
	     <xsl:for-each select='document("../testcases/testcases.xml")/tc:testcases/tc:testcase/tc:message-exchange[@type=$exchange]/../@xml:id'>
			    
		<a href="../testcases/#{.}">
		    <xsl:value-of select="."/>
		</a>

		<xsl:text> </xsl:text>

	     </xsl:for-each>
    </xsl:template>

</xsl:stylesheet>
