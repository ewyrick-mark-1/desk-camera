import {useState, useEffect } from 'react'
import {createRoot } from 'react-dom/client'

const API = 'http://desk-pi.local:3000'

function App() {
	const [files, setFiles] = useState([])

	useEffect(() => {
		fetch(`${API}/files`)
		.then(res => res.json())
		.then(setFiles)
	}, [])

	return (
		<div>
			<h1>Desk Camera</h1>
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

