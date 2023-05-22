const http = require('node:http');
const fs = require('node:fs');

const hostname = '127.0.0.1';
const port = 8088;
let reqNumber = 0;
let errNumber = 0;

function factorial(num){
  let result = 1n;
  while(num != 0n){
    result *= num;
    num--;
  }
  return result;
}

function anagram(Input){
  let repeat = 1n;
  let counted = new Map();
  for(let letter of Input){
    if(counted[letter]){
      counted[letter]++;
    }
    else{
      counted[letter] = 1n;
    }
  }
  for(let number of Object.values(counted)){
    repeat *= factorial(number);
  }
  return (factorial(BigInt(Input.length))/repeat).toString();
}

const server = http.createServer((req, res) => {
  reqNumber++;
  if(req.method == 'GET' && req.url === '/ping'){
    res.statusCode = 204;
    res.setHeader('Content-Type', 'text/plain');
    res.end();
  }
  else if(req.method == 'GET' && req.url.split('?')[0] === '/anagram'){
    let p = req.url.split('?')[1].split('=')[1];
    if(/^[a-zA-Z]+$/.test(p)){
      let q = anagram(p.toLowerCase());
      let responseBody = JSON.stringify({"p" : p, "total" : q});
      res.statusCode = 200;
      res.setHeader('Content-Type', 'text/plain');
      res.end(responseBody);
    }
    else{
      res.statusCode = 400;
      res.setHeader('Content-Type', 'text/plain');
      res.end();
    }
  }
  else if(req.method == 'GET' && req.url === '/secret'){
    let filePath = '/tmp/secret.key';
    if(fs.existsSync(filePath)){
      res.statusCode = 200;
      res.setHeader('Content-Type', 'text/plain');
      res.end(fs.readFileSync(filePath));
    }
    else{
      res.statusCode = 404;
      errNumber++;
      res.setHeader('Content-Type', 'text/plain');
      res.end();
    }
  }
  else if(req.method == 'GET' && req.url === '/status'){
    let time = new Date();
		let responseBody = JSON.stringify({"time" : time.toISOString().split('.')[0]+"Z", "req" : reqNumber, "err" : errNumber});
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/plain');
    res.end(responseBody);
  }
  else if(req.method == 'GET'){
    res.statusCode = 404;
    errNumber++;
    res.setHeader('Content-Type', 'text/plain');
    res.end();
  }
});

server.listen(port, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});