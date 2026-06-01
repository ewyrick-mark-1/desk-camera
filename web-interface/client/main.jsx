import {useState, useEffect } from 'react'
import {createRoot } from 'react-dom/client'

const API = 'http://desk-pi.local:3000'

function App() {
	const [files, setFiles] = useState([])
	const [output, setOutput] = useState(null)
	
	useEffect(() => {
		fetch(`${API}/files`)
		.then(res => res.json())
		.then(setFiles)
	}, [])

	const runCam = () => {
		fetch(`${API}/run`)
		.then(res => res.json())
		.then(data => setOutput(data.stdout))
	}

	return (
		<div>
			<h1>Desk Camera</h1>
			<button onClick={runCam}>Take Image</button>
		{output && <p>{output}</p>}
		<ul>
				{files.map(file => (
					<li key={file}>
						<a href={`${API}/files/${file}`} download>{file}</a>
					</li>
				))}
			</ul>
		</div>	
	)
}

createRoot(document.getElementById('app')).render(<App />)

