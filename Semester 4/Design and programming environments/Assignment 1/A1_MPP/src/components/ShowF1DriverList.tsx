// ShowF1DriverList.tsx
import React from 'react';
import './ShowF1DriverList.css';
import { F1Driver } from '../../backend/models/f1Drivers';

interface F1DriverListProps {
    drivers: F1Driver[];
    isLoading: boolean;
}

const F1DriverList: React.FC<F1DriverListProps> = ({ drivers, isLoading }) => {
    console.log('Drivers:', drivers); // Add this line to check the format of the drivers array

    // Check if drivers is not an array or is undefined
    if (isLoading) {
        return <p>Loading...</p>;
    }

    if (!Array.isArray(drivers) || drivers.length === 0) {
        console.error("Drivers is not an array or is empty:", drivers);
        return <div>No drivers available</div>; // Display a message indicating no drivers available
    }

    return (
        <div className="f1-driver-list-container">
            <h2 className="list-title">F1 Drivers</h2>
            <ul className="driver-list">
                {drivers.map(driver => (
                    <li key={driver.id} className="driver-item">
                        <span className='driver-data'>Id: {driver.id} Name: {driver.name}, Team: {driver.team}, Age: {driver.age}</span>
                    </li>
                ))}
            </ul>
        </div>
    );
}

export default F1DriverList;
