const express = require('express');
const f1DriverController = require('../controllers/f1DriverController');

const router = express.Router();

// Routes for F1 drivers
router.get('/f1drivers', f1DriverController.getAllF1Drivers);
router.get('/f1drivers/:id', f1DriverController.getF1DriverById);
router.post('/f1drivers', f1DriverController.createF1Driver);
router.put('/f1drivers/:id', f1DriverController.updateF1Driver);
router.delete('/f1drivers/:id', f1DriverController.deleteF1Driver);

module.exports = router;
