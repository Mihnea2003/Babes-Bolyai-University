// GetF1DriverByIdForm.tsx
import React, { useState } from 'react';
import './GetF1DriverByIdForm.css'; // Assuming you have a CSS file for styling

interface F1Driver {
    id: number;
    name: string;
    team: string;
    age: number;
}

interface GetF1DriverByIdFormProps {
    onGetDriverById: (id: number) => Promise<F1Driver | null>; // Promise should return the fetched driver or null
}

const GetF1DriverByIdForm: React.FC<GetF1DriverByIdFormProps> = ({ onGetDriverById }) => {
    const [id, setId] = useState('');
    const [driver, setDriver] = useState<F1Driver | null>(null);

    const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        if (!id) {
            alert('Please fill in the ID field');
            return;
        }
        try {
            const driverId = parseInt(id);
            const fetchedDriver = await onGetDriverById(driverId);
            setDriver(fetchedDriver);
            setId('');
        } catch (error) {
            console.error('Error getting F1 driver by ID:', error);
        }
    };

    return (
        <div className="get-f1-driver-by-id-container">
            <header>
                <h1 className="title">Get F1 Driver By ID</h1>
            </header>
            <form onSubmit={handleSubmit}>
                <div className="form-group">
                    <label className="form-label">ID:</label>
                    <input className="form-field" type="number" value={id} onChange={(e) => setId(e.target.value)} />
                </div>
                <button className='button' type="submit">Get Driver</button>
            </form>
            {driver && (
                <div className="driver-details">
                    <h2>Driver Details</h2>
                    <p>ID: {driver.id}</p>
                    <p>Name: {driver.name}</p>
                    <p>Team: {driver.team}</p>
                    <p>Age: {driver.age}</p>
                </div>
            )}
        </div>
    );
}

export default GetF1DriverByIdForm;
