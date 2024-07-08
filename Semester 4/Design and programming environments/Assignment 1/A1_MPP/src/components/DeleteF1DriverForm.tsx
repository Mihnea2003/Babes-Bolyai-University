// DeleteF1DriverForm.tsx
import React, { useState } from 'react';
import axios from 'axios';
import './DeleteF1DriverForm.css';

interface DeleteF1DriverFormProps {
    onDelete: (id: number) => void;
    drivers: { id: number; name: string }[];
}

const DeleteF1DriverForm: React.FC<DeleteF1DriverFormProps> = ({ onDelete, drivers }) => {
    const [id, setId] = useState<number>();

    const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        if (!id) {
            alert('Please fill in the ID field');
            return;
        }
    
        const driverToDelete = drivers.find(driver => driver.id === id);
        if (!driverToDelete) {
            alert('Driver with this ID does not exist');
            return;
        }
    
        try {
            await axios.delete(`http://localhost:5000/api/f1drivers/${id}`);
            onDelete(id);
            setId(undefined); // Reset ID after deletion
        } catch (error) {
            console.error('Error deleting F1 driver:', error);
        }
    };

    return (
        <div className="delete-f1-driver-container">
            <header>
                <h1 className="title">Delete F1 Driver</h1>
            </header>
            <form onSubmit={handleSubmit}>
                <div className="form-group">
                    <label className="form-label">ID:</label>
                    <input className="form-field" type="number" value={id || ''} onChange={(e) => setId(parseInt(e.target.value))} />
                </div>
                <button className='button' type="submit">Delete Driver</button>
            </form>
        </div>
    );
}

export default DeleteF1DriverForm;
