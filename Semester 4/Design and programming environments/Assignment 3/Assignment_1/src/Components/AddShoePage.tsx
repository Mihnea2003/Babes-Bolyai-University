import React, { useState } from 'react';
import axios from 'axios';
import './AddShoePage.css';
import { Shoe } from '../../backend/models/Shoes';

interface AddShoeFormProps {
  onAddShoe: (shoe: Shoe) => void;
}

function AddShoeForm({ onAddShoe }: AddShoeFormProps) {
  const [brand, setBrand] = useState('');
  const [size, setSize] = useState('');
  const [model, setModel] = useState('');
  const [available, setAvailable] = useState('');
  const [customerId, setCustomerId] = useState('');

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    try {
      const response = await axios.post<Shoe>('http://localhost:5000/api/shoes', {
        shoe_brand: brand,
        shoe_size: parseFloat(size),
        shoe_model: model,
        shoe_available: available === 'true',
        customer_id: customerId
      });
      const newShoe: Shoe = response.data;
      onAddShoe(newShoe);
      // Reset form fields after successful submission
      setBrand('');
      setSize('');
      setModel('');
      setAvailable('');
      setCustomerId('');
    } catch (error) {
      console.error('Error adding shoe:', error);
      // Handle error here
    }
  };
  
  return (
    <div className="add-shoe-container">
      <header>
        <h1 className="title">Add Shoe</h1>
      </header>
      <form onSubmit={handleSubmit}>
        <div className="form__group">
          <label className="form__label">Brand:</label>
          <input className="form__field" type="text" value={brand} onChange={(e) => setBrand(e.target.value)} />
        </div>
        <div className="form__group">
          <label className="form__label">Size:</label>
          <input className="form__field" type="number" value={size} onChange={(e) => setSize(e.target.value)} />
        </div>
        <div className="form__group">
          <label className="form__label">Model:</label>
          <input className="form__field" type="text" value={model} onChange={(e) => setModel(e.target.value)} />
        </div>
        <div className="form__group">
          <label className="form__label">Available:</label>
          <select className="form__field" value={available} onChange={(e) => setAvailable(e.target.value)}>
            <option value="true">Yes</option>
            <option value="false">No</option>
          </select>
        </div>
        <div className="form__group">
          <label className="form__label">Customer ID:</label>
          <input className="form__field" type="text" value={customerId} onChange={(e) => setCustomerId(e.target.value)} />
        </div>
        <button className='button-63' type="submit">Add</button>
      </form>
    </div>
  );
}

export default AddShoeForm;
