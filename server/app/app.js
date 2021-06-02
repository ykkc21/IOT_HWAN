const express = require('express');
const path = require('path');
const socket = require('socket.io');

const app = express();

app.set('port', process.env.PORT || 3000);

app.get('/', (req, res) => {
    // res.send('Hello, Express');
    res.sendFile(path.join(__dirname, '/index.html'));
});

const server = app.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});

const io = socket(server);

io.on('connection', socket => {
    console.log('hello');
});