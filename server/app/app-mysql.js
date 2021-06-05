var mysql = require('mysql');

var connection = mysql.createConnection({
    host : 'localhost',
    user : 'hwanroot',
    password : '1234',
    database : 'hwan'
});

connection.connect();

connection.query('SELECT * FROM roomInfo', function(error, results, fields){
    if (error){
        console.log(error);
    }
    console.log(results);
});

connection.end();