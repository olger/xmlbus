from xmlbus import SoapMessage

def echoAction(request):
   response = request.createResponse()
   return response

def dumpAction(request):
   response = request.createResponse()
   return response
   