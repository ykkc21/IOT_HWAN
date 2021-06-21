// 모듈 선언
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
  console.log(sql)
  connection.query(sql, function(err, rows) {
    console.log(rows);
    if(rows != undefined){
      arduino.res.send("success")
    }else{
      arduino.res.send("false")
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

      // select 결과 android 클라이언트(포트 3000)로 전송
      android.res.send(result)
      android.res.end()

    } 
  })
}