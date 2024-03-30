# Start http server
import os, os.path, sys

###########################################################################
# Globals
required_python_version = (3,5)
web_port = 8000
web_host = "localhost"
web_dir = "Web"
###########################################################################
# Detect Python version
def DetectPython(required_version):
    if (sys.version_info <= required_version):
        return False
    else:
        return True
###########################################################################
# Print log statement
def LogStatement(message, include_elipses = True):
    output = " -- "
    output += message
    if include_elipses:
        output += " ... "
    print(output)
###########################################################################
# Print error statement
def ErrorStatement(message, include_elipses = True):
    output = "ERROR: "
    output += message
    if include_elipses:
        output += " ... "
    print(output)
###########################################################################
## Main
def main():

    # Check Python
    if DetectPython(required_python_version) == False:
        ErrorStatement("Python %d.%d or higher is required to run this script" % required_python_version)
        sys.exit(-1)

    # Go to web root
    os.chdir(web_dir)

    # Start server
    import http.server
    import socketserver
    request_handler = http.server.SimpleHTTPRequestHandler
    with socketserver.TCPServer((web_host, web_port), request_handler) as httpd:
        LogStatement("Now serving at http://" + web_host + ":" + str(web_port))
        httpd.serve_forever()
###########################################################################
main()
