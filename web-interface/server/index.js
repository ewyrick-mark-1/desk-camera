const express = require('express')
const path = require('path')
const fs = require('fs')
const cors = require('cors')

const { createServer } = require('http')
const { Server } = require('socket.io')
const { exec } = require('child_process')

const app = express();
const server = createServer(app);
const io = new Server(server, {cors: { origin: '*'}});

const IMG = path.join(__dirname, '../../img');

app.use(cors())

//REST endpoints

//pull list of files
app.get('/files', (req, res) => {
	const dates = fs.readdirSync(IMG)
		.filter(f => fs.statSync(path.join(IMG, f)).isDirectory())
		.sort().reverse();
	const grouped = {};
	dates.forEach(date => {
		grouped[date] = fs.readdirSync(path.join(IMG, date))
			.filter(f => f.endsWith('.png') || f.endsWith('.mp4'));
	});
	res.json(grouped);

})

//serve a file
app.get('/files/:date/:filename', (req, res) => {
	const filePath = path.join(IMG, req.params.date, req.params.filename)
	res.sendFile(filePath)
})

//take an img or video
app.get('/run', (req, res) => {
	
	//add a command whitelist if ever exposed online.
	const flag = req.query.flag || `--pic`; //pic is fallback
	console.log('received flag:', flag);
	console.log('running command:', `./cam ${flag}` );
	
	const args = flag.split(' ');
	//const command = `./cam ${args.join(' ')}`;
	const command = `./cam ${flag}`;
	exec(command, { cwd: path.join(__dirname, '../../build/') }, (error, stdout, stderr) => {
		if(error){
			return res.status(500).json({ error: error.message, stderr});
		}
		res.json({ stdout, stderr });
	})
})



//SOCKET.IO - webhooks w named events

io.on('connection', (socket) => {
	console.log('Client connected:', socket.id);
	
	//pull list of files
	socket.on('get_files', () => {
		const files = fs.readdirSync(IMG).filter(f => f.endsWith('.png'))
		socket.emit('files_list', files);
	});

	//serve an img
	socket.on('get_image', (filename) => {
		const imageData = fs.readFileSync(path.join(IMG, filename)).toString('base64');
		socket.emit('image_data', {filename, imageData});
	});

	socket.on('disconnect', () => console.log('Client disconnected'))


})
server.listen(3000, '0.0.0.0', () => console.log('running on :3000'))
