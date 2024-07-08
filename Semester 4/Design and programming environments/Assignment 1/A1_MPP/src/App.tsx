// App.tsx
import React, { useState, useEffect } from 'react';
import './App.css';
import AddF1DriverForm from './components/AddF1DriverForm';
import DeleteF1DriverForm from './components/DeleteF1DriverForm';
import UpdateF1DriverForm from './components/UpdateF1DriverForm';
import F1DriverList from './components/ShowF1DriverList';
import GetF1DriverByIdForm from './components/GetF1DriverByIdForm';
import axios from 'axios';
import { F1Driver } from '../backend/models/f1Drivers';

function App() {
    const [drivers, setDrivers] = useState<F1Driver[]>([]);
    const [isLoading, setIsLoading] = useState<boolean>(true);
    const [error, setError] = useState<string | null>(null);

    useEffect(() => {
        const fetchDrivers = async () => {
            try {
                const response = await axios.get<F1Driver[]>('http://localhost:5000/api/f1drivers');
                setDrivers(response.data || []);
                setIsLoading(false);
            } catch (error) {
                console.error('Error fetching drivers:', error);
                setError('Error fetching drivers. Please try again later.');
                setIsLoading(false);
            }
        };

        fetchDrivers();
    }, []);

    const handleGetDriverById = async (id: number): Promise<F1Driver | null> => {
        try {
            const response = await axios.get<F1Driver>(`http://localhost:5000/api/f1drivers/${id}`);
            return response.data;
        } catch (error) {
            console.error('Error fetching driver by ID:', error);
            return null;
        }
    };

    const handleAddDriver = async (driver: F1Driver) => {
        try {
            setDrivers(prevDrivers => [...prevDrivers, driver]); // Optimistically update the state
            await axios.post<F1Driver>('http://localhost:5000/api/f1drivers', driver);
        } catch (error) {
            console.error('Error adding driver:', error);
        }
    };

    const handleDeleteDriver = async (id: number) => {
        try {
            setDrivers(prevDrivers => prevDrivers.filter(driver => driver.id !== id)); // Optimistically update the state
            await axios.delete(`http://localhost:5000/api/f1drivers/${id}`);
        } catch (error) {
            console.error('Error deleting driver:', error);
        }
    };

    const handleUpdateDriver = async (id: number, updatedDriver: F1Driver) => {
        try {
            const response = await axios.put(`http://localhost:5000/api/f1drivers/${id}`, updatedDriver);
            const newDriver = response.data;
            setDrivers(prevDrivers =>
                prevDrivers.map(driver => (driver.id === id ? newDriver : driver))
            );
        } catch (error) {
            console.error('Error updating driver:', error);
        }
    };

    return (
        <div className="App">
            <header className="App-header">
                <h1>F1 Driver Management</h1>
                {isLoading && <p>Loading...</p>}
                {error && <p>{error}</p>}
                <div className="row">
                    <div className="column">
                        <F1DriverList drivers={drivers} isLoading={isLoading} />
                    </div>
                    <div className="column">
                        <AddF1DriverForm onAdd={handleAddDriver} />
                    </div>
                </div>
                <div className="row">
                    <div className="column">
                        <DeleteF1DriverForm onDelete={handleDeleteDriver} drivers={drivers} />
                    </div>
                    <div className="column">
                        <UpdateF1DriverForm onUpdate={handleUpdateDriver} />
                    </div>
                </div>
                <div className="row">
                    <div className="column">
                        <GetF1DriverByIdForm onGetDriverById={handleGetDriverById} />
                    </div>
                </div>
            </header>
        </div>
    );
}

export default App;
