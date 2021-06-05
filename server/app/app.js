const app = require('express')();
const server = require('http').createServer(app);
const io = require('socket.io')(server);
const mysql = require('mysql');

const path = require('path');

// 데이터베이스 정보
var connection = mysql.createConnection({
    host : 'localhost',
    user : 'hwanroot',
    password : '1234',
    database : 'hwan'
});

// 데이터베이스 연결
connection.connect();

app.set('port', process.env.PORT || 3000);
app.set('view engine', 'html');

app.get('/', (req, res) => {
    // res.send('Hello, Express');
    res.sendFile(path.join(__dirname, '/index.html'));
});

app.get('/process/login', function(req, res){
    var id = req.param('id');

    console.log('/process/login 처리, id: ' + id);

        // 쿼리 수행
        var sql = 'SELECT name FROM roomInfo WHERE room = \'' + id + '\'';
        var name = '';
        connection.query('SELECT * FROM roomInfo WHERE room = \'203\'', function(error, rows, fields){
            if (error){
                console.log(error);
            }
            console.log(rows);

            name = rows[0].name;

            // res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
            // res.write("Success, name: " + name);
        });

    res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
    res.write("Success, name: " + name);
    res.end();
})

// 'connection' 이라는 이벤트를 감지한다.
io.sockets.on('connection', () => {
    console.log('hello');
    
    socket.on('emit_from_client', (data) => {
        console.log('client sent: ' + data);
        io.sockets.emit('emit_from_server', data);
    });

    // 연결 종료 감지
    socket.on('disconnect', function() {
        console.log('user disconnected');
    })
})

// http를 3000 포트에서 실행한다.
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});

// TCP 서버 - 현재 사용 안함
const net = require('net');

net.createServer(function (client){
    console.log('Client connected');

    //Client로 부터 오는 data를 화면에 출력
    client.on('data', function(data){
        var led = data;
        console.log('Client sent ' + data);
        // console.log('Client sent ' + data.toString());

        // 입력받은 값이 1 이면 client에게 led on / 0 이면 led off 메시지 전송
        if(led == 1) {
          client.write("led on");
        } else if(led == 0) {
          client.write("led off");
        }
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

// 데이터베이스 연결해제
connection.end();