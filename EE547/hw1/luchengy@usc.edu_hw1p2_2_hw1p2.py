from http.server import HTTPServer, BaseHTTPRequestHandler
import json
import os
import datetime

error_number = 0
requests_number = 0

def factorial(num):
    result = 1
    while(num!=0):
        result *= num
        num-=1
    return result

def anagram(Input):
    repeat = 1
    counted = set()
    for letter in Input:
        if letter not in counted:
            ct = Input.count(letter, 0, len(Input))
            repeat *= factorial(ct)
            counted.add(letter)
    return str(factorial(len(Input)) // repeat)

class MyHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global requests_number
        global error_number
        requests_number += 1
        path, _, query_string = self.path.partition("?")
        if path == "/ping":
            self.send_response(204)
            self.end_headers()
        elif path == "/anagram":
            query_value = query_string[2:len(query_string)]
            if query_value.lower().isalpha():
                number = anagram(query_value)
                anagram_result = {
                    "p": query_value, 
                    "total": number
                    }
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(anagram_result).encode('utf-8'))
            else:
                self.send_response(400)
                self.end_headers()
        elif path == "/secret":
            if os.path.exists('/tmp/secret.key'):
                self.send_response(200)
                self.send_header('Content-type','text/plain')
                self.end_headers()
                with open('/tmp/secret.key', 'r') as file:
                    self.wfile.write(file.read().encode('utf-8'))
            else: 
                error_number +=1 
                self.send_response(404)
                self.end_headers()
        elif path == "/status":
                status_result = {
                    "time": datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"), 
                    "req": requests_number, 
                    "err": error_number
                    }
                self.send_response(200)
                self.send_header('Content-type', 'application/json')
                self.end_headers()
                self.wfile.write(json.dumps(status_result).encode('utf-8'))
        else:
            error_number += 1
            self.send_response(404)
            self.end_headers()

if __name__ == "__main__":
    httpd = HTTPServer(('', 8088), MyHTTPRequestHandler)
    httpd.serve_forever()
