// 모듈 선언
const app = require('express')();
const server = require('http').createServer(app);
const query = require('./mysql_query');
const android = require('./app')
require('date-utils');

// 서버 포트 설정
app.set('port', process.env.PORT || 3030);

// / 주소로 접그 시 
app.get('/', (req, res) => {
    // client로 'Hello, Arduino' 전송
    res.send('Hello, Arduino');
});


//
// 아두이노 부분
//

// 가스 데이터 수신
// 3.35.55.95:3030/arduino/sensor/센서시리얼번호/gas/가스값 로 접근 시
app.get('/arduino/sensor/:sensor/gas/:gas', function(req, res){

    module.exports.res = res;

    // 센서시리얼번호, 가스값 저장
    var params = req.params;
    var sensor = params.sensor;
    var gas = params.gas;

    // 현재 시간 
    var newDate = new Date();
    var yyyymmddhh = newDate.toFormat('YYYYMMDDHH')
    var min = newDate.getMinutes();
    if(min < 10){
        min = '0' + min;
    }
    var sec = newDate.getSeconds()
    if(sec < 10){
        sec = '0' + sec;
    }
    var time = yyyymmddhh + min + sec;
    

    // gasHistory 에 insert
    var sql = 'INSERT INTO hwan.gasHistory (room, `date`, gas) VALUES((SELECT room FROM roomInfo WHERE sensor = \'' 
        + sensor + '\'), \'' + time + '\', ' + gas + ')';

    query.insert(sql);
})

// 화재 발생 수신
// 3.35.55.95:3030/arduino/sensor/센서시리얼번호/fire 로 접근 시
app.get('/arduino/sensor/:sensor/fire', function(req, res){

    module.exports.res = res;

    // 센서 시리얼번호 저장
    var params = req.params;
    var sensor = params.sensor;

    // 현재 시간
    var newDate = new Date();
    var yyyymmddhh = newDate.toFormat('YYYYMMDDHH')
    var min = newDate.getMinutes();
    if(min < 10){
        min = '0' + min;
    }
    var sec = newDate.getSeconds()
    if(sec < 10){
        sec = '0' + sec;
    }
    var time = yyyymmddhh + min + sec;

    // fireHistory 에 insert
    var sql = 'INSERT INTO fireHistory (`date`, room) VALUES(\'' + time + '\', (SELECT room FROM roomInfo WHERE sensor = \'' + sensor + '\'))';
    query.insert(sql);

})

// 서버 실행
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});