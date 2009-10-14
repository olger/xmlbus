<xsl:stylesheet version="1.0" xmlns:l="http://www.w3.org/2002/ws/addressing/logs/" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <xsl:output method="xml" indent="yes"/>
        <xsl:template match="l:log">
                <l:log xmlns:l="http://www.w3.org/2002/ws/addressing/logs/">
                        <xsl:for-each select="//l:message[@type='request']">
                                <xsl:sort select="@timestamp"/>
                                <xsl:copy-of select="current()"/>
                                <xsl:copy-of select="following-sibling::l:message[1]"/>
                        </xsl:for-each>
                </l:log>
        </xsl:template>
</xsl:stylesheet> 

