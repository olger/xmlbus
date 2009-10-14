<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:sch="http://www.ascc.net/xml/schematron" xmlns:wsa="http://www.w3.org/2005/08/addressing" xmlns:wsaw="http://www.w3.org/2005/03/addressing/wsdl" xmlns:soap11="http://schemas.xmlsoap.org/soap/envelope/" xmlns:soap12="http://www.w3.org/2003/05/soap-envelope" xmlns:wsdl11="http://schemas.xmlsoap.org/wsdl/" xmlns:wsdl20="http://www.w3.org/2006/01/wsdl" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:customer="http://example.org/customer" xmlns:notify="http://example.org/notify" xmlns:echo="http://example.org/echo" xmlns:alertcontrol="http://example.org/alertcontrol" xmlns:log="http://www.w3.org/2002/ws/addressing/logs/" version="1.0" wsa:dummy-for-xmlns="" wsaw:dummy-for-xmlns="" soap11:dummy-for-xmlns="" soap12:dummy-for-xmlns="" wsdl11:dummy-for-xmlns="" wsdl20:dummy-for-xmlns="" xs:dummy-for-xmlns="" customer:dummy-for-xmlns="" notify:dummy-for-xmlns="" echo:dummy-for-xmlns="" alertcontrol:dummy-for-xmlns="" log:dummy-for-xmlns="">
   <xsl:template match="*|@*" mode="schematron-get-full-path">
      <xsl:apply-templates select="parent::*" mode="schematron-get-full-path"/>
      <xsl:text>/</xsl:text>
      <xsl:if test="count(. | ../@*) = count(../@*)">@</xsl:if>
      <xsl:value-of select="name()"/>
      <xsl:text>[</xsl:text>
      <xsl:value-of select="1+count(preceding-sibling::*[name()=name(current())])"/>
      <xsl:text>]</xsl:text>
   </xsl:template>
   <xsl:template match="/">
      <xsl:apply-templates select="/" mode="M12"/>
      <xsl:apply-templates select="/" mode="M13"/>
      <xsl:apply-templates select="/" mode="M14"/>
      <xsl:apply-templates select="/" mode="M15"/>
      <xsl:apply-templates select="/" mode="M16"/>
      <xsl:apply-templates select="/" mode="M17"/>
      <xsl:apply-templates select="/" mode="M18"/>
      <xsl:apply-templates select="/" mode="M19"/>
      <xsl:apply-templates select="/" mode="M20"/>
      <xsl:apply-templates select="/" mode="M21"/>
      <xsl:apply-templates select="/" mode="M22"/>
      <xsl:apply-templates select="/" mode="M23"/>
      <xsl:apply-templates select="/" mode="M24"/>
      <xsl:apply-templates select="/" mode="M25"/>
      <xsl:apply-templates select="/" mode="M26"/>
      <xsl:apply-templates select="/" mode="M27"/>
      <xsl:apply-templates select="/" mode="M28"/>
      <xsl:apply-templates select="/" mode="M29"/>
      <xsl:apply-templates select="/" mode="M30"/>
      <xsl:apply-templates select="/" mode="M31"/>
      <xsl:apply-templates select="/" mode="M32"/>
      <xsl:apply-templates select="/" mode="M33"/>
      <xsl:apply-templates select="/" mode="M34"/>
      <xsl:apply-templates select="/" mode="M35"/>
      <xsl:apply-templates select="/" mode="M36"/>
      <xsl:apply-templates select="/" mode="M37"/>
      <xsl:apply-templates select="/" mode="M38"/>
      <xsl:apply-templates select="/" mode="M39"/>
      <xsl:apply-templates select="/" mode="M40"/>
      <xsl:apply-templates select="/" mode="M41"/>
      <xsl:apply-templates select="/" mode="M42"/>
      <xsl:apply-templates select="/" mode="M43"/>
      <xsl:apply-templates select="/" mode="M44"/>
      <xsl:apply-templates select="/" mode="M45"/>
      <xsl:apply-templates select="/" mode="M46"/>
      <xsl:apply-templates select="/" mode="M47"/>
      <xsl:apply-templates select="/" mode="M48"/>
      <xsl:apply-templates select="/" mode="M49"/>
      <xsl:apply-templates select="/" mode="M50"/>
      <xsl:apply-templates select="/" mode="M51"/>
      <xsl:apply-templates select="/" mode="M52"/>
      <xsl:apply-templates select="/" mode="M53"/>
      <xsl:apply-templates select="/" mode="M54"/>
      <xsl:apply-templates select="/" mode="M55"/>
      <xsl:apply-templates select="/" mode="M56"/>
      <xsl:apply-templates select="/" mode="M57"/>
      <xsl:apply-templates select="/" mode="M58"/>
      <xsl:apply-templates select="/" mode="M59"/>
      <xsl:apply-templates select="/" mode="M60"/>
      <xsl:apply-templates select="/" mode="M61"/>
      <xsl:apply-templates select="/" mode="M62"/>
      <xsl:apply-templates select="/" mode="M63"/>
      <xsl:apply-templates select="/" mode="M64"/>
      <xsl:apply-templates select="/" mode="M65"/>
      <xsl:apply-templates select="/" mode="M66"/>
      <xsl:apply-templates select="/" mode="M67"/>
   </xsl:template>
   <xsl:template match="log:message" priority="4000" mode="M12">
      <xsl:choose>
         <xsl:when test="@testcase"/>
         <xsl:otherwise>message missing testcase attribute.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="@message"/>
         <xsl:otherwise>message missing message attribute.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M12"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M12"/>
   <xsl:template match="log:message[@testcase='test1100'][@message='1']/log:content" priority="4000" mode="M13">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1100 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M13"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M13"/>
   <xsl:template match="log:message[@testcase='test1200'][@message='1']/log:content" priority="4000" mode="M14">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1200 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M14"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M14"/>
   <xsl:template match="log:message[@testcase='test1101'][@message='1']/log:content" priority="4000" mode="M15">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1101 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:MessageID" against test1101 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M15"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M15"/>
   <xsl:template match="log:message[@testcase='test1201'][@message='1']/log:content" priority="4000" mode="M16">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1201 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:MessageID" against test1201 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M16"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M16"/>
   <xsl:template match="log:message[@testcase='test1102'][@message='1']/log:content" priority="4000" mode="M17">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1102 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1102 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M17"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M17"/>
   <xsl:template match="log:message[@testcase='test1202'][@message='1']/log:content" priority="4000" mode="M18">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1202 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1202 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M18"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M18"/>
   <xsl:template match="log:message[@testcase='test1103'][@message='1']/log:content" priority="4000" mode="M19">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1103 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1103 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M19"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M19"/>
   <xsl:template match="log:message[@testcase='test1203'][@message='1']/log:content" priority="4000" mode="M20">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1203 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1203 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M20"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M20"/>
   <xsl:template match="log:message[@testcase='test1104'][@message='1']/log:content" priority="4000" mode="M21">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1104 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1104 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1104 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M21"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M21"/>
   <xsl:template match="log:message[@testcase='test1204'][@message='1']/log:content" priority="4000" mode="M22">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1204 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1204 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1204 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M22"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M22"/>
   <xsl:template match="log:message[@testcase='test1106'][@message='1']/log:content" priority="4000" mode="M23">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1106 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1106 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1106 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M23"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M23"/>
   <xsl:template match="log:message[@testcase='test1206'][@message='1']/log:content" priority="4000" mode="M24">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1206 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1206 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1206 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M24"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M24"/>
   <xsl:template match="log:message[@testcase='test1107'][@message='1']/log:content" priority="4000" mode="M25">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1107 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1107 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions" against test1107 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description" against test1107 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M25"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M25"/>
   <xsl:template match="log:message[@testcase='test1207'][@message='1']/log:content" priority="4000" mode="M26">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1207 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1207 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions" against test1207 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description" against test1207 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M26"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M26"/>
   <xsl:template match="log:message[@testcase='test1108'][@message='1']/log:content" priority="4000" mode="M27">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1108 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1108 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'" against test1108 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1108 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'" against test1108 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/customer:Metadata"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/customer:Metadata" against test1108 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M27"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M27"/>
   <xsl:template match="log:message[@testcase='test1208'][@message='1']/log:content" priority="4000" mode="M28">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1208 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1208 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'" against test1208 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1208 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'" against test1208 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/customer:Metadata"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/customer:Metadata" against test1208 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M28"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M28"/>
   <xsl:template match="log:message[@testcase='test1130'][@message='1']/log:content" priority="4000" mode="M29">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1130 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:MessageID" against test1130 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M29"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1130'][@message='1']" priority="3999" mode="M29">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1130'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1130 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M29"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1130'][@message='2']/log:content" priority="3998" mode="M29">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1130 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1130 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1130 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1130 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1130 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M29"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M29"/>
   <xsl:template match="log:message[@testcase='test1230'][@message='1']/log:content" priority="4000" mode="M30">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1230 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:MessageID" against test1230 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M30"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1230'][@message='1']" priority="3999" mode="M30">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1230'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1230 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M30"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1230'][@message='2']/log:content" priority="3998" mode="M30">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1230 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1230 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1230 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1230 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1230 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M30"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M30"/>
   <xsl:template match="log:message[@testcase='test1131'][@message='1']/log:content" priority="4000" mode="M31">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1131 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1131 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M31"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1131'][@message='1']" priority="3999" mode="M31">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1131'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1131 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M31"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1131'][@message='2']/log:content" priority="3998" mode="M31">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1131 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1131 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1131 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M31"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M31"/>
   <xsl:template match="log:message[@testcase='test1231'][@message='1']/log:content" priority="4000" mode="M32">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1231 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1231 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M32"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1231'][@message='1']" priority="3999" mode="M32">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1231'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1231 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M32"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1231'][@message='2']/log:content" priority="3998" mode="M32">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1231 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1231 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1231 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M32"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M32"/>
   <xsl:template match="log:message[@testcase='test1132'][@message='1']/log:content" priority="4000" mode="M33">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1132 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1132 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1132 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M33"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1132'][@message='1']" priority="3999" mode="M33">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1132'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1132 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M33"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1132'][@message='2']/log:content" priority="3998" mode="M33">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1132 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'" against test1132 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1132 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1132 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1132 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M33"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M33"/>
   <xsl:template match="log:message[@testcase='test1232'][@message='1']/log:content" priority="4000" mode="M34">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1232 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1232 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1232 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M34"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1232'][@message='1']" priority="3999" mode="M34">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1232'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1232 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M34"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1232'][@message='2']/log:content" priority="3998" mode="M34">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1232 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'" against test1232 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1232 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1232 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1232 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M34"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M34"/>
   <xsl:template match="log:message[@testcase='test1133'][@message='1']/log:content" priority="4000" mode="M35">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1133 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1133 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1133 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'" against test1133 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1133 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M35"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1133'][@message='1']" priority="3999" mode="M35">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1133'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M35"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1133'][@message='2']/log:content" priority="3998" mode="M35">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/customer:CustomerKey = 'Fault#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/customer:CustomerKey = 'Fault#123456789'" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter                    and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1133 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M35"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M35"/>
   <xsl:template match="log:message[@testcase='test1233'][@message='1']/log:content" priority="4000" mode="M36">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1233 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1233 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1233 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'" against test1233 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1233 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M36"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1233'][@message='1']" priority="3999" mode="M36">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1233'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M36"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1233'][@message='2']/log:content" priority="3998" mode="M36">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1233 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M36"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M36"/>
   <xsl:template match="log:message[@testcase='test1134'][@message='1']/log:content" priority="4000" mode="M37">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1134 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo) or soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo) or soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1134 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1134 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M37"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1134'][@message='1']" priority="3999" mode="M37">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1134'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M37"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1134'][@message='2']/log:content" priority="3998" mode="M37">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1134 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M37"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M37"/>
   <xsl:template match="log:message[@testcase='test1234'][@message='1']/log:content" priority="4000" mode="M38">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1234 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo) or soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo) or soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1234 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1234 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M38"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1234'][@message='1']" priority="3999" mode="M38">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1234'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M38"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1234'][@message='2']/log:content" priority="3998" mode="M38">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1234 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M38"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M38"/>
   <xsl:template match="log:message[@testcase='test1235'][@message='1']/log:content" priority="4000" mode="M39">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1235 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1235 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1235 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1235 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'" against test1235 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M39"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1235'][@message='1']" priority="3999" mode="M39">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1235'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M39"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1235'][@message='2']/log:content" priority="3998" mode="M39">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1235 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M39"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M39"/>
   <xsl:template match="log:message[@testcase='test1236'][@message='1']/log:content" priority="4000" mode="M40">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1236 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1236 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0"/>
         <xsl:otherwise>assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1236 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M40"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M40"/>
   <xsl:template match="log:message[@testcase='test1237'][@message='1']/log:content" priority="4000" mode="M41">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1237 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1237 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/@soap12:role = 'http://www.w3.org/2003/05/soap-envelope/role/next'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/@soap12:role = 'http://www.w3.org/2003/05/soap-envelope/role/next'" against test1237 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0"/>
         <xsl:otherwise>assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1237 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M41"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M41"/>
   <xsl:template match="log:message[@testcase='test1238'][@message='1']/log:content" priority="4000" mode="M42">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1238 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1238 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand" against test1238 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand       and soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand and soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand cast as xs:boolean = true()" against test1238 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M42"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1238'][@message='1']" priority="3999" mode="M42">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1238'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1238 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M42"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1238'][@message='2']/log:content" priority="3998" mode="M42">
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/soap12:NotUnderstood) or soap12:Envelope/soap12:Header/soap12:NotUnderstood/@qname/(resolve-QName(.,parent::node()) = xs:QName('alertcontrol:alertcontrol'))"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/soap12:NotUnderstood) or soap12:Envelope/soap12:Header/soap12:NotUnderstood/@qname/(resolve-QName(.,parent::node()) = xs:QName('alertcontrol:alertcontrol'))" against test1238 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:MustUnderstand'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:MustUnderstand'))" against test1238 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M42"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M42"/>
   <xsl:template match="log:message[@testcase='test1140'][@message='1']/log:content" priority="4000" mode="M43">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:To) = 2" against test1140 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M43"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1140'][@message='1']" priority="3999" mode="M43">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1140'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1140 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M43"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1140'][@message='2']/log:content" priority="3998" mode="M43">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1140 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1140 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous'                           or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous' or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1140 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1140 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1140 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M43"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M43"/>
   <xsl:template match="log:message[@testcase='test1141'][@message='1']/log:content" priority="4000" mode="M44">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:ReplyTo) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:ReplyTo) = 2" against test1141 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M44"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1141'][@message='1']" priority="3999" mode="M44">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1141'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1141 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M44"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1141'][@message='2']/log:content" priority="3998" mode="M44">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1141 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1141 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous' or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))" against test1141 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1141 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1141 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M44"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M44"/>
   <xsl:template match="log:message[@testcase='test1142'][@message='1']/log:content" priority="4000" mode="M45">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:FaultTo) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:FaultTo) = 2" against test1142 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M45"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1142'][@message='1']" priority="3999" mode="M45">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1142'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1142 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M45"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1142'][@message='2']/log:content" priority="3998" mode="M45">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1142 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1142 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous' or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))" against test1142 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1142 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1142 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M45"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M45"/>
   <xsl:template match="log:message[@testcase='test1143'][@message='1']/log:content" priority="4000" mode="M46">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:Action) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:Action) = 2" against test1143 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M46"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1143'][@message='1']" priority="3999" mode="M46">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1143'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1143 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M46"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1143'][@message='2']/log:content" priority="3998" mode="M46">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1143 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1143 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test' or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1143 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1143 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1143 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M46"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M46"/>
   <xsl:template match="log:message[@testcase='test1144'][@message='1']/log:content" priority="4000" mode="M47">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:MessageID) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:MessageID) = 2" against test1144 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M47"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1144'][@message='1']" priority="3999" mode="M47">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1144'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1144 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M47"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1144'][@message='2']/log:content" priority="3998" mode="M47">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1144 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1144 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test' or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))" against test1144 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M47"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M47"/>
   <xsl:template match="log:message[@testcase='test1146'][@message='1']/log:content" priority="4000" mode="M48">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:To) = 2" against test1146 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M48"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1146'][@message='1']" priority="3999" mode="M48">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1146'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1146 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M48"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1146'][@message='2']/log:content" priority="3998" mode="M48">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1146 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1146 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1146 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1146 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1146 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M48"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M48"/>
   <xsl:template match="log:message[@testcase='test1147'][@message='1']/log:content" priority="4000" mode="M49">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:Action) = 0"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:Action) = 0" against test1147 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M49"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1147'][@message='1']" priority="3999" mode="M49">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1147'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1147 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M49"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1147'][@message='2']/log:content" priority="3998" mode="M49">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1147 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))" against test1147 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1147 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1147 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1147 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M49"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M49"/>
   <xsl:template match="log:message[@testcase='test1149'][@message='1']/log:content" priority="4000" mode="M50">
      <xsl:choose>
         <xsl:when test="count(soap11:Envelope/soap11:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap11:Envelope/soap11:Header/wsa:To) = 2" against test1149 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1149 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0"/>
         <xsl:otherwise>assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1149 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M50"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M50"/>
   <xsl:template match="log:message[@testcase='test1240'][@message='1']/log:content" priority="4000" mode="M51">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1240 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M51"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1240'][@message='1']" priority="3999" mode="M51">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1240'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M51"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1240'][@message='2']/log:content" priority="3998" mode="M51">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous' or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1240 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M51"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M51"/>
   <xsl:template match="log:message[@testcase='test1241'][@message='1']/log:content" priority="4000" mode="M52">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:ReplyTo) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:ReplyTo) = 2" against test1241 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M52"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1241'][@message='1']" priority="3999" mode="M52">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1241'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M52"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1241'][@message='2']/log:content" priority="3998" mode="M52">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous' or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1241 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M52"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M52"/>
   <xsl:template match="log:message[@testcase='test1242'][@message='1']/log:content" priority="4000" mode="M53">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:FaultTo) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:FaultTo) = 2" against test1242 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M53"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1242'][@message='1']" priority="3999" mode="M53">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1242'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M53"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1242'][@message='2']/log:content" priority="3998" mode="M53">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous' or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1242 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M53"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M53"/>
   <xsl:template match="log:message[@testcase='test1243'][@message='1']/log:content" priority="4000" mode="M54">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:Action) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:Action) = 2" against test1243 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M54"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1243'][@message='1']" priority="3999" mode="M54">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1243'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M54"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1243'][@message='2']/log:content" priority="3998" mode="M54">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test' or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1243 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M54"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M54"/>
   <xsl:template match="log:message[@testcase='test1244'][@message='1']/log:content" priority="4000" mode="M55">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:MessageID) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:MessageID) = 2" against test1244 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M55"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1244'][@message='1']" priority="3999" mode="M55">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1244'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1244 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M55"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1244'][@message='2']/log:content" priority="3998" mode="M55">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1244 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1244 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1244 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test' or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))" against test1244 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M55"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M55"/>
   <xsl:template match="log:message[@testcase='test1246'][@message='1']/log:content" priority="4000" mode="M56">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1246 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M56"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1246'][@message='1']" priority="3999" mode="M56">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1246'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M56"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1246'][@message='2']/log:content" priority="3998" mode="M56">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1246 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M56"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M56"/>
   <xsl:template match="log:message[@testcase='test1247'][@message='1']/log:content" priority="4000" mode="M57">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1247 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M57"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1247'][@message='1']" priority="3999" mode="M57">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1247'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M57"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1247'][@message='2']/log:content" priority="3998" mode="M57">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1247 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M57"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M57"/>
   <xsl:template match="log:message[@testcase='test1248'][@message='1']/log:content" priority="4000" mode="M58">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:Action) = 0"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:Action) = 0" against test1248 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M58"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1248'][@message='1']" priority="3999" mode="M58">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1248'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M58"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1248'][@message='2']/log:content" priority="3998" mode="M58">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1248 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M58"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M58"/>
   <xsl:template match="log:message[@testcase='test1249'][@message='1']/log:content" priority="4000" mode="M59">
      <xsl:choose>
         <xsl:when test="count(soap12:Envelope/soap12:Header/wsa:To) = 2"/>
         <xsl:otherwise>assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1249 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1249 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0"/>
         <xsl:otherwise>assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1249 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M59"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M59"/>
   <xsl:template match="log:message[@testcase='test1150'][@message='1']/log:content" priority="4000" mode="M60">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1150 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address" against test1150 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')" against test1150 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1150 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M60"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1150'][@message='1']" priority="3999" mode="M60">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1150'][@message='3']"/>
         <xsl:otherwise>assertion "all required messages present" against test1150 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M60"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1150'][@message='3']/log:content" priority="3998" mode="M60">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1150 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1150 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1150 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M60"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M60"/>
   <xsl:template match="log:message[@testcase='test1250'][@message='1']/log:content" priority="4000" mode="M61">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1250 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address" against test1250 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1250 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1250 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M61"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1250'][@message='1']" priority="3999" mode="M61">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1250'][@message='3']"/>
         <xsl:otherwise>assertion "all required messages present" against test1250 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M61"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1250'][@message='3']/log:content" priority="3998" mode="M61">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1250 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1250 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1250 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M61"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M61"/>
   <xsl:template match="log:message[@testcase='test1251'][@message='1']/log:content" priority="4000" mode="M62">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1251 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address" against test1251 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1251 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo[not(@soap12:role)]/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo[not(@soap12:role)]/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1251 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo[@soap12:role='http://www.w3.org/2003/05/soap-envelope/role/none']/wsa:Address"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo[@soap12:role='http://www.w3.org/2003/05/soap-envelope/role/none']/wsa:Address" against test1251 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M62"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1251'][@message='1']" priority="3999" mode="M62">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1251'][@message='3']"/>
         <xsl:otherwise>assertion "all required messages present" against test1251 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M62"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1251'][@message='3']/log:content" priority="3998" mode="M62">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1251 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M62"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M62"/>
   <xsl:template match="log:message[@testcase='test1152'][@message='1']/log:content" priority="4000" mode="M63">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1152 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address" against test1152 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')" against test1152 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1152 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1152 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0"/>
         <xsl:otherwise>assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1152 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M63"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M63"/>
   <xsl:template match="log:message[@testcase='test1252'][@message='1']/log:content" priority="4000" mode="M64">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1252 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address" against test1252 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1252 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1252 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1252 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0"/>
         <xsl:otherwise>assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1252 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M64"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M64"/>
   <xsl:template match="log:message[@testcase='test1260'][@message='1']/log:content" priority="4000" mode="M65">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1260 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://example.org/unreachable'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://example.org/unreachable'" against test1260 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M65"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1260'][@message='1']" priority="3999" mode="M65">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1260'][@message='3']"/>
         <xsl:otherwise>assertion "all required messages present" against test1260 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M65"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1260'][@message='3']/log:content" priority="3998" mode="M65">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1260 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1260 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:DestinationUnreachable'))"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:DestinationUnreachable'))" against test1260 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI)      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI = 'http://example.org/unreachable'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI) or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI = 'http://example.org/unreachable'" against test1260 message 3 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M65"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M65"/>
   <xsl:template match="log:message[@testcase='test1170'][@message='1']/log:content" priority="4000" mode="M66">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1170 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:MessageID" against test1170 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:From/wsa:Address"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:From/wsa:Address" against test1170 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand       and soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand and soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand cast as xs:boolean = true()" against test1170 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M66"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1170'][@message='1']" priority="3999" mode="M66">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1170'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1170 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M66"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1170'][@message='2']/log:content" priority="3998" mode="M66">
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1170 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1170 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1170 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M66"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M66"/>
   <xsl:template match="log:message[@testcase='test1270'][@message='1']/log:content" priority="4000" mode="M67">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1270 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:MessageID" against test1270 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:From/wsa:Address"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:From/wsa:Address" against test1270 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand       and soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand cast as xs:boolean = true()"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand and soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand cast as xs:boolean = true()" against test1270 message 1 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M67"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1270'][@message='1']" priority="3999" mode="M67">
      <xsl:choose>
         <xsl:when test="following-sibling::log:message[@testcase='test1270'][@message='2']"/>
         <xsl:otherwise>assertion "all required messages present" against test1270 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M67"/>
   </xsl:template>
   <xsl:template match="log:message[@testcase='test1270'][@message='2']/log:content" priority="3998" mode="M67">
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1270 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID"/>
         <xsl:otherwise>assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1270 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:choose>
         <xsl:when test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'"/>
         <xsl:otherwise>assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1270 message 2 failed.
</xsl:otherwise>
      </xsl:choose>
      <xsl:apply-templates mode="M67"/>
   </xsl:template>
   <xsl:template match="text()" priority="-1" mode="M67"/>
   <xsl:template match="text()" priority="-1"/>
</xsl:stylesheet>