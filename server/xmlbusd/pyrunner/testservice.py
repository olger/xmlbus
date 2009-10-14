from xmlbus import SoapMessage

def echoAction(request):
   response = request.createResponse()
   return response
