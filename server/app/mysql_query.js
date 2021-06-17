//mysql모듈 - mysql 사용
const mysql = require('mysql')
const android = require('./app')
const arduino = require('./arduino')

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
connection.connect()

// INSERT 문
module.exports.insert = function(sql) {
  // var sql = 'INSERT INTO ' + table + ' values(?,?,?);';
  // var params = [classnum, name, score];
  console.log(sql)
  connection.query(sql, function(err, rows) {
    console.log(rows);
    if(rows != undefined){
      server.client.write("success")
    }else{
      server.client.write("false")
    }
  })
}

// SELECT 문
module.exports.select = function(sql) {
  console.log(sql)
  connection.query(sql, function(err, rows) {
    console.log(rows);
    if (err){
      //throw err;
      server.client.write("false")
    } else {

      var result = JSON.stringify(rows)
      console.log(result)
      android.res.send(result)
      android.res.end()
      // arduino.client.send("succes : " + result)

    } 
  })
}