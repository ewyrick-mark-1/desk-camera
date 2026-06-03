import {useState, useEffect } from 'react'
import {createRoot } from 'react-dom/client'

const API = 'http://desk-pi.local:3000'

function App() {
	const [files, setFiles] = useState([])
	const [output, setOutput] = useState(null)
	const [flag, setFlag] = useState('--pic')
	const [duration, setDuration] = useState(0)

	useEffect(() => {
		fetch(`${API}/files`)
		.then(res => res.json())
		.then(setFiles)
	}, [])

	const runPic = () => {
		setFlag('--pic')
		fetch(`${API}/run?flag=--pic`)
		.then(res => res.json())
		.then(data => setOutput(data.stdout))
	}

	const runVideo = () => {
		const videoFlag = `--video ${duration}`
		console.log('sending flag: ', videoFlag)
		setFlag(videoFlag)
		fetch(`${API}/run?flag=${videoFlag}`)
		.then(res => res.json())
		.then(data => setOutput(data.stdout))
	} 

	return (
		<div>
			<h1>Desk Camera</h1>
			<button onClick={runPic}>Take Image</button>
			//{output && <p>{output}</p>}
			<input
				value={duration}
				onChange={e => setDuration(e.target.value)}
				placeholder="video length - default is 10s"
			/>
			<button onClick={runVideo}>Take Video</button>
			<ul>
				{Object.entries(files).map(([date, dateFiles]) => (
					<div key={date}>
						<p>{date}</p>
						<hr />
						<div className="grid">
							{dateFiles.map(file => (
								<div key={file}>
								<a href={`${API}/files/${date}/${file}`} download>{file}</a>
								</div>
							))}
						</div>
					</div>
				))}
			</ul>
		</div>	
	)
}

createRoot(document.getElementById('app')).render(<App />)

