console.log("hello world");
const fs = require("fs");
const http = require("http");
const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader("Content-Type", "text/plain");
  res.end("hello");
});

fs.readFile("./test.txt", "utf-8", function (err, data) {
  if (err) {
    console.log(err);
  } else {
    console.log(data.toString());
  }
});

server.listen(80, '0.0.0.0', () => {
  console.log('running at http://0.0.0.0/')
})
