import { F1Driver } from "../models/F1Drivers";

export class Repository {
    private _f1Drivers: F1Driver[];
    private _nextId: number = 1;

    constructor(){
        this._f1Drivers = [];
        new F1Driver(1, 'Lewis Hamilton', 'Mercedes', 36, true),
        new F1Driver(2, 'Max Verstappen', 'Red Bull Racing', 24, true),
        new F1Driver(3, 'Lando Norris', 'McLaren', 22, true),

        this._f1Drivers = [
            new F1Driver(1, 'Lewis Hamilton', 'Mercedes', 36, true),
            new F1Driver(2, 'Max Verstappen', 'Red Bull Racing', 24, true),
            new F1Driver(3, 'Lando Norris', 'McLaren', 22, true),
        ];

    }

    addF1Driver(driver: F1Driver): void {
        const existingDriver = this._f1Drivers.find(d => d.name === driver.name);
        if (existingDriver) {
            throw new Error("F1 driver with this name already exists.");
        }
        driver.id = this._nextId++;
        this._f1Drivers.push(driver);
    }

    deleteF1DriverByName(name: string): void {
        const index = this._f1Drivers.findIndex(driver => driver.name === name);
        if (index === -1) {
            throw new Error("F1 driver with this name does not exist.");
        }
        this._f1Drivers[index].is_visible = false;
    }

    updateF1DriverByName(name: string, newDriver: F1Driver): void {
        const index = this._f1Drivers.findIndex(driver => driver.name === name);
        if (index === -1) {
            throw new Error("F1 driver with this name does not exist.");
        }
        this._f1Drivers[index] = newDriver;
    }

    getAllDrivers(): F1Driver[] {
        return this._f1Drivers;
    }
    
    displayAllDrivers(): F1Driver[] {
        return this._f1Drivers.filter(driver => driver.is_visible);
    }
}
