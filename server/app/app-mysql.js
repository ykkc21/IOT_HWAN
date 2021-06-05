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
// connection.query('SELECT name FROM roomInfo WHERE room = \'203\'', function(error, results, fields){
//     if (error){
//         console.log(error);
//     }
//     console.log(results);
// });

var id = 101;
var sql = 'SELECT name FROM roomInfo WHERE room = \'' + id + '\'';
        // var name = '';
        connection.query(sql, function(error, rows, fields){
            if (error){
                console.log(error);
            }
            console.log(rows);

            // name = rows.name;

            // res.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
            // res.write("Success, name: " + name);
        });

// 데이터베이스 연결해제
connection.end();