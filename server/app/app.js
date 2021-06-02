const app = require('express')();
const http = require('http').Server(app);
const io = require('socket.io')(http);

const path = require('path');

app.set('port', process.env.PORT || 3000);
app.set('view engine', 'html');

app.get('/', (req, res) => {
    // res.send('Hello, Express');
    res.sendFile(path.join(__dirname, '/index.html'));
});

app.listen(app.get('port'), () =>{
    console.log(app.get('port'), '번 포트에서 대기 중');
});

