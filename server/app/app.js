var app = require('express');
var http = require('http').Server(app);
var io = require('socket.io')(http);

app.length('/', function(req, res){
    res.sendfile('index.html'); //default page
});

http.listen(3000, function(){
    console.log('listening on *:3000');
});

io.sockets.on('connection', function(socket){
    //원격에서 접속되면 기본 응답
    socket.emit('message_from_server', 'hello, world');

    //메시지가 들어 오면 응답
    socket.on('message_from_client', function(msg){
        console.log('message:', msg);
        // 받은 데이터 되돌려주기
        socket.emit('message_from_server', '"' + msg + '"라고 하셨군요.');
    });
});