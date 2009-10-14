import libxml2
import urllib
import re
import time
import datetime

def parseString(htmlAsString):
    """Parse a BuilDBot page that is given as a string
    returns a libxml2dom doc object"""
    doc = libxml2.htmlParseDoc(htmlAsString, None)
    return doc

def generateTestsInXml(parsedDoc):
    lastgiventime = time.localtime()
    print lastgiventime
    files = []
    ctxt = parsedDoc.xpathNewContext()
    #foundNodes = ctxt.xpathEval("//substring(a@name,1,1)=T]")
    foundNodes = ctxt.xpathEval("//a[substring(@name,1,1)=T]")
    print 'foundNodes:%d',len(foundNodes)
    if len(foundNodes) == 0:
        ctxt.xpathFreeContext()
        return None
    for foundNode in foundNodes:
        print foundNode.content
        # lets decide on the build date
    
    ctxt.xpathFreeContext()
    return files

if __name__ == "__main__":
    u = urllib.urlopen('http://www.w3.org/TR/soap12-testcollection/')
    doc = parseString(u.read())
    result = generateTestsInXml(doc)
    if result != None:
        for item in result:
            print item
    doc.freeDoc()

