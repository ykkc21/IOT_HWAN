var mysql = require('mysql');

// 데이터베이스 정보
var connection = mysql.createConnection({
    host : 'localhost',
    user : 'hwanroot',
    password : '1234',
    database : 'hwan'
});

// 데이터베이스 연결
connection.connect();

// 쿼리 수행
connection.query('SELECT name FROM roomInfo WHERE room = \'203\'', function(error, results, fields){
    if (error){
        console.log(error);
    }
    console.log(results);
});

// 데이터베이스 연결해제
connection.end();