/* eslint-disable @typescript-eslint/no-explicit-any */
import { Request, Response } from 'express';
import {  collection, doc, getDoc, getDocs, query, where, addDoc, updateDoc, deleteDoc } from 'firebase/firestore';
import db from '../firebaseConfig';
import { Shoe } from '../models/Shoes';
interface Customer {
    customer_id: string;
    customer_name: string;
  }
  function mapToShoe(data: any): Shoe {
    return new Shoe(
      data.id,
      data.brand,
      data.size,
      data.model,
      data.available,
      data.customerId
    );
  }
  
  
    
// Get all customers
export const getAllCustomers = async (_req: Request, res: Response) => {
    try {
      const customersRef = collection(db, 'customer');
      const q = query(customersRef);
      const querySnapshot = await getDocs(q);
      const customers: Customer[] = querySnapshot.docs.map((doc) => ({
        customer_id: doc.id,
        customer_name: doc.data().customer_name, // add this line
      }));
      res.status(200).json(customers);
    } catch (error) {
      console.error('Error fetching customers:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  
  // Get a single customer by ID
  export const getCustomerById = async (req: Request, res: Response) => {
    const { customer_id } = req.params;
    try {
      const customerRef = doc(db, 'customer', customer_id);
      const docSnapshot = await getDoc(customerRef);
      if (!docSnapshot.exists()) {
        res.status(404).json({ message: 'Customer not found' });
      } else {
        const customer: Customer = {
          customer_id: docSnapshot.id,
          customer_name: docSnapshot.data().customer_name,
          ...docSnapshot.data(),
        };
        res.status(200).json(customer);
      }
    } catch (error) {
      console.error('Error fetching customer:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  // Create a new customer
  export const createCustomer = async (req: Request, res: Response) => {
    const { customer_name } = req.body;
    try {
      const customersRef = collection(db, 'customer');
      const newCustomerRef = await addDoc(customersRef, { customer_name });
      const newCustomer: Customer = {
        customer_id: newCustomerRef.id,
        customer_name,
      };
      res.status(201).json(newCustomer);
    } catch (error) {
      console.error('Error creating customer:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  // Update an existing customer
  export const updateCustomer = async (req: Request, res: Response) => {
    const { customer_id } = req.params;
    const { customer_name } = req.body;
    try {
      const customerRef = doc(db, 'customer', customer_id);
      await updateDoc(customerRef, { customer_name });
      const updatedCustomer: Customer = {
        customer_id,
        customer_name,
      };
      res.status(200).json(updatedCustomer);
    } catch (error) {
      console.error('Error updating customer:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  // Delete a customer
  export const deleteCustomer = async (req: Request, res: Response) => {
    const { customer_id } = req.params;
    try {
      const customerRef = doc(db, 'customer', customer_id);
      await deleteDoc(customerRef);
      res.status(204).end();
    } catch (error) {
      console.error('Error deleting customer:', error);
      res.status(500).json({ message: error.message });
    }
  };
  // Get all shoes for a customer
export const getShoesByCustomerId = async (req: Request, res: Response) => {
    const { customer_id } = req.params;
    try {
      const shoesRef = collection(db, 'shoe');
      const q = query(shoesRef, where('customer_id', '==', customer_id));
      const querySnapshot = await getDocs(q);
      const shoes: Shoe[] = querySnapshot.docs.map((doc) => mapToShoe(doc.data()));
      res.status(200).json(shoes);
    } catch (error) {
      console.error('Error fetching shoes:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  export const getAllShoes = async (_req: Request, res: Response) => {
    try {
      const shoesRef = collection(db, 'shoe');
      const q = query(shoesRef);
      const querySnapshot = await getDocs(q);
      const shoes: Shoe[] = querySnapshot.docs.map((doc) => mapToShoe({
        id: doc.id,
        brand: doc.data().shoe_brand,
        model: doc.data().shoe_model,
        size: doc.data().shoe_size,
        available: doc.data().shoe_available,
        customerId: doc.data().customer_id,
      }));
      res.status(200).json(shoes);
    } catch (error) {
      console.error('Error fetching shoes:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  export const getShoeById = async (req: Request, res: Response) => {
    const { shoe_id } = req.params;
    try {
      const shoeRef = doc(db, 'shoe', shoe_id);
      const docSnapshot = await getDoc(shoeRef);
      if (!docSnapshot.exists()) {
        res.status(404).json({ message: 'Shoe not found' });
      } else {
        const shoeData = docSnapshot.data();
        const shoe: Shoe = mapToShoe({
          id: docSnapshot.id,
          shoe_brand: shoeData.shoe_brand,
          shoe_size: shoeData.shoe_size,
          shoe_model: shoeData.shoe_model,
          shoe_available: shoeData.shoe_available,
          customer_id: shoeData.customer_id,
        });
        res.status(200).json(shoe);
      }
    } catch (error) {
      console.error('Error fetching shoe:', error);
      res.status(500).json({ message: error.message });
    }
  };
  

  // Create a new shoe
export const createShoe = async (req: Request, res: Response) => {
    const { shoe_brand, shoe_size, shoe_model, shoe_available, customer_id } = req.body;
    try {
      const shoesRef = collection(db, 'shoe');
      const newShoeRef = await addDoc(shoesRef, {
        shoe_brand,
        shoe_size,
        shoe_model,
        shoe_available,
        customer_id,
      });
      const newShoe: Shoe = mapToShoe({
        id: newShoeRef.id,
        shoe_brand,
        shoe_size,
        shoe_model,
        shoe_available,
        customer_id,
      });
      res.status(201).json(newShoe);
    } catch (error) {
      console.error('Error creating shoe:', error);
      res.status(500).json({ message: error.message });
    }
  };
  
  // Update an existing shoe
  export const updateShoe = async (req: Request, res: Response) => {
  const { shoe_id } = req.params;
  const { shoe_brand, shoe_size, shoe_model, shoe_available, customer_id } = req.body;
  try {
    const shoeRef = doc(db, 'shoe', shoe_id);
    await updateDoc(shoeRef, {
      shoe_brand,
      shoe_size,
      shoe_model,
      shoe_available,
      customer_id,
    });
    const updatedShoe: Shoe = mapToShoe({
      id: shoe_id,
      shoe_brand,
      shoe_size,
      shoe_model,
      shoe_available,
      customer_id,
    });
    res.status(200).json(updatedShoe);
  } catch (error) {
    console.error('Error updating shoe:', error);
    res.status(500).json({ message: error.message });
  }
};
  
  // Delete a shoe
  export const deleteShoe = async (req: Request, res: Response) => {
    const { shoe_id } = req.params;
    try {
      const shoeRef = doc(db, 'shoe', shoe_id);
      await deleteDoc(shoeRef);
      res.status(204).end();
    } catch (error) {
      console.error('Error deleting shoe:', error);
      res.status(500).json({ message: error.message });
    }
  };
  // Add 10 customers and 10 shoes to each customer
export const addTenCustomersAndShoes = async () => {
  try {
    const customersToAdd = Array.from({ length: 10 }, (_, i) => ({
      customer_name: `Customer${i + 1}`,
    }));

    const customersRef = collection(db, 'customer');

    for (const customer of customersToAdd) {
      const newCustomerRef = await addDoc(customersRef, customer);

      const shoesToAdd = Array.from({ length: 10 }, (_, i) => ({
        shoe_brand: `Brand${i + 1}`,
        shoe_size: i + 7,
        shoe_model: `Model${i + 1}`,
        shoe_available: true,
        customer_id: newCustomerRef.id,
      }));

      const shoesRef = collection(db, 'shoe');

      for (const shoe of shoesToAdd) {
        await addDoc(shoesRef, shoe);
      }
    }

    console.log('10 customers and 10 shoes added to each customer successfully');
  } catch (error) {
    console.error('Error adding customers and shoes:', error)
  }
};
addTenCustomersAndShoes();
  
  