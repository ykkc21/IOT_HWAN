const net = require('net');
const mysql = require('mysql');
const query = require('./mysql_query');
const arduino = require('../arduino');

// 앱
net.createServer(function (client){
    console.log('Client connected, 8080');

    module.exports.client = client;

    //Client로 부터 오는 data를 화면에 출력
    client.on('data', function(data){
        var room = data;
        console.log('Client sent ' + data);
        
        var sql = 'SELECT * FROM roomInfo WHERE room = ' + room;
        query.select(sql);
    });

    //Client와 접속이 끊기는 메시지 출력
    client.on('end',function(){
        console.log('Client disconnected');
    });

    client.on('error', function(e){
        console.log('error ' + e);
    })

    //Client가 접속하면 화면에 출력해주는 메시지
    client.write('Hello form tcp server');
}).listen(8080, function(){
    console.log('TCP server is listening on port 8080');
});