import React, { useState } from 'react';
import axios from 'axios';
import './UpdateShoePage.css';
import { Shoe } from '../../backend/models/Shoes';

interface UpdateShoeFormProps {
  onUpdateShoe: (shoe: Shoe) => void;
}

function UpdateShoeForm({ onUpdateShoe }: UpdateShoeFormProps) {
  const [id, setId] = useState('');
  const [brand, setBrand] = useState('');
  const [size, setSize] = useState('');
  const [model, setModel] = useState('');
  const [available, setAvailable] = useState('');

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();

    try {
      const response = await axios.put<Shoe>(`http://localhost:5000/api/shoes/${id}`, {
        shoe_brand: brand,
        shoe_size: parseFloat(size),
        shoe_model: model,
        shoe_available: available === 'true',
        // If customer ID is included in the form, add it here
        // customer_id: customerId,
      });

      onUpdateShoe(response.data);

      // Reset form fields
      setId('');
      setBrand('');
      setSize('');
      setModel('');
      setAvailable('');
    } catch (error) {
      console.error('Error updating shoe:', error);
      alert('Error updating shoe. Please try again later.');
    }
  };
  
  return (
    <div className="update-shoe-container">
      <header>
        <h1 className="title">Update Shoe</h1>
      </header>
      <form onSubmit={handleSubmit}>
        <div className="form__group">
          <label className="form__label">Id:</label>
          <input className="form__field" type="number" value={id} onChange={(e) => setId(e.target.value)} />
        </div>
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
        <button className='button-63' type="submit">Update</button>
      </form>
    </div>
  );
}

export default UpdateShoeForm;
