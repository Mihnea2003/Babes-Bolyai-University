/* eslint-disable no-undef */
/* eslint-disable @typescript-eslint/no-var-requires */
delete require.cache[require.resolve('./routes/Shoesroutes.ts')];
const shoeRoutes = require('./routes/Shoesroutes.ts');
const express = require('express');

const app = express();

app.use(express.json());

app.use((_req, res, next) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type, Authorization');
  next();
});

app.use('/api', shoeRoutes);

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});

module.exports = app;
