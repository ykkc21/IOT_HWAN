var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
 
app.get('/', function(req, res){
  res.sendFile(__dirname + '/test.html');
});
 
io.on('connection', function(socket){
    console.log('a user connected');
    socket.on('disconnect', function(){
      console.log('user disconnected');
    });
 
    socket.on('msg', function(msg){
        console.log('message: ' + msg);
        io.emit('msg', msg);
    });
});
 
http.listen(8080, function(){
  console.log('listening on *:8080');
});