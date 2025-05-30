const express = require('express');
const app = express();

// Middleware para parsear JSON
const PORT = process.env.PORT || 3000;
app.use(express.json());

// Endpoint raíz
app.get('/', (req, res) => {
  res.json({ message: '¡Servidor Express corriendo con Node.js!' });
});

app.listen(PORT, () => {
  console.log(`Servidor escuchando en http://localhost:${PORT}`);
});
