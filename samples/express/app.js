const express = require('express');
const app = express();
const port = 3000;

// Middleware para parsear JSON
app.use(express.json());

// Endpoint raíz
app.get('/', (req, res) => {
  res.json({ message: '¡Servidor Express corriendo con Node.js!' });
});

app.listen(port, () => {
  console.log(`Servidor escuchando en http://localhost:${port}`);
});
