// 모듈 선언
const app = require('express')();
const server = require('http').createServer(app);
const query = require('./mysql_query');
const path = require('path');

// 서버 포트 설정
app.set('port', process.env.PORT || 3000);  

// / 주소로 접근 시
app.get('/', (req, res) => {
    // client로 'Hello, Android' 전송
    res.send('Hello, Android');
});


//
// 앱 부분
//
// 화재감지기 제품번호 확인 
// 3.35.55.95:3000/app/set/센서시리얼번호 로 접근시
app.get('/app/set/:sensor', function(req, res){

    module.exports.res = res;

    // 호수 정보 select
    var sensor = req.params.sensor;
    var sql = 'SELECT room FROM roomInfo WHERE sensor = \'' + sensor + '\'';
    query.select(sql)
})

// 호실 근처 비상구, 소화기 정보
// 3.35.55.95:3000/app/notice/호수 로 접근 시
app.get('/app/notice/:room', function(req, res) {

    module.exports.res = res;

    // 비상구, 소화기 위치 정보 select
    var room = req.params.room;
    var sql = 'SELECT fe.location AS feLocation, ex.location AS exLocation' + 
               ' FROM roomInfo ri , fireExtinguisher fe , `exit` ex' +
               ' WHERE ri.room = \'' + room + '\' AND fe.feno = ri.feno AND ex.exno = ri.exno ';
    query.select(sql)
})

// 화재 이력
// 3.35.55.95:3000/app/history 로 접근 시
app.get('/app/history', function(req, res){

    module.exports.res = res;

    // 화재 이력 최근 15개 select
    var sql = 'SELECT DATE_FORMAT(`date`, "%Y-%m-%d %H:%i:%s") AS t, room FROM fireHistory ORDER BY fireNo DESC LIMIT 15';
    query.select(sql)
})

// 가스 데이터
// 3.35.55.95:3000/app/gas/호수 로 접근 시
app.get('/app/gas/:room', function(req, res){

    module.exports.res = res;

    // 가장 최근 가스 값 select
    var room = req.params.room;
    var sql = 'SELECT gas FROM gasHistory WHERE room=\'' + room + '\' ORDER BY gasNo DESC LIMIT 1'
    query.select(sql)
})


// 화재 데이터
// 3.35.55.95:3000/app/fire 로 접근 시
app.get('/app/fire', function(req, res){

    module.exports.res = res;

    // 가장 최근 화재 데이터 select
    var sql = 'SELECT room, DATE_FORMAT(`date`, "%Y-%m-%d %H:%i:%s") AS t FROM fireHistory ORDER BY fireNo DESC LIMIT 1';
    query.select(sql)
})

// 서버 실행
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});