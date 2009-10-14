<?xml version="1.0" encoding="utf-8"?>
<sch:schema xmlns:s="http://www.w3.org/2002/ws/addr/testsuite/testcases/" xmlns:sch="http://www.ascc.net/xml/schematron">
   <sch:ns prefix="wsa" uri="http://www.w3.org/2005/08/addressing"/>
   <sch:ns prefix="wsaw" uri="http://www.w3.org/2005/03/addressing/wsdl"/>
   <sch:ns prefix="soap11" uri="http://schemas.xmlsoap.org/soap/envelope/"/>
   <sch:ns prefix="soap12" uri="http://www.w3.org/2003/05/soap-envelope"/>
   <sch:ns prefix="wsdl11" uri="http://schemas.xmlsoap.org/wsdl/"/>
   <sch:ns prefix="wsdl20" uri="http://www.w3.org/2006/01/wsdl"/>
   <sch:ns prefix="xs" uri="http://www.w3.org/2001/XMLSchema"/>
   <sch:ns prefix="customer" uri="http://example.org/customer"/>
   <sch:ns prefix="notify" uri="http://example.org/notify"/>
   <sch:ns prefix="echo" uri="http://example.org/echo"/>
   <sch:ns prefix="alertcontrol" uri="http://example.org/alertcontrol"/>
   <sch:ns prefix="log" uri="http://www.w3.org/2002/ws/addressing/logs/"/>
   <sch:pattern name="message">
      <sch:rule context="log:message">
         <sch:assert test="@testcase">message missing testcase attribute</sch:assert>
         <sch:assert test="@message">message missing message attribute</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1100">
      <sch:rule context="log:message[@testcase='test1100'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1100 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1200">
      <sch:rule context="log:message[@testcase='test1200'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1200 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1101">
      <sch:rule context="log:message[@testcase='test1101'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1101 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:MessageID" against test1101 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1201">
      <sch:rule context="log:message[@testcase='test1201'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1201 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:MessageID" against test1201 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1102">
      <sch:rule context="log:message[@testcase='test1102'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1102 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1102 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1202">
      <sch:rule context="log:message[@testcase='test1202'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1202 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1202 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1103">
      <sch:rule context="log:message[@testcase='test1103'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1103 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1103 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1203">
      <sch:rule context="log:message[@testcase='test1203'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1203 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1203 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1104">
      <sch:rule context="log:message[@testcase='test1104'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1104 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1104 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1104 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1204">
      <sch:rule context="log:message[@testcase='test1204'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1204 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1204 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1204 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1106">
      <sch:rule context="log:message[@testcase='test1106'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1106 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1106 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1106 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1206">
      <sch:rule context="log:message[@testcase='test1206'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1206 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1206 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1206 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1107">
      <sch:rule context="log:message[@testcase='test1107'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1107 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1107 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions" against test1107 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description" against test1107 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1207">
      <sch:rule context="log:message[@testcase='test1207'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1207 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1207 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl11:definitions" against test1207 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/wsdl20:description" against test1207 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1108">
      <sch:rule context="log:message[@testcase='test1108'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/notify'" against test1108 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1108 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'" against test1108 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1108 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'" against test1108 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/customer:Metadata">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/customer:Metadata" against test1108 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1208">
      <sch:rule context="log:message[@testcase='test1208'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/notify'" against test1208 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1208 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/@customer:level = 'premium'" against test1208 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1208 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Metadata/@customer:total = '1'" against test1208 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/customer:Metadata">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/customer:Metadata" against test1208 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1130">
      <sch:rule context="log:message[@testcase='test1130'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1130 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:MessageID" against test1130 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1130'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1130'][@message='2']">assertion "all required messages present" against test1130 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1130'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1130 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1130 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1130 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1130 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1130 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1230">
      <sch:rule context="log:message[@testcase='test1230'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1230 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:MessageID" against test1230 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1230'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1230'][@message='2']">assertion "all required messages present" against test1230 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1230'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1230 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1230 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1230 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1230 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1230 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1131">
      <sch:rule context="log:message[@testcase='test1131'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1131 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1131 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1131'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1131'][@message='2']">assertion "all required messages present" against test1131 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1131'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1131 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1131 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1131 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1231">
      <sch:rule context="log:message[@testcase='test1231'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1231 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1231 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1231'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1231'][@message='2']">assertion "all required messages present" against test1231 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1231'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1231 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1231 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1231 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1132">
      <sch:rule context="log:message[@testcase='test1132'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1132 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1132 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1132 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1132'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1132'][@message='2']">assertion "all required messages present" against test1132 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1132'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1132 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'" against test1132 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1132 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1132 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1132 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1232">
      <sch:rule context="log:message[@testcase='test1232'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1232 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1232 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1232 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1232'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1232'][@message='2']">assertion "all required messages present" against test1232 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1232'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1232 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'" against test1232 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1232 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1232 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1232 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1133">
      <sch:rule context="log:message[@testcase='test1133'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1133 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1133 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1133 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'">assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'" against test1133 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1133 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1133'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1133'][@message='2']">assertion "all required messages present" against test1133 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1133'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'" against test1133 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/customer:CustomerKey = 'Fault#123456789'">assertion "soap11:Envelope/soap11:Header/customer:CustomerKey = 'Fault#123456789'" against test1133 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter                    and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter                    and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1133 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))" against test1133 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1133 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1133 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1233">
      <sch:rule context="log:message[@testcase='test1233'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1233 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1233 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1233 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'" against test1233 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1233 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1233'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1233'][@message='2']">assertion "all required messages present" against test1233 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1233'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'" against test1233 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'" against test1233 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1233 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))" against test1233 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1233 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1233 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1134">
      <sch:rule context="log:message[@testcase='test1134'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1134 message 1 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo) or soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo) or soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1134 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1134 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1134'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1134'][@message='2']">assertion "all required messages present" against test1134 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1134'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/fault'" against test1134 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'">assertion "soap11:Envelope/soap11:Header/customer:CustomerKey = 'Key#123456789'" against test1134 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap11:Envelope/soap11:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1134 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString')) or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('soap11:Sender'))" against test1134 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1134 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1134 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1234">
      <sch:rule context="log:message[@testcase='test1234'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1234 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo) or soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo) or soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1234 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:ReferenceParameters/customer:CustomerKey = 'Key#123456789'" against test1234 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1234'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1234'][@message='2']">assertion "all required messages present" against test1234 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1234'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault' or soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/fault'" against test1234 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Key#123456789'" against test1234 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1234 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))" against test1234 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1234 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1234 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1235">
      <sch:rule context="log:message[@testcase='test1235'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1235 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1235 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1235 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'" against test1235 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:ReferenceParameters/customer:CustomerKey = 'Fault#123456789'" against test1235 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1235'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1235'][@message='2']">assertion "all required messages present" against test1235 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1235'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1235 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey = 'Fault#123456789'" against test1235 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()">assertion "soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter      and soap12:Envelope/soap12:Header/customer:CustomerKey/@wsa:IsReferenceParameter cast as xs:boolean = true()" against test1235 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('echo:EmptyEchoString'))" against test1235 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1235 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1235 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1236">
      <sch:rule context="log:message[@testcase='test1236'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1236 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1236 message 1 failed</sch:assert>
         <sch:assert test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0">assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1236 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1237">
      <sch:rule context="log:message[@testcase='test1237'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1237 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1237 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/@soap12:role = 'http://www.w3.org/2003/05/soap-envelope/role/next'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/@soap12:role = 'http://www.w3.org/2003/05/soap-envelope/role/next'" against test1237 message 1 failed</sch:assert>
         <sch:assert test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0">assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1237 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1238">
      <sch:rule context="log:message[@testcase='test1238'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1238 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1238 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand">assertion "soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand" against test1238 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand       and soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand cast as xs:boolean = true()">assertion "soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand       and soap12:Envelope/soap12:Header/alertcontrol:alertcontrol/@soap12:mustUnderstand cast as xs:boolean = true()" against test1238 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1238'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1238'][@message='2']">assertion "all required messages present" against test1238 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1238'][@message='2']/log:content">
         <sch:assert test="not(soap12:Envelope/soap12:Header/soap12:NotUnderstood) or soap12:Envelope/soap12:Header/soap12:NotUnderstood/@qname/(resolve-QName(.,parent::node()) = xs:QName('alertcontrol:alertcontrol'))">assertion "not(soap12:Envelope/soap12:Header/soap12:NotUnderstood) or soap12:Envelope/soap12:Header/soap12:NotUnderstood/@qname/(resolve-QName(.,parent::node()) = xs:QName('alertcontrol:alertcontrol'))" against test1238 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:MustUnderstand'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:MustUnderstand'))" against test1238 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1140">
      <sch:rule context="log:message[@testcase='test1140'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:To) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:To) = 2" against test1140 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1140'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1140'][@message='2']">assertion "all required messages present" against test1140 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1140'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1140 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1140 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous'                           or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous'                           or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1140 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1140 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1140 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1141">
      <sch:rule context="log:message[@testcase='test1141'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:ReplyTo) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:ReplyTo) = 2" against test1141 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1141'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1141'][@message='2']">assertion "all required messages present" against test1141 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1141'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1141 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1141 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))" against test1141 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1141 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1141 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1142">
      <sch:rule context="log:message[@testcase='test1142'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:FaultTo) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:FaultTo) = 2" against test1142 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1142'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1142'][@message='2']">assertion "all required messages present" against test1142 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1142'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1142 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1142 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))" against test1142 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1142 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1142 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1143">
      <sch:rule context="log:message[@testcase='test1143'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:Action) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:Action) = 2" against test1143 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1143'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1143'][@message='2']">assertion "all required messages present" against test1143 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1143'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1143 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1143 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1143 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1143 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1143 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1144">
      <sch:rule context="log:message[@testcase='test1144'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:MessageID) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:MessageID) = 2" against test1144 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1144'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1144'][@message='2']">assertion "all required messages present" against test1144 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1144'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1144 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1144 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test'      or soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))" against test1144 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1146">
      <sch:rule context="log:message[@testcase='test1146'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:To) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:To) = 2" against test1146 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1146'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1146'][@message='2']">assertion "all required messages present" against test1146 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1146'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1146 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))                                 or soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1146 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1146 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1146 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1146 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1147">
      <sch:rule context="log:message[@testcase='test1147'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:Action) = 0">assertion "count(soap11:Envelope/soap11:Header/wsa:Action) = 0" against test1147 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1147'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1147'][@message='2']">assertion "all required messages present" against test1147 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1147'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1147 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))">assertion "soap11:Envelope/soap11:Body/soap11:Fault/faultcode/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))" against test1147 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))">assertion "soap11:Envelope/soap11:Header/wsa:FaultDetail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1147 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1147 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1147 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1149">
      <sch:rule context="log:message[@testcase='test1149'][@message='1']/log:content">
         <sch:assert test="count(soap11:Envelope/soap11:Header/wsa:To) = 2">assertion "count(soap11:Envelope/soap11:Header/wsa:To) = 2" against test1149 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1149 message 1 failed</sch:assert>
         <sch:assert test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0">assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1149 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1240">
      <sch:rule context="log:message[@testcase='test1240'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:To) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1240 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1240'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1240'][@message='2']">assertion "all required messages present" against test1240 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1240'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1240 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1240 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1240 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:To = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1240 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1240 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1240 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1241">
      <sch:rule context="log:message[@testcase='test1241'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:ReplyTo) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:ReplyTo) = 2" against test1241 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1241'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1241'][@message='2']">assertion "all required messages present" against test1241 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1241'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1241 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1241 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1241 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:ReplyTo'))" against test1241 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1241 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1241 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1242">
      <sch:rule context="log:message[@testcase='test1242'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:FaultTo) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:FaultTo) = 2" against test1242 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1242'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1242'][@message='2']">assertion "all required messages present" against test1242 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1242'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1242 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1242 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1242 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:FaultTo'))" against test1242 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1242 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1242 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1243">
      <sch:rule context="log:message[@testcase='test1243'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:Action) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:Action) = 2" against test1243 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1243'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1243'][@message='2']">assertion "all required messages present" against test1243 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1243'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1243 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1243 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1243 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:Action = 'http://message.id/test'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1243 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1243 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1243 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1244">
      <sch:rule context="log:message[@testcase='test1244'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:MessageID) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:MessageID) = 2" against test1244 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1244'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1244'][@message='2']">assertion "all required messages present" against test1244 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1244'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1244 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1244 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1244 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeader/wsa:MessageID = 'http://message.id/test'      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:MessageID'))" against test1244 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1246">
      <sch:rule context="log:message[@testcase='test1246'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:To) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1246 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1246'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1246'][@message='2']">assertion "all required messages present" against test1246 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1246'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1246 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1246 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1246 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:To'))" against test1246 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1246 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1246 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1247">
      <sch:rule context="log:message[@testcase='test1247'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:To) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1247 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1247'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1247'][@message='2']">assertion "all required messages present" against test1247 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1247'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1247 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1247 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidAddressingHeader'))" against test1247 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:InvalidCardinality'))" against test1247 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1247 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1247 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1248">
      <sch:rule context="log:message[@testcase='test1248'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:Action) = 0">assertion "count(soap12:Envelope/soap12:Header/wsa:Action) = 0" against test1248 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1248'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1248'][@message='2']">assertion "all required messages present" against test1248 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1248'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1248 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1248 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:MessageAddressingHeaderRequired'))" against test1248 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemHeaderQName/(resolve-QName(.,.) = xs:QName('wsa:Action'))" against test1248 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1248 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1248 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1249">
      <sch:rule context="log:message[@testcase='test1249'][@message='1']/log:content">
         <sch:assert test="count(soap12:Envelope/soap12:Header/wsa:To) = 2">assertion "count(soap12:Envelope/soap12:Header/wsa:To) = 2" against test1249 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1249 message 1 failed</sch:assert>
         <sch:assert test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0">assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1249 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1150">
      <sch:rule context="log:message[@testcase='test1150'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1150 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address" against test1150 message 1 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')">assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')" against test1150 message 1 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')">assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1150 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1150'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1150'][@message='3']">assertion "all required messages present" against test1150 message 3 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1150'][@message='3']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1150 message 3 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1150 message 3 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1150 message 3 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1250">
      <sch:rule context="log:message[@testcase='test1250'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1250 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address" against test1250 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1250 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1250 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1250'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1250'][@message='3']">assertion "all required messages present" against test1250 message 3 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1250'][@message='3']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1250 message 3 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1250 message 3 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1250 message 3 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1251">
      <sch:rule context="log:message[@testcase='test1251'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1251 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address" against test1251 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1251 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo[not(@soap12:role)]/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo[not(@soap12:role)]/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1251 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo[@soap12:role='http://www.w3.org/2003/05/soap-envelope/role/none']/wsa:Address">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo[@soap12:role='http://www.w3.org/2003/05/soap-envelope/role/none']/wsa:Address" against test1251 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1251'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1251'][@message='3']">assertion "all required messages present" against test1251 message 3 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1251'][@message='3']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1251 message 3 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1152">
      <sch:rule context="log:message[@testcase='test1152'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1152 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address">assertion "soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address" against test1152 message 1 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')">assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = '')" against test1152 message 1 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')">assertion "not(soap11:Envelope/soap11:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1152 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap11:Envelope/soap11:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1152 message 1 failed</sch:assert>
         <sch:assert test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0">assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1152 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1252">
      <sch:rule context="log:message[@testcase='test1252'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1252 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address" against test1252 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = '')" against test1252 message 1 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')">assertion "not(soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/anonymous')" against test1252 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'">assertion "soap12:Envelope/soap12:Header/wsa:FaultTo/wsa:Address = 'http://www.w3.org/2005/08/addressing/none'" against test1252 message 1 failed</sch:assert>
         <sch:assert test="not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0">assertion "not(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']) or count(../following-sibling::log:message[@testcase=current()/../@testcase and @message!='1']/log:content/*) = 0" against test1252 message 1 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1260">
      <sch:rule context="log:message[@testcase='test1260'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1260 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://example.org/unreachable'">assertion "soap12:Envelope/soap12:Header/wsa:ReplyTo/wsa:Address = 'http://example.org/unreachable'" against test1260 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1260'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1260'][@message='3']">assertion "all required messages present" against test1260 message 3 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1260'][@message='3']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://www.w3.org/2005/08/addressing/fault'" against test1260 message 3 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Value/(resolve-QName(.,.) = xs:QName('soap12:Sender'))" against test1260 message 3 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:DestinationUnreachable'))">assertion "soap12:Envelope/soap12:Body/soap12:Fault/soap12:Code/soap12:Subcode/soap12:Value/(resolve-QName(.,.) = xs:QName('wsa:DestinationUnreachable'))" against test1260 message 3 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI)      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI = 'http://example.org/unreachable'">assertion "not(soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI)      or soap12:Envelope/soap12:Body/soap12:Fault/soap12:Detail/wsa:ProblemIRI = 'http://example.org/unreachable'" against test1260 message 3 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1170">
      <sch:rule context="log:message[@testcase='test1170'][@message='1']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1170 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:MessageID" against test1170 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:From/wsa:Address">assertion "soap11:Envelope/soap11:Header/wsa:From/wsa:Address" against test1170 message 1 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand       and soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand cast as xs:boolean = true()">assertion "soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand       and soap11:Envelope/soap11:Header/wsa:From/@soap11:mustUnderstand cast as xs:boolean = true()" against test1170 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1170'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1170'][@message='2']">assertion "all required messages present" against test1170 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1170'][@message='2']/log:content">
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap11:Envelope/soap11:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1170 message 2 failed</sch:assert>
         <sch:assert test="soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID">assertion "soap11:Envelope/soap11:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap11:Envelope/soap11:Header/wsa:MessageID" against test1170 message 2 failed</sch:assert>
         <sch:assert test="not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType) or soap11:Envelope/soap11:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1170 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
   <sch:pattern name="test1270">
      <sch:rule context="log:message[@testcase='test1270'][@message='1']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoIn'" against test1270 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:MessageID" against test1270 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:From/wsa:Address">assertion "soap12:Envelope/soap12:Header/wsa:From/wsa:Address" against test1270 message 1 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand       and soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand cast as xs:boolean = true()">assertion "soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand       and soap12:Envelope/soap12:Header/wsa:From/@soap12:mustUnderstand cast as xs:boolean = true()" against test1270 message 1 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1270'][@message='1']">
         <sch:assert test="following-sibling::log:message[@testcase='test1270'][@message='2']">assertion "all required messages present" against test1270 message 2 failed</sch:assert>
      </sch:rule>
      <sch:rule context="log:message[@testcase='test1270'][@message='2']/log:content">
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'">assertion "soap12:Envelope/soap12:Header/wsa:Action = 'http://example.org/action/echoOut'" against test1270 message 2 failed</sch:assert>
         <sch:assert test="soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID">assertion "soap12:Envelope/soap12:Header/wsa:RelatesTo = ../preceding-sibling::log:message[@testcase=current()/../@testcase and @message='1']/log:content/soap12:Envelope/soap12:Header/wsa:MessageID" against test1270 message 2 failed</sch:assert>
         <sch:assert test="not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'">assertion "not(soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType) or soap12:Envelope/soap12:Header/wsa:RelatesTo/@RelationshipType = 'http://www.w3.org/2005/08/addressing/reply'" against test1270 message 2 failed</sch:assert>
      </sch:rule>
   </sch:pattern>
</sch:schema>