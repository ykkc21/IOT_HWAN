const app = require('express')();
const server = require('http').createServer(app);
const query = require('./mysql_query');
const path = require('path');
const arduino = require('./arduino')

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

    module.exports.res = res;

    var params = req.params;
    var room = params.room;

    console.log('room 번호 : ' + room);

    // 쿼리 수행
    // var sql = 'SELECT * FROM roomInfo WHERE room = \'' + room + '\'';
    var sql = 'SELECT room, `date` FROM fireHistory WHERE room=\'' + room + '\' ORDER BY `date` DESC LIMIT 1';
    console.log(sql);
    var t = '';
    connection.query(sql, function(error, rows, fields){
        if (error){
            console.log(error);
        }
        console.log(rows);

        t = rows[0].date;
        console.log(t);

        res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
        res.write(t);
        res.end();
    });

});


//
// 앱 부분
//

// 화재감지기 제품번호 확인
app.get('/app/set/:sensor', function(req, res){

    module.exports.res = res;

    var sensor = req.params.sensor;

    var sql = 'SELECT room FROM roomInfo WHERE sensor = \'' + sensor + '\'';
    var room = '';

    query.select(sql)
})

// 호실 근처 비상구, 소화기 정보
app.get('/app/notice/:room', function(req, res) {

    module.exports.res = res;

    var room = req.params.room;

    var sql = 'SELECT fe.location AS feLocation, ex.location AS exLocation' + 
               ' FROM roomInfo ri , fireExtinguisher fe , `exit` ex' +
               ' WHERE ri.room = \'' + room + '\' AND fe.feno = ri.feno AND ex.exno = ri.exno ';


    query.select(sql)
})

// 화재 이력
app.get('/app/history', function(req, res){

    module.exports.res = res;

    var sql = 'SELECT `date`, room FROM fireHistory ORDER BY fireNo DESC LIMIT 15';
    
    query.select(sql)
})

// 가스 데이터
app.get('/app/gas/:room', function(req, res){

    module.exports.res = res;

    var room = req.params.room;

    var sql = 'SELECT gas FROM gasHistory WHERE room=\'' + room + '\' ORDER BY `date` DESC LIMIT 1';

    query.select(sql)
})


// 화재 데이터
app.get('/app/fire/:room', function(req, res){

    module.exports.res = res;

    var room = req.params.room;

    var sql = 'SELECT room, `date` FROM fireHistory WHERE room=\'' + room + '\' ORDER BY `date` DESC LIMIT 1';

    query.select(sql)
})

// http를 3000 포트에서 실행한다.
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});