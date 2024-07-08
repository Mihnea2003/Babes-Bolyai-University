/* eslint-disable @typescript-eslint/no-explicit-any */
export class Shoe {
    public _id: string;
    public _brand: string;
    public _size: number;
    public _model: string;
    public _available: boolean;
    public _customerId: string; // New property

    constructor(id:string,brand: string, size: number, model: string, available: boolean = true, customerId: string) {
        if (size < 0) {
            throw new Error("Shoe size can't be a negative number.");
        }
        this._id = id
        this._brand = brand;
        this._size = size;
        this._model = model;
        this._available = available;
        this._customerId = customerId; 
    }

    static fromFirebase(data: any): Shoe {
        const { shoe_id, shoe_brand, shoe_size, shoe_model, shoe_available, customer_id } = data;
        const shoe = new Shoe(shoe_id,shoe_brand, shoe_size, shoe_model, shoe_available, customer_id);
        shoe._id = shoe_id;
        return shoe;
    }

    // Getter for the new property
    get customerId(): string {
        return this._customerId;
    }

    // Setter for the new property
    set customerId(customerId: string) {
        this._customerId = customerId;
    }
    get id(): string {
        return this._id;
    }

    get brand(): string {
        return this._brand;
    }

    get size(): number {
        return this._size;
    }

    get model(): string {
        return this._model;
    }

    get available(): boolean {
        return this._available;
    }

    set brand(brand: string) {
        this._brand = brand;
    }

    set size(size: number) {
        if (size < 0) {
            throw new Error("Shoe size can't be a negative number.");
        }
        this._size = size;
    }

    set model(model: string) {
        this._model = model;
    }

    set available(available: boolean) {
        this._available = available;
    }

    public toString = (): string => {
        return `Shoe: Brand: ${this._brand}, Size: ${this._size}, Model: ${this._model}, Available: ${this._available}`;
    }
}
