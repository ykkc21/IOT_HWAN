const app = require('express')();
const server = require('http').createServer(app);
const query = require('./mysql_query');
const path = require('path');
const android = require('./app')
require('date-utils');

app.set('port', process.env.PORT || 3030);
app.set('views', path.join(__dirname, 'views'));
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'html');


app.get('/', (req, res) => {
    // res.send('Hello, Express');
    res.sendFile(path.join(__dirname, '/index.html'));
});


//
// 아두이노 부분
//

// 가스 데이터 수신
app.get('/arduino/sensor/:sensor/gas/:gas', function(req, res){

    module.exports.res = res;

    var params = req.params;
    var sensor = params.sensor;
    var gas = params.gas;

    var newDate = new Date();
    // var time = newDate.toFormat('YYYYMMDDHHmmss');
    var time = newDate.toFormat('YYYYMMDDHH') + newDate.getMinutes() + newDate.getSeconds();

    var sql = 'INSERT INTO hwan.gasHistory (room, `date`, gas) VALUES((SELECT room FROM roomInfo WHERE sensor = \'' 
        + sensor + '\'), \'' + time + '\', ' + gas + ')';

    query.insert(sql);
})

// 화재 발생 수신
app.get('/arduino/sensor/:sensor/fire', function(req, res){

    module.exports.res = res;


    var params = req.params;
    var sensor = params.sensor;

    var newDate = new Date();
    // var time = newDate.toFormat('YYYYMMDDHHmmss');
    var time = newDate.toFormat('YYYYMMDDHH') + newDate.getMinutes() + newDate.getSeconds();


    var sql = 'INSERT INTO fireHistory (`date`, room) VALUES(\'' + time + '\', (SELECT room FROM roomInfo WHERE sensor = \'' + sensor + '\'))';

    query.insert(sql);

})

// http를 3030 포트에서 실행한다.
server.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});