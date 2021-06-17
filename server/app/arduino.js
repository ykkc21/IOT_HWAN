const app = require('express')();
const server = require('http').createServer(app);
const query = require('./mysql_query');
const path = require('path');
const android = require('./app')
const mysql = require('mysql')

// 데이터베이스 부분
// 데이터베이스와 연결할 객체 생성
var connection = mysql.createConnection({
    // DataBase 주소
    host : 'localhost',
    // user
    user : 'hwanroot',
    // password
    password : '1234',
    // DataBase 이름
    database : 'hwan'
})

// 데이터베이스 연결
connection.connect();

app.set('port', process.env.PORT || 3030);
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
app.get('/arduino/room/:room', function(req, res){
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

        // res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
        // res.write(name);
        res.send(name);
        res.end();
    });

});


//
// 아두이노 부분
//

// 가스 데이터 수신
app.get('/arduino/sensor/:sensor/gas/:gas', function(req, res){
    var params = req.params;
    var sensor = params.sensor;
    var gas = params.gas;

    console.log(sensor + ", " + gas);
})

// 화재 발생 수신



// http를 3030 포트에서 실행한다.
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});