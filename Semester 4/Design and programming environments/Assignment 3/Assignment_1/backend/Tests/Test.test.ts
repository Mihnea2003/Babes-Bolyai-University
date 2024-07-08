/* eslint-disable @typescript-eslint/no-explicit-any */
import { Request, Response } from 'express';
import { ParamsDictionary } from 'express-serve-static-core';
import {
  getAllCustomers,
  getCustomerById,
  createCustomer,
  updateCustomer,
  deleteCustomer,
  getShoesByCustomerId,
  getAllShoes,
  createShoe,
  updateShoe,
  deleteShoe
} from '../controller/shoecontroller'; // Import your controller functions

describe('Customer Controller Tests', () => {
  let req: Request<ParamsDictionary, any, any>;
  let res: Partial<Response>;

  beforeEach(() => {
    req = {} as Request<ParamsDictionary, any, any>;
    res = {
      status: jest.fn().mockReturnValue({}),
      json: jest.fn(),
      end: jest.fn()
    };
  });

  describe('getAllCustomers', () => {
    it('should fetch all customers', async () => {
      await getAllCustomers(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(200);
      expect(res.json).toHaveBeenCalled();
    });
    // Add more test cases for error scenarios
  });

  describe('getCustomerById', () => {
    it('should fetch a customer by ID', async () => {
      // Mock request params
      req.params = { customer_id: 'customer_id_here' } as ParamsDictionary;
      await getCustomerById(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(200);
      expect(res.json).toHaveBeenCalled();
    });
    // Add more test cases for error scenarios
  });

  describe('createCustomer', () => {
    it('should create a new customer', async () => {
      // Mock request body
      req.body = { customer_name: 'New Customer' };
      await createCustomer(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(201);
      expect(res.json).toHaveBeenCalledWith({ customer_id: expect.any(String), customer_name: 'New Customer' });
    });
    // Add more test cases for error scenarios
  });

  describe('updateCustomer', () => {
    it('should update an existing customer', async () => {
      // Mock request params and body
      req.params = { customer_id: 'customer_id_here' } as ParamsDictionary;
      req.body = { customer_name: 'Updated Customer' };
      await updateCustomer(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(200);
      expect(res.json).toHaveBeenCalledWith({ customer_id: 'customer_id_here', customer_name: 'Updated Customer' });
    });
    // Add more test cases for error scenarios
  });

  describe('deleteCustomer', () => {
    it('should delete an existing customer', async () => {
      // Mock request params
      req.params = { customer_id: 'customer_id_here' } as ParamsDictionary;
      await deleteCustomer(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(204);
      expect(res.end).toHaveBeenCalled();
    });
    // Add more test cases for error scenarios
  });

});

describe('Shoe Controller Tests', () => {
  let req: Request<ParamsDictionary, any, any>;
  let res: Partial<Response>;

  beforeEach(() => {
    req = {} as Request<ParamsDictionary, any, any>;
    res = {
      status: jest.fn().mockReturnValue({}),
      json: jest.fn(),
      end: jest.fn()
    };
  });

  describe('getShoesByCustomerId', () => {
    it('should fetch all shoes for a customer', async () => {
      // Mock request params
      req.params = { customer_id: 'customer_id_here' } as ParamsDictionary;
      await getShoesByCustomerId(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(200);
      expect(res.json).toHaveBeenCalled();
    });
    // Add more test cases for error scenarios
  });

  describe('getAllShoes', () => {
    it('should fetch all shoes', async () => {
      await getAllShoes(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(200);
      expect(res.json).toHaveBeenCalled();
    });
    // Add more test cases for error scenarios
  });

  

  describe('createShoe', () => {
    it('should create a new shoe', async () => {
      // Mock request body
      req.body = { shoe_brand: 'Nike', shoe_size: 10, shoe_model: 'Air Max', shoe_available: true, customer_id: 'customer_id_here' };
      await createShoe(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(201);
      expect(res.json).toHaveBeenCalledWith({ id: expect.any(String), brand: 'Nike', size: 10, model: 'Air Max', available: true, customerId: 'customer_id_here' });
    });
    // Add more test cases for error scenarios
  });

  describe('updateShoe', () => {
    it('should update an existing shoe', async () => {
      // Mock request params and body
      req.params = { shoe_id: 'shoe_id_here' } as ParamsDictionary;
      req.body = { shoe_brand: 'Adidas', shoe_size: 9, shoe_model: 'UltraBoost', shoe_available: false, customer_id: null };
      await updateShoe(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(200);
      expect(res.json).toHaveBeenCalledWith({ id: 'shoe_id_here', brand: 'Adidas', size: 9, model: 'UltraBoost', available: false, customerId: null });
    });
    // Add more test cases for error scenarios
  });

  describe('deleteShoe', () => {
    it('should delete an existing shoe', async () => {
      // Mock request params
      req.params = { shoe_id: 'shoe_id_here' } as ParamsDictionary;
      await deleteShoe(req, res as Response);
      expect(res.status).toHaveBeenCalledWith(204);
      expect(res.end).toHaveBeenCalled();
    });
    // Add more test cases for error scenarios
  });

});

