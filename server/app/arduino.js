const app = require('express')();
const server = require('http').createServer(app);
const query = require('./mysql_query');
const path = require('path');
const android = require('./app')

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
// 아두이노 부분
//



// http를 3000 포트에서 실행한다.
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});