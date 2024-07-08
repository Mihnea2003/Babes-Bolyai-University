// Example in-memory data storage (replace this with a database)
let f1Drivers = [
    { id: 1, name: "Lewis Hamilton", team: "Mercedes", age: 36 },
    { id: 2, name: "Max Verstappen", team: "Red Bull Racing", age: 24 },
    { id: 3, name: "Valtteri Bottas", team: "Mercedes", age: 32 },
    { id: 4, name: "Lando Norris", team: "McLaren", age: 22 },
    { id: 5, name: "Sergio Perez", team: "Red Bull Racing", age: 31 }
];

module.exports.getAllF1Drivers = (req, res) => {
    res.status(200).json(f1Drivers);
};

module.exports.getF1DriverById = (req, res) => {
    const id = parseInt(req.params.id);
    const driver = f1Drivers.find(driver => driver.id === id);
    if (driver) {
        res.status(200).json(driver);
    } else {
        res.status(404).json({ message: 'F1 driver not found' });
    }
};

module.exports.createF1Driver = (req, res) => {
    const { id, name, team, age, is_visible } = req.body;
    if (!id) {
        return res.status(400).json({ message: 'ID is required' });
    }
    const existingDriver = f1Drivers.find(driver => driver.id === id);
    if (existingDriver) {
        return res.status(400).json({ message: 'Driver with the provided ID already exists' });
    }
    const newDriver = { id, name, team, age };
    f1Drivers.push(newDriver);
    res.status(201).json(newDriver);
};




module.exports.updateF1Driver = (req, res) => {
    const id = parseInt(req.params.id);
    const { name, team, age, is_visible } = req.body;
    const index = f1Drivers.findIndex(driver => driver.id === id);
    if (index !== -1) {
        f1Drivers[index].name = name;
        f1Drivers[index].team = team;
        f1Drivers[index].age = age;
        res.status(200).json(f1Drivers[index]);
    } else {
        res.status(404).json({ message: 'F1 driver not found' });
    }
};


module.exports.deleteF1Driver = (req, res) => {
    const id = parseInt(req.params.id);
    const index = f1Drivers.findIndex(driver => driver.id === id);
    if (index !== -1) {
        f1Drivers.splice(index, 1);
        res.status(204).end();
    } else {
        res.status(404).json({ message: 'F1 driver not found' });
    }
};
