//소켓 서버는 연결을 위한 수신 처리 후 서버 연결을 통한 데이터 송신/수신을 한다.
//net모듈의 소켓 객체를 사용
var net = require('net');

//서버를 생성
var server = net.createServer(function(client){
    console.log('Client connected');

    //Client로 부터 오는 data를 화면에 출력
    client.on('data', function(data){
        var str = data();
        console.log('Client sent ' + str);
        // console.log('Client sent ' + data.toString());
        client.write(str);
        client.write("Tt");

        // 입력받은 값이 1 이면 client에게 led on / 0 이면 led off 메시지 전송
        if (str == "1") {
          console.log("led on");
          client.write("led on");
        } else if(str == "0") {
          client.write("led off");
        }
    });

    //Client와 접속이 끊기는 메시지 출력
    client.on('end',function(){
        console.log('Client disconnected');
    });

    //Client가 접속하면 화면에 출력해주는 메시지
    client.write('Hello');
});

//에러가 발생할 경우 화면에 에러 메시지 출력
server.on('error',function(err){
    console.log('err'+err);
})

//port 8080으로 접속이 가능하도록 대기
server.listen(8080, function(){
    console.log('Server listening for connections');
});
