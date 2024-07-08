/* eslint-disable @typescript-eslint/no-var-requires */
const express = require('express');
const shoeController = require('../controller/shoecontroller'); 

const router = express.Router();

// customer routes
router.get('/customers', shoeController.getAllCustomers);
router.get('/customers/:customer_id', shoeController.getCustomerById);
router.post('/customers', shoeController.createCustomer);
router.put('/customers/:customer_id', shoeController.updateCustomer);
router.delete('/customers/:customer_id', shoeController.deleteCustomer);
router.get('/customers/:customer_id/shoes', shoeController.getShoesByCustomerId);

// shoe routes
router.get('/shoes', shoeController.getAllShoes); 
router.get('/shoes/:shoe_id', shoeController.getShoeById);
router.post('/shoes', shoeController.createShoe);
router.put('/shoes/:shoe_id', shoeController.updateShoe);
router.delete('/shoes/:shoe_id', shoeController.deleteShoe);

module.exports = router;
