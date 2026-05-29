const express = require('express')
const path = require('path')
const fs = require('fs')
const cors = require('cors')

const app = express();
const IMG = path.join(__dirname, '../../img')

app.use(cors())

//pull list of files
app.get('/files', (req, res) => {
	const files = fs. readdirSync(IMG).filter(f => f.endsWith('.png'))
	res.json(files)
})

//serve an img
app.get('/files/:filename', (req, res) => {
	const filePath = path.join(IMG, req.params.filename)
	res.sendFile(filePath)
})

app.listen(3000, '0.0.0.0', () => console.log('running on :3000'))
