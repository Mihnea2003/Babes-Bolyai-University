import React from 'react';
import { Shoe } from 'd:/MPP_A1/Assignment_1/backend/models/Shoes';

interface ShowShoeListProps {
    shoes: Shoe[];
    isLoading: boolean;
}

const ShowShoeList: React.FC<ShowShoeListProps> = ({ shoes, isLoading }) => {
    console.log('Shoes:', shoes);

    if (isLoading) {
        return <p>Loading...</p>;
    }

    if (!Array.isArray(shoes) || shoes.length === 0) {
        console.error("Shoes is not an array or is empty:", shoes);
        return <div>No shoes available</div>;
    }

    return (
        <div className="shoe-list-container">
            <h2 className="list-title">Shoes</h2>
            <ul className="shoe-list">
            {shoes.map((shoe) => {
                return (
                    <li key={shoe.id} className="shoe-list-item">
                        <div className='shoe-list-item-content'>
                            Model: {shoe.model}, Brand: {shoe.brand}, Size: {shoe.size}, Available: {shoe.available ? 'Yes' : 'No'}
                        </div>
                    </li>
                );
            })}
            </ul>
        </div>
    );
}

export default ShowShoeList;
