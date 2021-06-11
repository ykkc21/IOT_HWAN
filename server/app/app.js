const app = require('express')();
const server = require('http').createServer(app);
// const { Server } = require('socket.io');
// const io = new Server(server);
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
app.set('views', path.join(__dirname, 'views'));
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'html');


app.get('/', (req, res) => {
    // res.send('Hello, Express');
    res.sendFile(path.join(__dirname, '/index.html'));
});

//
// 테스트용
//

// 거주자 이름 확인
app.get('/room/:room', function(req, res){
    var params = req.params;
    var room = params.room;

    console.log('room 번호 : ' + room);

    // 쿼리 수행
    var sql = 'SELECT * FROM roomInfo WHERE room = \'' + room + '\'';
    console.log(sql);
    var name = '';
    connection.query(sql, function(error, rows, fields){
        if (error){
            console.log(error);
        }
        console.log(rows);

        name = rows[0].name;
        console.log(name);

        res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
        res.write(name);
        res.end();
    });

});

//
// 앱 부분
//

// 화재감지기 제품번호 확인
app.get('/set/:sensor', function(req, res){
    var sensor = req.params.sensor;

    var sql = 'SELECT room FROM roomInfo WHERE sensor = \'' + sensor + '\'';
    var room = '';
    connection.query(sql, function(error, rows, fields){
        if(error){
            console.log(error);
        }
         
        room = rows[0].room;
        
        res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
        res.write(room);
        res.end();
        
        
    });
})

// 호실 근처 비상구, 소화기 정보
app.get('/notice/:room', function(req, res) {
    var room = req.params.room;

    var sql = 'SELECT fe.location AS feLocation, ex.location AS exLocation' + 
               ' FROM roomInfo ri , fireExtinguisher fe , `exit` ex' +
               ' WHERE ri.room = ' + room + ' AND fe.feno = ri.feno AND ex.exno = ri.exno ';


    var feLocation = '';
    var exLocation = '';
    connection.query(sql, function(error, rows, fields){
        if(error){
            console.log(error);
        }
         
        feLocation = rows[0].feLocation;
        exLocation = rows[0].exLocation;

        res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
        res.write(feLocation + ', ' + exLocation);
        res.end();
    })
})

// // socket.io
// io.on('connection', (socket) => {
//     console.log('user connected');

// })

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
// connection.end();