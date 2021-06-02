const express = require('express');
const path = require('path');
const socket = require('socket.io');

const app = express();

app.set('port', process.env.PORT || 3000);
app.set('view engine', 'html');


app.get('/', (req, res) => {
    // res.send('Hello, Express');
    res.sendFile(path.join(__dirname, '/index.html'));
});

const server = app.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});


module.export = (server) => {
    const io = socket(server);

    io.on('connection', socket => { // 웹 소켓 연결시
        console.log('hello');

        socket.on('reply', data => {
            console.log(data);
            socket.emit(data);
        });
    });
};