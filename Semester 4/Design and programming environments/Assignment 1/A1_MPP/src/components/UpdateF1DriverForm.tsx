// UpdateF1DriverForm.tsx
import React, { useState } from 'react';
import './UpdateF1DriverForm.css';
import axios from 'axios';
import { F1Driver } from '../../backend/models/f1Drivers';



interface UpdateF1DriverFormProps {
    onUpdate: (id: number, updatedDriver: F1Driver) => void;
}

function UpdateF1DriverForm({ onUpdate }: UpdateF1DriverFormProps) {
    const [id, setId] = useState('');
    const [name, setName] = useState('');
    const [team, setTeam] = useState('');
    const [age, setAge] = useState('');

    const handleSubmit = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        if (!id || !name || !team || !age) {
            alert('Please fill in all fields');
            return;
        }
        const ageValue = parseInt(age);
        if (isNaN(ageValue) || ageValue <= 0) {
            alert('Please enter a valid age');
            return;
        }
        try {
            const response = await axios.post<F1Driver>('http://localhost:5000/api/f1drivers', { id, name, team, age: ageValue });
            const newDriver: F1Driver = response.data;
            onUpdate(parseInt(id), newDriver);
            setId('');
            setName('');
            setTeam('');
            setAge('');
        } catch (error) {
            console.error('Error updating F1 driver:', error);
        }
    };
    

    return (
        <div className="update-f1-driver-container">
            <header>
                <h1 className="title">Update F1 Driver</h1>
            </header>
            <form onSubmit={handleSubmit}>
                <div className="form-group">
                    <label className="form-label">ID:</label>
                    <input className="form-field" type="number" value={id} onChange={(e) => setId(e.target.value)} />
                </div>
                <div className="form-group">
                    <label className="form-label">Name:</label>
                    <input className="form-field" type="text" value={name} onChange={(e) => setName(e.target.value)} />
                </div>
                <div className="form-group">
                    <label className="form-label">Team:</label>
                    <input className="form-field" type="text" value={team} onChange={(e) => setTeam(e.target.value)} />
                </div>
                <div className="form-group">
                    <label className="form-label">Age:</label>
                    <input className="form-field" type="number" value={age} onChange={(e) => setAge(e.target.value)} />
                </div>
                <button className='button' type="submit">Update Driver</button>
            </form>
        </div>
    );
}

export default UpdateF1DriverForm;
