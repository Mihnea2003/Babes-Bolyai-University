/* eslint-disable @typescript-eslint/no-unused-vars */
import { useState, useEffect } from 'react';
import axios from 'axios';
import AddShoeForm from './Components/AddShoePage';
import UpdateShoeForm from './Components/UpdateShoePage';
import { Shoe } from '../backend/models/Shoes';
import './App.css';
import React from 'react';
export interface Customer {
  customer_id: string;
  customer_name: string;
}
function App() {
  const [shoes, setShoes] = useState<Shoe[]>([]);
  const [isLoading, setIsLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);
  const [currentPage, setCurrentPage] = useState(1);
  const shoesPerPage = 5;
  const [isError, setIsError] = useState(false);
  const [customers, setCustomers] = useState<Customer[]>([]);

  const checkConnection = async () => {
    try {
      const response = await fetch('http://localhost:5000/api/shoesdefine');
      if (!response.ok) {
        setIsError(true);
      }
    } catch (error) {
      setIsError(true);
    }
  };

  useEffect(() => {
    checkConnection();
  }, []);
  useEffect(() => {
    const fetchShoes = async () => {
      try {
        const response = await axios.get<Shoe[]>('http://localhost:5000/api/shoesdefine');
        setShoes(response.data || []);
        console.log(response.data);
        setIsLoading(false);
      } catch (error) {
        console.error('Error fetching shoes:', error);
        setError('Error fetching shoes - Server is closed');
        setIsLoading(false);
      }
    };

    const fetchCustomers = async () => {
      try {
        const response = await axios.get<Customer[]>('http://localhost:5000/api/customers');
        setCustomers(response.data || []);
        setIsLoading(false);
      } catch (error) {
        console.error('Error fetching customers:', error);
        setError('Error fetching customers - Server is closed');
        setIsLoading(false);
      }
    };

    fetchShoes();
    fetchCustomers();
  }, []);
  
  const handlePageChange = (pageNumber: number) => {
    setCurrentPage(pageNumber);
  };

  const getIndexRange = () => {
    const startIndex = (currentPage - 1) * shoesPerPage;
    const endIndex = startIndex + shoesPerPage;
    return [startIndex, endIndex];
  };

  const getPageNumbers = () => {
    const totalShoes = shoes.length;
    const totalPages = Math.ceil(totalShoes / shoesPerPage);
    return Array.from({ length: totalPages }, (_, index) => index + 1);
  };

  const handleDeleteShoe = async (shoeId: string) => {
    try {
      await axios.delete(`http://localhost:5000/api/shoes/${shoeId}`);
      const updatedShoes = shoes.filter(shoe => shoe.id !== shoeId);
      setShoes(updatedShoes);
    } catch (error) {
      console.error('Error deleting shoe:', error);
    }
  };

  const [selectedShoe, setSelectedShoe] = useState<Shoe | null>(null);

  const handleAddShoe = async (shoe: Shoe) => {
    try {
      const response = await axios.post<Shoe>('http://localhost:5000/api/shoes', shoe);
      setShoes(prevShoes => [...prevShoes, response.data]);
    } catch (error) {
      console.error('Error adding shoe:', error);
    }
  };

  const handleUpdateShoe = async (updatedShoe: Shoe) => {
    try {
      await axios.put(`http://localhost:5000/api/shoes/${updatedShoe.id}`, updatedShoe);
      setShoes(prevShoes => prevShoes.map(shoe => shoe.model === updatedShoe.model ? updatedShoe : shoe));
      setSelectedShoe(null); // Reset selected shoe after update
    } catch (error) {
      console.error('Error updating shoe:', error);
    }
  };

  const handleSortByModel = () => {
    const sortedShoes = [...shoes];
    sortedShoes.sort((a, b) => a.model.localeCompare(b.model));
    setShoes(sortedShoes);
  };

  const [startIndex, endIndex] = getIndexRange();
  const currentShoes = shoes.slice(startIndex, endIndex);
  return (
    <div>
    {isError && (
      <div style={{ color: 'red', textAlign: 'center', fontSize: 50 }}>
        There was an error connecting to the server. Please check your internet connection and try again later.
      </div>
    )}
      <header>
        <h1 className="title">Shoe Market</h1>
      </header>
      <button className='button-63' onClick={handleSortByModel}>Sort by Model</button>
      <AddShoeForm onAddShoe={handleAddShoe} />
      <UpdateShoeForm onUpdateShoe={handleUpdateShoe} />
      {isLoading && <p>Loading...</p>}
      {error && <p>{error}</p>}
      <ul>
  {Array.isArray(currentShoes) && currentShoes.length > 0 ? (
    currentShoes.map(shoe => (
      <li key={shoe._id}>
        <button className="shoe-button" onClick={() => setSelectedShoe(shoe)}>{shoe._model}</button>
        <button className="button-63" onClick={() => handleDeleteShoe(shoe._id)}>Delete</button>
      </li>
    ))
  ) : (
    <p>No shoes available</p>
  )}
</ul>
      {selectedShoe && (
        <div className="shoe-details">
          <h2>Shoe Details</h2>
          <p><strong>Size:</strong> {selectedShoe._size}</p>
          <p><strong>Brand:</strong> {selectedShoe._brand}</p>
          <p><strong>Available:</strong> {selectedShoe._available ? 'Yes' : 'No'}</p>
          <button className="button-63" onClick={() => setSelectedShoe(null)}>Close</button>
        </div>
      )}
      <div className="pagination">
        {getPageNumbers().map(pageNumber => (
          <button
            key={pageNumber}
            className={`button-63 ${currentPage === pageNumber ? 'active' : ''}`}
            onClick={() => handlePageChange(pageNumber)}
          >
            {pageNumber}
          </button>
        ))}
      </div>
      
    </div>
  );
}

export default App;
